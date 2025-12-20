# Architektur Deep-Dive: AKIR Framework

## 1. Trust-Chain & Provisioning
Der Vertrauensanker liegt beim **Manager**. Nur er kann neue Administratoren autorisieren.

- **Manager:** Generiert Unique Secret-Keys und hinterlegt deren SHA-256 Hashes in der geschützten Registry.
- **Admin:** Nutzt diesen Key für die tägliche Authentifizierung.

### 2FA Provisioning
Neue Identitäten im System erfordern eine kryptografische Signatur, die nur durch einen MFA-geschützten Workflow (TOTP/FIDO2) einer zweiten autorisierten Person ausgelöst werden kann. Dies eliminiert den "Single Point of Failure" auf administrativer Ebene.

## 2. Kernel Enforcement Layer
Der Treiber (`edrdrv.sys`) agiert als oberster Schiedsrichter im System.

### Object Manager Callbacks
Wir nutzen `ObRegisterCallbacks`, um Handle-Anfragen auf den `EDRAgent.exe` zu filtern. 
- **Ziel:** Verhindert `PROCESS_TERMINATE` und `PROCESS_VM_WRITE`.
- **Kontext:** Selbst `NT AUTHORITY\SYSTEM` kann den Schutz nicht ohne den korrekten Key beenden.

## 3. Die Resilienz-Logik: Dead Man's Switch
Der Schutzstatus des Systems ist an einen Timer gebunden. Wird dieser nicht zwischen 14:30 und 15:30 Uhr aktualisiert, isoliert AKIR den Host.

### Der HTTPS -> HTTP Trick
Um automatisierte Replay-Angriffe zu verhindern, muss der Administrator den vom Tool generierten `https://`-Link manuell im Terminal zu `http://` abändern. Diese bewusste Protokoll-Manipulation dient als **Proof-of-Presence** (Beweis der Anwesenheit eines Menschen).

## 4. Integritätssicherung (SMSS Guard)
Wir überwachen den Session Manager (`smss.exe`), da dieser der Einstiegspunkt für fortgeschrittene Persistenz ist.
- **Vorgehensweise:** Vergleich der `.text`-Sektion im RAM mit dem signierten On-Disk Image.
- **Reaktion:** Bei Mismatch erfolgt ein sofortiger **VSS-Snapshot Rollback**.
