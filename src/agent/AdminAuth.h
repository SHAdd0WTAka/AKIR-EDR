#pragma once
#include <string>

// Deklarationen für die Authentifizierungs-Logik
bool ValidateAdminSession(std::string inputUrl);
std::string GetKeyState(std::string admin);
bool VerifySecret(std::string inputUrl);
void ResetKernelTimer();
bool IsWithinWindow(int startHour, int startMin, int endHour, int endMin);
