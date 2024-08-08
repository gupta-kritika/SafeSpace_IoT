#include <WiFi.h>
#include <FirebaseESP32.h>

// Replace with your network credentials
char ssid[] = "<network_ssid>";
char pass[] = "<password>";

// Firebase configuration
#define FIREBASE_HOST "<firebase_daatbase_link>"
#define FIREBASE_AUTH "<firebase_auth_token>"

FirebaseData firebaseData;
FirebaseAuth auth;
FirebaseConfig config;

float temperature, heartRate, spO2;

void sendToFirebase() {
  if (Firebase.ready()) {
    Firebase.setFloat(firebaseData, "/sensorData/temperature", temperature);
    Firebase.setFloat(firebaseData, "/sensorData/heartRate", heartRate);
    Firebase.setFloat(firebaseData, "/sensorData/spO2", spO2);
  } else {
    Serial.println("Firebase not ready");
  }
}

void setup() {
  Serial.begin(9600); // Initialize serial communication for debugging
  Serial2.begin(9600, SERIAL_8N1, 16, 17); // Initialize Serial2 with RX (GPIO 16) and TX (GPIO 17)

  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, pass);

  // Try connecting to WiFi for up to 20 seconds
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(1000);
    Serial.print(".");
    attempts++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nConnected to WiFi");

    // Configure Firebase
    config.host = FIREBASE_HOST;
    config.signer.tokens.legacy_token = FIREBASE_AUTH;

    Serial.println("Connecting to Firebase...");
    Firebase.begin(&config, &auth);
    Firebase.reconnectWiFi(true);
  } else {
    Serial.println("\nFailed to connect to WiFi. Please check your credentials and network.");
  }
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    if (Serial2.available() > 0) {
      String data = Serial2.readStringUntil('\n');
      sscanf(data.c_str(), "%f,%f,%f", &temperature, &heartRate, &spO2);
      Serial.print("Received data: ");
      Serial.print(temperature);
      Serial.print(", ");
      Serial.print(heartRate);
      Serial.print(", ");
      Serial.println(spO2);

      sendToFirebase();
    }
  } else {
    Serial.println("WiFi disconnected. Reconnecting...");
    WiFi.begin(ssid, pass);
  }
} 
