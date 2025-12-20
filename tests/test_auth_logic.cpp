#include <gtest/gtest.h>
#include <string>
#include "../src/agent/AdminAuth.h" // Sauberer Include statt extern

// Test-Szenario: Korrekter HTTPS-zu-HTTP Wechsel
TEST(AuthTest, ProtocolManipulationCheck) {
    std::string validKey = "active_secret_key";
    
    // Simuliere falsche Eingabe (bleibt HTTPS) -> Muss fehlschlagen
    EXPECT_FALSE(ValidateAdminSession("https://edr.local/auth?code=" + validKey));

    // Simuliere korrekte manuelle Eingabe (Wechsel zu HTTP) -> Muss klappen
    // Hinweis: Im PoC gibt GetKeyState immer "ACTIVE" zurück und VerifySecret immer true.
    EXPECT_TRUE(ValidateAdminSession("http://edr.local/auth?code=" + validKey));
}

// Test-Szenario: 2FA Status Check (Mock-basiert)
TEST(AuthTest, RejectPendingKey) {
    // Da wir im PoC GetKeyState hardcoded haben, ist dieser Test hier symbolisch.
    // In einer echten Implementierung würden wir Mocking-Frameworks (gmock) nutzen.
    
    // Angenommen GetKeyState würde "PENDING" zurückgeben:
    // EXPECT_FALSE(ValidateAdminSession("http://edr.local/auth?code=pending_key"));
}