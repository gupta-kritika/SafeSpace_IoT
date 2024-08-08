#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include "MAX30100_PulseOximeter.h"

// Define I2C addresses for the sensors
#define MLX90614_I2C_ADDR 0x5A   // MLX90614 default I2C address
#define MAX30100_I2C_ADDR 0x57   // MAX30100 default I2C address

// Create instances for sensors
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
PulseOximeter pox;
float sensor[4];
#define REPORTING_PERIOD_MS 1000
uint32_t tsLastReport = 0;

void onBeatDetected() {
  Serial.println("Heart beat detected!");
}

void setup() {
  Wire.begin();
  Serial.begin(9600); // Initialize serial communication with ESP32

  if (!pox.begin(MAX30100_I2C_ADDR)) {
    Serial.println("FAILED");
    for (;;);
  } else {
    Serial.println("SUCCESS");
  }

  // Configure sensor to use 7.6mA for LED drive
  pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);

  // Register a callback routine
  pox.setOnBeatDetectedCallback(onBeatDetected);
  
  // Initialize MLX90614
  mlx.begin(MLX90614_I2C_ADDR); // Initialize with MLX90614 I2C address
}

void loop() {
  // Update MAX30100 sensor
  pox.update();
  float bpm, spo, temp;
  
  temp = mlx.readObjectTempC();
  sensor[2] = 100;

  Serial.print(" *C\tObject Temperature: ");
  Serial.print(temp);
  Serial.println(" *C");

  if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
    bpm = pox.getHeartRate();
    spo = pox.getSpO2();
    
    // Print heart rate and SpO2
    Serial.print("Heart rate: ");
    Serial.print(bpm);
    Serial.print(" bpm / SpO2: ");
    Serial.print(spo);
    Serial.println(" %");

    // Send data to ESP32
    Serial.print(temp);
    Serial.print(",");
    Serial.print(bpm);
    Serial.print(",");
    Serial.println(spo);
    
    tsLastReport = millis();
  }
}
