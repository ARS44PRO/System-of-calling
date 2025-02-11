#include "AudioOutputI2S.h"
#include "AudioGeneratorMP3.h"
#include "AudioFileSourceSD.h"
#include <SPI.h>
#include <SD.h>
#include "WiFi.h"
#include "AsyncUDP.h"

const char * ssid = "ARS44PRO";
const char * password = "ars44profhc";

AsyncUDP udp;

// Declare pointers for the MP3 generator, file source, and output.
AudioFileSourceSD *source;
AudioGeneratorMP3 *mp3;
AudioOutputI2S *out;
File file;
const int CS = 5;

#define SPI_SPEED SD_SCK_MHZ(40)

void setup() {
  // Start the serial communication.
  Serial.begin(115200);
  delay(500);
  pinMode(2, OUTPUT);
  source = new AudioFileSourceSD();
  out = new AudioOutputI2S(0, 1);
  mp3 = new AudioGeneratorMP3();

  Serial.println("Initializing SD card...");
  if (!SD.begin(CS)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
      Serial.println("WiFi Failed");
      while(1) {
          delay(1000);
      }
  }
  digitalWrite(2, HIGH);
  if(udp.listen(4444)) {
      Serial.print("UDP Listening on IP: ");
      Serial.println(WiFi.localIP());
  

  // source = new AudioFileSourceSD("/days.mp3");

  // out->SetOutputModeMono(true);
  // mp3->begin(source, out);
}
}
int i = 0;
void loop() {
  if (udp.listen(4444)){
    udp.onPacket([](AsyncUDPPacket packet) {
      int data = String((char*)packet.data()).toInt();
      if (data==1){
        i = 1;
      } else if (data==5){
        i = 2;
      }
    });
  }
  if (i==1){
    played();
    i = 0;
  } else if (i==2){
    mp3->stop();
    i = 0;
  }
  if (mp3->isRunning()) {
    if (!mp3->loop()) played();
  } 

}

void played(){
  source = new AudioFileSourceSD("/days.mp3");
  mp3->begin(source, out);
}
