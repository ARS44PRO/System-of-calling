#include <WiFi.h>
#include <WebSocketClient.h>

const char* ssid     = "ARS44PRO";
const char* password = "ars44profhc";

char path[] = "localhost";
char host[] = IPAdress(172, 20, 10, 2);

WebSocketClient webSocketClient;
WiFiClient client;

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

  delay(5000);

  if (client.connect(host, 8001)) {
    Serial.println("Connected");
  } else {
    Serial.println("Connection failed.");
  }

  webSocketClient.path = path;
  webSocketClient.host = host;
  if (webSocketClient.handshake(client)) {
    Serial.println("Handshake successful");
  } else {
    Serial.println("Handshake failed.");
  }

}

void loop() {
  String data;
  webSocketClient.getData(data);
  Serial.println(data);
  delay(3000);

}