#include "WiFi.h"
#include "AsyncUDP.h"

const char * ssid = "ARS44PRO";
const char * password = "ars44profhc";

AsyncUDP udp;

void setup()
{
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.println("WiFi Failed");
        while(1) {
            delay(1000);
        }
    }
    if(udp.listen(4444)) {
        Serial.print("UDP Listening on IP: ");
        Serial.println(WiFi.localIP());
    }
}
void loop()
{
  if (udp.listen(4444)){
    udp.onPacket([](AsyncUDPPacket packet) {
      int data = String((char*)packet.data()).toInt();
      Serial.println(data);
    });
  }
}
