#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>

// WiFi
const char* ssid = "YOUR_WIFI";
const char* password = "YOUR_PASSWORD";

// API URL
String url = "https://www.googleapis.com/calendar/v3/calendars/YOUR_CALENDAR_ID/events?key=YOUR_API_KEY";

void setup() {
  Serial.begin(115200);

  // Connect WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected!");

  // HTTPS request
  WiFiClientSecure client;
  client.setInsecure();  // important

  HTTPClient http;
  http.begin(client, url);

  int httpCode = http.GET();

  if (httpCode > 0) {
    String payload = http.getString();
    Serial.println("Data Received:");
    Serial.println(payload);  // JSON output
  } else {
    Serial.println("Error in HTTP request");
  }

  http.end();
}

void loop() {
}