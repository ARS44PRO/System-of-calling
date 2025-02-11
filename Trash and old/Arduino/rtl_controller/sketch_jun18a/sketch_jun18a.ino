#include "defines.h"
// #include "GyverButton.h"

// GButton bt(PA15, LOW_PULL);
const IPAddress server(192,168,1,254);


void setup()
{
  Serial.begin(115200);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  pinMode(LED_R, OUTPUT);
  digitalWrite(LED_R, HIGH);
  delay(1000);
  digitalWrite(LED_R, LOW);
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() 
{
  // bt.tick();
  WiFiHttpClient http(client, server, 8090);
  String type = "text/plain";
  if (bt.isSingle()){
    http.post("/post", type, "2");
    Serial.println("2");
  } else if (bt.isDouble()){
    http.post("/post", type, "1");
    Serial.println("1");
  }
  http.stop();  
  delay(400);
}
