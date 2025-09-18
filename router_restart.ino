#include <WiFi.h>
#include <HTTPClient.h>
#include "config.h"

unsigned long lastRestartTime = 0;
int consecutiveFailures = 0;

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("ESP32 Router Auto-Restart");
  
  connectToWiFi();
  lastRestartTime = millis();
}

void loop() {
  unsigned long currentTime = millis();
  
  if (currentTime - lastRestartTime >= RESTART_INTERVAL_HOURS * 60 * 60 * 1000UL) {
    Serial.println("Time-based restart");
    restartRouter();
    lastRestartTime = currentTime;
  }
  
  if (!checkInternet()) {
    consecutiveFailures++;
    if (consecutiveFailures >= MAX_FAILURES) {
      Serial.println("Failure-based restart");
      restartRouter();
      consecutiveFailures = 0;
      lastRestartTime = currentTime;
    }
  } else {
    consecutiveFailures = 0;
  }
  
  delay(60000);
}

void connectToWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" WiFi connected");
}

bool checkInternet() {
  if (WiFi.status() != WL_CONNECTED) {
    connectToWiFi();
    return false;
  }
  
  HTTPClient http;
  http.begin("http://www.google.com");
  http.setTimeout(5000);
  int httpCode = http.GET();
  http.end();
  
  return httpCode > 0;
}

void restartRouter() {
  Serial.println("Restarting router...");
  
  HTTPClient http;
  http.begin(String("http://") + ROUTER_IP + "/api/device/control");
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  
  String rebootData = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><request><Control>1</Control></request>";
  http.POST(rebootData);
  
  http.end();
  delay(60000);
  connectToWiFi();
}