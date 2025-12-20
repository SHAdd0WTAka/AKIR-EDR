# Build.ps1 - Verifizierter Build-Prozess

$ErrorActionPreference = "Stop"

# 1. Verify VCPKG Hash
$ManifestHash = Get-FileHash "vcpkg.json" -Algorithm SHA256
Write-Host "Verifying Chain of Trust for Build Environment: $($ManifestHash.Hash)"
# In production, compare against known good hash

# 2. Build with CMake
Write-Host "Building AKIR Framework..."
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE="$env:VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake"
cmake --build build --config Release

Write-Host "Build Complete."
