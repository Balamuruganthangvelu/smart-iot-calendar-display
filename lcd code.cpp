#include <WiFi.h>
#include <HTTPClient.h>
#include <LiquidCrystal_I2C.h>
#include <ArduinoJson.h>

// WiFi Credentials
const char* ssid = "YOUR_WIFI";
const char* password = "YOUR_PASSWORD";

// Google Calendar API URL
String url = "https://www.googleapis.com/calendar/v3/calendars/YOUR_CALENDAR_ID/events?key=YOUR_API_KEY";

// LCD setup
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(115200);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Connecting WiFi");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting...");
  }

  lcd.clear();
  lcd.print("WiFi Connected");
  delay(2000);
}

void loop() {

  if (WiFi.status() == WL_CONNECTED) {

    HTTPClient http;
    http.begin(url);

    int httpCode = http.GET();

    if (httpCode > 0) {

      String payload = http.getString();
      Serial.println(payload);

      // JSON Parsing
      DynamicJsonDocument doc(4096);
      deserializeJson(doc, payload);

      const char* event = doc["items"][0]["summary"];
      const char* time = doc["items"][0]["start"]["dateTime"];

      lcd.clear();

      lcd.setCursor(0,0);
      lcd.print(event);

      lcd.setCursor(0,1);
      lcd.print("Time:");
      lcd.print(time);

    } else {
      lcd.clear();
      lcd.print("API Error");
    }

    http.end();
  }

  delay(60000); // update every 1 minute
}