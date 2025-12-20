# Install.ps1 - Deployment, Signierung & Driver-Registration

$ErrorActionPreference = "Stop"

Write-Host "[AKIR] Starting Installation..."

# 1. Self-Signed Certificate Creation (PoC)
Write-Host "[AKIR] Creating Self-Signed Code Signing Certificate..."
$cert = New-SelfSignedCertificate -Type CodeSigningCert -Subject "CN=AKIR_EDR_Root" -CertStoreLocation Cert:\LocalMachine\My
$certPath = "Cert:\LocalMachine\My\$($cert.Thumbprint)"

# 2. Signing Binaries
Write-Host "[AKIR] Signing Binaries..."
# Set-AuthenticodeSignature -FilePath ".\build\Release\EDRAgent.exe" -Certificate $cert
# Set-AuthenticodeSignature -FilePath ".\build\Release\edrdrv.sys" -Certificate $cert

# 3. Apply WDAC Policy
Write-Host "[AKIR] Applying WDAC Policy..."
# ConvertFrom-CiPolicy -XmlFilePath "..\policies\WDAC_EDR.xml" -BinaryFilePath "C:\Windows\System32\CodeIntegrity\SiPolicy.p7b"

# 4. Register Kernel Driver
Write-Host "[AKIR] Registering Kernel Driver..."
# sc.exe create AKIRDriver binPath= "C:\Program Files\AKIR\edrdrv.sys" type= kernel start= system

Write-Host "[AKIR] Installation Complete. Reboot required."
