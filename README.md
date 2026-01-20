# AQI-Monitor-Node-Mcu

This project is a complete **WiFi-based Air Quality Monitoring Station** built using **NodeMCU ESP8266**.  
It measures:

- 🌡 Temperature (DHT11)
- 💧 Humidity (DHT11)
- 🌫 PM1.0, PM2.5, PM10 (PMS5003 Laser Dust Sensor)
- 🫁 CO₂ Concentration (MH-Z19 Sensor)
- 🌐 Live Web Dashboard (ESP8266 Web Server)

All sensor data is displayed in real-time on a web page hosted directly by the ESP8266.

---

## 🧰 Hardware Used

| Component | Description |
|------------|-------------|
| NodeMCU ESP8266 | Main microcontroller with WiFi |
| DHT11 | Temperature & Humidity sensor |
| PMS5003 | PM1.0 / PM2.5 / PM10 Air Quality Sensor |
| MH-Z19 | CO₂ (Carbon Dioxide) Sensor |
| Breadboard | For solderless connections |
| Jumper Wires | Male-Female connections |
| 5V Power Supply | For PMS5003 & MH-Z19 |

---

## 🔌 Pin Connections

### DHT11
| DHT11 | NodeMCU |
|-------|--------|
| VCC | 3.3V |
| GND | GND |
| DATA | D5 |

### PMS5003 (UART via SoftwareSerial)
| PMS5003 | NodeMCU |
|---------|--------|
| TX | D6 |
| RX | D7 |
| VCC | 5V |
| GND | GND |

### MH-Z19 CO₂ Sensor (UART)
| MH-Z19 | NodeMCU |
|--------|--------|
| TX | D1 |
| RX | D2 |
| Vin | 5V |
| GND | GND |

---

## 📚 Arduino Libraries Required

Install these from Arduino Library Manager:

- ESP8266WiFi
- ESP8266WebServer
- DHT sensor library
- PMS (by Mariusz Wojcieszek or equivalent)
- MHZ19
- SoftwareSerial

---

## 🌐 Web Interface

The ESP8266 hosts a web server at port 80.  
Once connected to WiFi, open the browser and visit:
```
http://<ESP8266_IP_ADDRESS>/
```

The page auto-refreshes every 2 seconds and shows:

- Temperature
- Humidity
- PM1.0
- PM2.5
- PM10
- CO₂ in ppm

---

## ⚙️ Features

- Real-time air quality monitoring
- Wireless access via phone or laptop
- No external cloud required
- Fully local network operation

---

## 📸 Project Type

This project is ideal for:

- Smart Home Environment Monitoring
- Pollution Tracking
- Educational IoT Projects
