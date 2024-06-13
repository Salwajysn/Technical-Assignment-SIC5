#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "FIK-Dekanat";
const char* password = "F4silkom";

const char* serverName = "http://172.23.13.4:5000/sensor";

#define MQPIN 34 // Pin where the sensor is connected

void setup() {
  Serial.begin(115200);
  pinMode(MQPIN, INPUT);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    // Read sensor value
    int sensorValue = analogRead(MQPIN);
    Serial.println("MQ Sensor Value is: ");
    Serial.println(sensorValue);

    // Create JSON payload
    String httpRequestData = "{\"sensor_value\": " + String(sensorValue) + "}";

    // Send HTTP POST request
    http.begin(serverName);
    http.addHeader("Content-Type", "application/json");

    int httpResponseCode = http.POST(httpRequestData);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(httpResponseCode);
      Serial.println(response);
    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  } else {
    Serial.println("WiFi Disconnected");
  }

  delay(10000); // Send a request every 10 seconds
}
