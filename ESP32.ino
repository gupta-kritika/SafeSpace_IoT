#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL32156ZMyW"
#define BLYNK_TEMPLATE_NAME "SAFESPACE"
#define BLYNK_AUTH_TOKEN "bKKKmtXUIgAzLNT6gO1onUgz14bmpLnU"
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Replace with your Blynk auth token
char auth[] = "bKKKmtXUIgAzLNT6gO1onUgz14bmpLnU";
char ssid[] = "LC";
char pass[] = "lc@tiet1";

BlynkTimer timer;

float temperature, heartRate, spO2;

void sendToBlynk() {
  Blynk.virtualWrite(V1, temperature);
  Blynk.virtualWrite(V2, heartRate);
  Blynk.virtualWrite(V3, spO2);
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
    Serial.println("Connecting to Blynk...");
    Blynk.begin(auth, ssid, pass, "blynk.cloud", 8080); // Specify the Blynk server and port
  } else {
    Serial.println("\nFailed to connect to WiFi. Please check your credentials and network.");
  }

  // Set a timer to send data every second
  timer.setInterval(1000L, sendToBlynk);
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    Blynk.run();
  }
  timer.run();

  if (Serial2.available() > 0) {
    String data = Serial2.readStringUntil('\n');
    sscanf(data.c_str(), "%f,%f,%f", &temperature, &heartRate, &spO2);
    Serial.print("Received data: ");
    Serial.print(temperature);
    Serial.print(", ");
    Serial.print(heartRate);
    Serial.print(", ");
    Serial.println(spO2);

    Blynk.virtualWrite(V1, temperature);
    Blynk.virtualWrite(V2, heartRate);
    Blynk.virtualWrite(V3, spO2);
  }
}
