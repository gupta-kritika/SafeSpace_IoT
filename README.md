
# IoT Project: Health Monitoring System with MAX30100 and MLX90614 Sensors

## Project Overview

This project implements a health monitoring system using the MAX30100 and MLX90614 sensors interfaced with an Arduino Uno. The system measures pulse rate, SpO2 levels, and body temperature. The data collected by the sensors is transmitted to an ESP32 WiFi module via serial communication, which then pushes the data to Firebase Realtime Database for real-time monitoring and analysis.

This project was created as a part of a Stress Detection and Management Application that detected stress through Image detection and classified it into four intensity levels with the help of physiological sensor data collected through IoT implementation. The application further helped users manage stress through a chatbot functionality and an NLP-based recommendation system.

## Components Used

- **Arduino Uno**: Serves as the main microcontroller for interfacing with the sensors.
- **ESP32 WiFi Module**: Handles Wi-Fi connectivity and data transmission to Firebase.
- **MAX30100 Sensor**: Measures pulse rate and SpO2 levels.
- **MLX90614 Sensor**: Measures body temperature without contact.
- **Firebase Realtime Database**: Stores the sensor data for real-time monitoring.

## Project Features

- **Real-time Data Collection**: The MAX30100 and MLX90614 sensors continuously collect vital health data.
- **Data Transmission**: The Arduino Uno sends the collected data to the ESP32 module via serial communication.
- **Cloud Integration**: The ESP32 module pushes the data to Firebase Realtime Database, allowing for remote monitoring and analysis.


## Hardware Setup

1. **Sensor Connections**:
   - **MAX30100**: Connect the sensor to the Arduino Uno via I2C (SDA to A4, SCL to A5).
   - **MLX90614**: Connect the sensor to the Arduino Uno via I2C (SDA to SDA, SCL to SCL).

2. **Arduino to ESP32 Communication**:
   - **TX (Arduino)** to **RX (ESP32)**
   - **RX (Arduino)** to **TX (ESP32)**
   - **GND (Arduino)** to **GND (ESP32)**

3. **Power Supply**:
   - Power the Arduino Uno and ESP32 with an appropriate power source.

## Software Setup

### 1. Arduino IDE

- Install the necessary libraries:
  - `Adafruit_MAX30100`
  - `Adafruit_MLX90614`
  - `Firebase ESP32`
  
- Load the provided Arduino sketch to interface with the sensors and communicate with the ESP32 module.

### 2. Firebase Setup

- Create a Firebase project and configure a Realtime Database.
- Obtain the Firebase credentials (API key, database URL) and add them to the ESP32 sketch.

### 3. Upload Code

- Upload the Arduino sketch to the Arduino Uno.
- Upload the ESP32 sketch to the ESP32 module.

## Usage

1. **Power on the system**: Ensure both the Arduino Uno and ESP32 module are powered on.
2. **Data Collection**: The sensors will start collecting data immediately.
3. **Data Transmission**: The Arduino sends the sensor data to the ESP32, which then pushes it to Firebase.
4. **Monitoring**: Access the Firebase Realtime Database to view the collected data in real time.


## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.

## Acknowledgements

- Thanks to the open-source community for providing the libraries and tools used in this project.
- Special mention to the authors of the MAX30100 and MLX90614 sensor libraries.



