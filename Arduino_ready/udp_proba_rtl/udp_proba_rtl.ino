#include <WiFi.h>
#include <WiFiUdp.h>
#include "GyverButton.h"
GButton bt(PA12, LOW_PULL);

int status = WL_IDLE_STATUS;
char ssid[] = "ARS44PRO";        //  your network SSID (name)
char pass[] = "ars44profhc";     // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;                   // your network key Index number (needed only for WEP)

unsigned int localPort = 4444;      // local port to listen on

WiFiUDP Udp;

void setup() {
    //Initialize serial and wait for port to open:
    Serial.begin(115200);
    pinMode(LED_G, OUTPUT);
    while (!Serial) {
        ; // wait for serial port to connect. Needed for native USB port only
    }

    // check for the presence of the shield:
    if (WiFi.status() == WL_NO_SHIELD) {
        Serial.println("WiFi shield not present");
        // don't continue:
        while (true);
    }

    // attempt to connect to Wifi network:
    while (status != WL_CONNECTED) {
        Serial.print("Attempting to connect to SSID: ");
        Serial.println(ssid);
        // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
        status = WiFi.begin(ssid,pass);
        // wait 10 seconds for connection:
        delay(10000);
    }
    Serial.println("Connected to wifi");
    digitalWrite(LED_G, HIGH);
    printWifiStatus();

    Serial.println("\nStarting connection to server...");
    // if you get a connection, report back via serial:
}

void loop() {
  bt.tick();
  if (bt.isSingle()){
    Udp.beginPacket("172.20.10.2", 4444);
    Udp.write("1");
    Udp.endPacket();
  }
  if (bt.isDouble()){
    Udp.beginPacket("172.20.10.2", 4444);
    Udp.write("5");
    Udp.endPacket();
  }
}


void printWifiStatus() {
    // print the SSID of the network you're attached to:
    Serial.print("SSID: ");
    Serial.println(WiFi.SSID());

    // print your WiFi shield's IP address:
    IPAddress ip = WiFi.localIP();
    Serial.print("IP Address: ");
    Serial.println(ip);

    // print the received signal strength:
    long rssi = WiFi.RSSI();
    Serial.print("signal strength (RSSI):");
    Serial.print(rssi);
    Serial.println(" dBm");
}
