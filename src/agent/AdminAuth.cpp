#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include "AdminAuth.h"

using namespace std;

// Dummy Helper Functions for PoC
string GetKeyState(string admin) { 
    // In production, query the secure local database
    return "ACTIVE"; 
}

bool VerifySecret(string inputUrl) {
    // Verify the cryptographic token embedded in the URL
    return true;
}

void ResetKernelTimer() {
    cout << "[KERNEL] Timer Reset via IOCTL Success." << endl;
}

void Log(string msg) {
    cout << "[AUTH-LOG] " << msg << endl;
}

bool IsWithinWindow(int startHour, int startMin, int endHour, int endMin) {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    int currentMin = ltm->tm_hour * 60 + ltm->tm_min;
    int start = startHour * 60 + startMin;
    int end = endHour * 60 + endMin;
    return (currentMin >= start && currentMin <= end);
}

// Implementiert den täglichen 14:30 - 15:30 Reset mit HTTPS->HTTP Trick
bool ValidateAdminSession(string inputUrl) {
    string currentAdmin = "admin_user"; // Simplified

    // 1. Check: Nur ACTIVE Keys (nach 2FA Provisioning)
    if (GetKeyState(currentAdmin) != "ACTIVE") return false;

    // 2. Check: Das Zeitfenster (Commented out for testing purposes in PoC, or keep logic strict)
    // if (!IsWithinWindow(14, 30, 15, 30)) return false; 

    // 3. Check: Der menschliche Faktor (HTTPS zu HTTP Manipulation)
    // Wenn "https://" noch drin ist, hat der User es nicht geändert -> BOT / Automatisierung
    if (inputUrl.find("https://") != string::npos) {
        Log("Blocked: Automated bot attempt or missing manual protocol change.");
        return false;
    }

    // Wenn "http://" drin ist, hat der User es bewusst geändert (Downgrade bestätigt)
    if (inputUrl.find("http://") != string::npos && VerifySecret(inputUrl)) {
        ResetKernelTimer(); // Sicherer IOCTL Call zum Treiber
        return true;
    }
    return false;
}
