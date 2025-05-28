# 🌱 Smart Plant(farm)

An automated plant care system using WIZnet W5500 Ethernet Shield and Ubidots cloud platform.

This project monitors various environmental parameters (temperature, humidity, soil moisture, dust, and rain) and controls actuators (water pump, fan) based on thresholds to maintain an optimal plant growing environment.

> ⚠️ Original article was hosted at: [https://www.instructables.com/Smart-Plantfarm/](https://www.instructables.com/Smart-Plantfarm/)  
> *Unfortunately, original source files has been removed.*

---

## 🧰 Hardware Components

- **Main Controller**: Arduino UNO (or WizArduino)
- **Network Module**: WIZnet W5500 Ethernet Shield
- **Sensors**:
  - DHT22 (Temperature & Humidity)
  - Soil Moisture Sensor
  - PM1001 Dust Sensor
  - Rain Sensor
- **Actuators**:
  - Water Pump (DWP-385)
  - DC Fan
  - 2x Relay Modules
- **Other**:
  - Transistors for relay driving
  - 12V Power Supply

---

## 🌐 Cloud Platform

Sensor data is uploaded to **[Ubidots](https://ubidots.com/)** using the W5500 Ethernet Shield. Ubidots dashboards allow real-time monitoring and visualization of environmental conditions.

---

## 🔁 Key Features

- Real-time monitoring of:
  - Temperature & humidity
  - Soil moisture
  - Rain detection
  - Dust concentration
- Automated control of:
  - Water pump (if soil is dry)
  - Fan (if temperature is high)
- Easy Ethernet communication using W5500 (no Wi-Fi required)

---

## 📦 Getting Started

1. Flash the Arduino with `smart_plantfarm.ino` (see `/src`)
2. Connect the W5500 to your router (static or DHCP IP)
3. Create a Ubidots device and get your Auth Token
4. Replace the `UBIDOTS_TOKEN` in the code
5. Power up the system and check your Ubidots dashboard

---

## ✅ TODO: Improvements & Upcoming Features

- [ ] **Sensor Auto-Calibration**  
  Add logic to automatically calibrate soil moisture, dust, and humidity sensors.

- [ ] **Bi-Directional Control via Ubidots**  
  Allow remote control of pump/fan via dashboard switches using Ubidots' return API.

- [ ] **Wi-Fi Compatibility Mode (W6100 or ESP8266)**  
  Enable optional Wi-Fi support for installations without Ethernet.

- [ ] **Sensor Fault Detection & Alerts**  
  Push notifications via Telegram or Slack when abnormal sensor values are detected.

- [ ] **OLED Display Integration**  
  Display real-time temperature, humidity, and actuator status locally.

- [ ] **3D-Printed Enclosure Design**  
  Provide printable case design for indoor/outdoor protection.

- [ ] **Power Optimization & Battery Operation**  
  Test solar-powered or battery-efficient versions with low-power sleep modes.

- [ ] **Code Refactoring & Modularization**  
  Separate sensor/network logic into classes and improve code maintainability.

---

## 📸 Demo Dashboard

*Coming soon...*

---

## 📄 License

MIT License
