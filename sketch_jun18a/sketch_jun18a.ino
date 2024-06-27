#include "defines.h"

const IPAddress server(192,168,110,158);

WiFiClient client;

void setup()
{
  Serial.begin(115200);
  WiFi.begin(ssid);
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
  pinMode(PA30, INPUT);
}

void loop() 
{
  WiFiHttpClient  http(client, server, 8090);
  String type = "text/plain";
  if (digitalRead(PA30)){
  http.post("/post", type, "ok");
  }
  http.stop();  
}
  /*btn.tick();
  if (btn.isSingle()){
    http.POST("2");
  }else if (btn.isDouble()){
    http.POST("1");
  }else if (btn.isHolded()){
    http.POST("0");
  }*/
