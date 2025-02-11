#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "ARS44PRO";
const char* password =  "ars44profhc";

void setup() {
  Serial.begin(115200); 

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  HTTPClient http;
  http.begin("http://172.20.10.2:8090/getaudio"); //HTTP
  http.GET();
  uint8_t val = http.getString().toInt();
  Serial.println(val);
  http.end();
  delay(3000);
}
