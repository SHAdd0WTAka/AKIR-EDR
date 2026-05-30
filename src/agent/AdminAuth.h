#pragma once
#include <string>

// Deklarationen für die Authentifizierungs-Logik
bool ValidateAdminSession(const std::string& inputUrl);
std::string GetAdminKeyState(const std::string& admin);
bool VerifySecret(const std::string& inputUrl);
void ResetKernelTimer();
bool IsWithinWindow(int startHour, int startMin, int endHour, int endMin);
