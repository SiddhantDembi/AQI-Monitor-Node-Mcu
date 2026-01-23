#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <SoftwareSerial.h>
#include <DHT.h>
#include "PMS.h"
#include <MHZ19.h>

#define DHTPIN D5
#define DHTTYPE DHT11

const char* ssid = "<SSID>";
const char* password = "<PASS";

ESP8266WebServer server(80);
DHT dht(DHTPIN, DHTTYPE);

// PMS5003 → RX = D6, TX = D7
SoftwareSerial pmsSerial(D6, D7);
PMS pms(pmsSerial);
PMS::DATA data;

// MH-Z19 → RX = D1, TX = D2
SoftwareSerial co2Serial(D1, D2);
MHZ19 mhz19;

float temperature = 0;
float humidity = 0;
int pm1 = 0, pm25 = 0, pm10 = 0;
int co2ppm = 0;

void handleRoot() {
  String html = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Air Quality Monitor</title>
<script>
function updateData() {
  fetch('/data')
    .then(res => res.json())
    .then(d => {
      document.getElementById("temp").innerText = d.temp;
      document.getElementById("hum").innerText = d.hum;
      document.getElementById("pm1").innerText = d.pm1;
      document.getElementById("pm25").innerText = d.pm25;
      document.getElementById("pm10").innerText = d.pm10;
      document.getElementById("co2").innerText = d.co2;
    });
}
setInterval(updateData, 2000);
</script>
</head>
<body onload="updateData()">
<h2>Air Quality Monitor</h2>
<p>Temperature: <span id="temp">--</span> °C</p>
<p>Humidity: <span id="hum">--</span> %</p>
<p>PM1.0: <span id="pm1">--</span> µg/m³</p>
<p>PM2.5: <span id="pm25">--</span> µg/m³</p>
<p>PM10: <span id="pm10">--</span> µg/m³</p>
<p>CO₂: <span id="co2">--</span> ppm</p>
</body>
</html>
)rawliteral";

  server.send(200, "text/html", html);
}

void handleData() {
  String json = "{";
  json += "\"temp\":" + String(temperature) + ",";
  json += "\"hum\":" + String(humidity) + ",";
  json += "\"pm1\":" + String(pm1) + ",";
  json += "\"pm25\":" + String(pm25) + ",";
  json += "\"pm10\":" + String(pm10) + ",";
  json += "\"co2\":" + String(co2ppm);
  json += "}";

  server.send(200, "application/json", json);
}

void setup() {
  Serial.begin(9600);
  pmsSerial.begin(9600);
  co2Serial.begin(9600);
  dht.begin();

  pms.wakeUp();
  delay(3000);
  pms.activeMode();

  mhz19.begin(co2Serial);
  mhz19.autoCalibration(false);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(500);

  server.on("/", handleRoot);
  server.on("/data", handleData);
  server.begin();
}

unsigned long lastRead = 0;

void loop() {
  server.handleClient();

  if (millis() - lastRead > 2000) {
    lastRead = millis();

    humidity = dht.readHumidity();
    temperature = dht.readTemperature();

    if (pms.readUntil(data)) {
      pm1  = data.PM_AE_UG_1_0;
      pm25 = data.PM_AE_UG_2_5;
      pm10 = data.PM_AE_UG_10_0;
    }

    co2ppm = mhz19.getCO2();
  }
}
