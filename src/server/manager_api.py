from flask import Flask, request, jsonify
import pyotp
import secrets

app = Flask(__name__)

# Mock Database
class MockDB:
    def __init__(self):
        self.keys = {}
    
    def save_pending_key(self, admin_id, key, status):
        self.keys[admin_id] = {"key": key, "status": status}
        
    def update_key_status(self, admin_id, status):
        if admin_id in self.keys:
            self.keys[admin_id]["status"] = status
            
    def get_status(self, admin_id):
        return self.keys.get(admin_id, {}).get("status")

db = MockDB()
OFFICER_SECRET = pyotp.random_base32() # Shared secret for Security Officer

# 1. Schritt: Key-Erstellung (Status: PENDING)
@app.route('/api/request_new_admin', methods=['POST'])
def request_key():
    # In production: Verify manager session here
    
    temp_key = secrets.token_hex(16)
    admin_id = request.json['admin_id']
    
    # Speichere den Key, aber markiere ihn als deaktiviert
    db.save_pending_key(admin_id, temp_key, status="WAITING_FOR_2FA")
    
    return jsonify({
        "message": "Key generiert. Er muss durch einen zweiten Security-Officer via 2FA aktiviert werden.",
        "request_id": admin_id
    })

# 2. Schritt: 2FA-Aktivierung durch eine ZWEITE Person
@app.route('/api/activate_key', methods=['POST'])
def activate_key():
    token = request.json.get('otp')
    admin_id = request.json.get('admin_id')
    
    if not token or not admin_id:
        return "Missing data", 400

    # Prüfe den TOTP-Token des ZWEITEN Managers (Security Officer)
    totp = pyotp.TOTP(OFFICER_SECRET)
    if totp.verify(token):
        db.update_key_status(admin_id, status="ACTIVE")
        return "✅ Admin-Key wurde erfolgreich aktiviert.", 200
    else:
        return "❌ Ungültiger 2FA-Token. Aktivierung abgelehnt.", 403

if __name__ == '__main__':
    print(f"Security Officer Secret (for testing): {OFFICER_SECRET}")
    app.run(port=5000)
