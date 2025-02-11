#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

const char* ssid = "ARS44PRO";
const char* password = "ars44profhc";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  HTTPClient http;    
  WiFiClient wifiClient;
  http.begin(wifiClient, "http://192.168.1.1:8090/post");      
  http.addHeader("Content-Type", "text/plain");  
  http.POST(2);
  http.end();  
  delay(10);
}
