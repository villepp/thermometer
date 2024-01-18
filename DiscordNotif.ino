#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "";
const char* password = "";

const char* webhook_url = "https://discord.com/api/webhooks/...........";

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to wifi...");
  }
  Serial.println("Connected to wifi");
}

void loop() {
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');

    
    if (command == "TempOver70") {
      sendDiscordMessage("Sauna on lämmin, 70V°C");
    } else if (command == "TempOver80") {
      sendDiscordMessage("Lämpötila yli 80°C");
    } else if (command == "TempOver90") {
      sendDiscordMessage("Lämpötila yli 90°C");
    } else if (command == "TempOver100") {
      sendDiscordMessage("Nyt vois melkeen jo mennä saunaan, 100°C");
    } else if (command == "TempOver110") {
      sendDiscordMessage("Lämpötila yli 110°C");
    } else if (command == "TempOver120") {
      sendDiscordMessage("Lämpötila yli 120°C");
    }
    // 
  }
}

void sendDiscordMessage(String message) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(webhook_url);
    http.addHeader("Content-Type", "application/json");
    
    String payload = "{\"content\": \"" + message + "\"}";
    
    int httpResponseCode = http.POST(payload);
    http.end();

    if (httpResponseCode > 0) {
      Serial.print("HTTP response code: ");
      Serial.println(httpResponseCode);
    } else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
  } else {
    Serial.println("wifi not connected");
  }
}
