#pragma once
#include <string>

// Deklarationen für die Authentifizierungs-Logik
[[nodiscard]] bool ValidateAdminSession(const std::string& inputUrl) noexcept;
[[nodiscard]] std::string GetAdminKeyState(const std::string& admin) noexcept;
[[nodiscard]] bool VerifySecret(const std::string& inputUrl) noexcept;
void ResetKernelTimer() noexcept;
[[nodiscard]] bool IsWithinWindow(int startHour, int startMin, int endHour, int endMin) noexcept;
