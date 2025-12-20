# 🛡️ AKIR: Advanced Kernel-Level Integrity & Resilience Framework

AKIR ist ein Proof-of-Concept (PoC) Framework zur Absicherung kritischer Windows-Infrastrukturen. Im Gegensatz zu klassischen EDR-Systemen, die primär auf Detektion setzen, fokussiert sich AKIR auf unüberwindbare Integrität und kryptografisch erzwungene Resilienz.

## 🎯 Kernphilosophie: "Assume Breach"

AKIR geht davon aus, dass Angreifer bereits administrative Privilegien erlangt haben könnten. Das System schützt den Endpunkt durch:

*   **Hardware-Anchored Trust:** Nutzung des TPM für Integritäts-Attestierung.
*   **Dual-Authorization:** Keine kritische Änderung ohne Vier-Augen-Prinzip (2FA).
*   **Human-in-the-loop:** Physische Anwesenheitstests durch bewusste Protokoll-Manipulation.

## 🏗️ System-Architektur

### 1. Kernel-Mode Enforcement (`edrdrv.sys`)

Das Fundament bildet ein Windows-Kernel-Treiber, der direkt in die Objekt-Manager-Routinen eingreift.

*   **Anti-Tamper:** Über `ObRegisterCallbacks` wird verhindert, dass selbst Administrator-Prozesse den Schutz-Agenten beenden oder modifizieren.
*   **Registry-Hardening:** Filtert Schreibzugriffe auf sicherheitskritische Konfigurationsschlüssel.
*   **Network-Isolation:** Integrierter WFP (Windows Filtering Platform) Layer zur sofortigen Isolierung bei Integritätsverlust.

### 2. Resilience Engine (The "Dead Man's Switch")

Ein täglicher administrativer Reset ist erforderlich, um den "Normalbetrieb" aufrechtzuerhalten.

*   **Zeitfenster:** Die Authentifizierung ist nur zwischen 14:30 und 15:30 Uhr möglich.
*   **Protocol-Flip (HTTPS -> HTTP):** Als Schutz gegen automatisierte Bots generiert das System eine HTTPS-Challenge. Der Admin muss diese manuell zu HTTP abändern, um seine bewusste Interaktion zu beweisen.

### 3. Identity & Provisioning (2FA Flow)

Neue Administratoren werden über ein duales Modell autorisiert:

*   **Manager 1:** Beantragt den kryptografischen Key.
*   **Manager 2 (Security Officer):** Aktiviert den Key mittels eines TOTP-Zweitfaktors (Google Authenticator/YubiKey).

## 🛠️ Build & Security Pipeline

Das Projekt nutzt eine gehärtete CI/CD-Pipeline, um die Chain of Trust bereits bei der Entwicklung sicherzustellen:

*   **vcpkg Integration:** Manifest-gesteuerte, reproduzierbare Abhängigkeiten.
*   **Binary Hardening:** Erzwingt `/guard:cf` (Control Flow Guard) und `/CETCOMPAT`.
*   **Security-Unit-Tests:** Die Pipeline bricht ab, wenn die 2FA-Logik oder der Protokoll-Check im Code manipuliert werden.

## 🚀 Installation (PoC)

1.  **Environment:** Windows 10/11 mit aktiviertem Testsigning-Mode (`bcdedit /set testsigning on`).
2.  **Build:**
    ```powershell
    ./scripts/Build.ps1
    ```
3.  **Deployment:**
    ```powershell
    ./scripts/Install.ps1
    ```

## ⚠️ Disclaimer

Dieses Projekt dient ausschließlich Bildungs- und Forschungszwecken (PoC). Der Einsatz eines Kernel-Treibers kann bei Fehlkonfiguration zur Systeminstabilität (BSOD) führen.

Entwickelt für High-Security-Umgebungen, in denen "Administrator-Rechte" nicht das Ende der Verteidigungslinie bedeuten dürfen.

---

👉 **Detaillierte Einblicke findest du im [Wiki](../../wiki) oder in der [Architektur-Dokumentation](docs/AKIR_Architecture_DeepDive.md).**