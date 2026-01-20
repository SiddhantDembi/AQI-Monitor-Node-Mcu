#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <SoftwareSerial.h>
#include <DHT.h>
#include "PMS.h"
#include <MHZ19.h>

#define DHTPIN D5
#define DHTTYPE DHT11

const char* ssid = "<YOUR_SSID>";
const char* password = "<YOUR_PASS>";

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
  String html = "<html><head><meta http-equiv='refresh' content='2'></head><body>";
  html += "<h2>Air Quality Monitor</h2>";
  html += "<p>Temperature: " + String(temperature) + " &deg;C</p>";
  html += "<p>Humidity: " + String(humidity) + " %</p>";
  html += "<p>PM1.0: " + String(pm1) + " ug/m3</p>";
  html += "<p>PM2.5: " + String(pm25) + " ug/m3</p>";
  html += "<p>PM10: " + String(pm10) + " ug/m3</p>";
  html += "<p>CO2: " + String(co2ppm) + " ppm</p>";
  html += "</body></html>";
  server.send(200, "text/html", html);
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
  mhz19.autoCalibration(false);   // Disable ABC for indoor monitoring

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  server.on("/", handleRoot);
  server.begin();
}

void loop() {
  server.handleClient();

  humidity = dht.readHumidity();
  temperature = dht.readTemperature();

  if (pms.readUntil(data)) {
    pm1  = data.PM_AE_UG_1_0;
    pm25 = data.PM_AE_UG_2_5;
    pm10 = data.PM_AE_UG_10_0;
  }

  co2ppm = mhz19.getCO2();
}
