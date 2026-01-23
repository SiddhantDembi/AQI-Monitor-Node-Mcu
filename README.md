# AQI-Monitor-Node-Mcu

This project is a complete **WiFi-based Air Quality Monitoring Station** built using **NodeMCU ESP8266**.  
It measures:

- 🌡 Temperature (DHT11)
- 💧 Humidity (DHT11)
- 🌫 PM1.0, PM2.5, PM10 (PMS5003 Laser Dust Sensor)
- 🫁 CO₂ Concentration (MH-Z19 Sensor)
- 🌐 Live Web Dashboard (ESP8266 Web Server)
- 📊 Historical Data & Graphs using InfluxDB + Grafana

All sensor data is displayed in real-time on a web page hosted directly by the ESP8266.

---

## 📷 Setup Photos

### 🔌 Hardware Circuit
![IMG_2788](https://github.com/user-attachments/assets/b28aeb2f-7776-4dff-8f65-a9c2688a2203)

### 🌐 Web Dashboard (Live Output)
![ccaed038-a20e-4a51-9039-de2e0f3a6784](https://github.com/user-attachments/assets/5d8d59fa-6d59-4bbc-a82c-7b15fdf75734)

### 📊 Grafana Dashboard (Readings from InfluxDB)
<img width="1913" height="831" alt="image" src="https://github.com/user-attachments/assets/6ef738c2-0d1e-4f38-af72-9e4dfcb082f5" />

---

## 🧰 Hardware Used

| Component | Description |
|------------|-------------|
| NodeMCU ESP8266 | Main microcontroller with WiFi |
| DHT11 | Temperature & Humidity sensor |
| PMS5003 | PM1.0 / PM2.5 / PM10 Air Quality Sensor |
| MH-Z19 | CO₂ (Carbon Dioxide) Sensor |
| Breadboard | For solderless connections |
| Jumper Wires | Male-Female & Male-Male connections |
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
- ESP8266HTTPClient
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

Live display:
- Temperature (°C)
- Humidity (%)
- PM1.0 / PM2.5 / PM10 (µg/m³)
- CO₂ (ppm)

The page updates automatically using AJAX (no memory leaks, no full refresh).

---

## 📊 Data Logging & Visualization

Sensor data is pushed to:
- InfluxDB 2.x → Time-series storage
- Grafana → Professional dashboards, history, trends, alerts

Features:
- Real-time graphs
- Daily / weekly history
- Live value tiles
- Threshold coloring
- Expandable to multiple rooms

---

## ⚙️ Features

- Local web interface (no cloud dependency)
- Time-series storage with InfluxDB
- Professional Grafana dashboard
- Zero-value filtering for CO₂ sensor
- No soldering required
- Modular & scalable (add more rooms/sensors)

---

## 📸 Project Type

This project is ideal for:

- Smart Home Environment Monitoring
- Pollution Tracking
- Educational IoT Projects
