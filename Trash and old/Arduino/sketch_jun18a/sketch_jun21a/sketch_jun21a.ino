#include <WiFi.h>
#include <WiFiClient.h>
#include <HttpClient.h>

char ssid[] = "GreenWorld 11C";
char pass[] = "70467277";

const IPAddress server(192,168,110,158);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid);
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
  WiFiClient c;
  HttpClient http(c);
  http.get(server, NULL, 8090, "/");
  Serial.println(http.read());
  Serial.println(http.responseStatusCode());
  http.stop();
  delay(5000);
}

