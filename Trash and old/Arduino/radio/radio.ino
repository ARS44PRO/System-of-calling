#include "Arduino.h"
#include "WiFi.h"
#include "AudioFileSourceHTTPStream.h"
#include "AudioFileSourceBuffer.h"
#include "AudioGeneratorMP3.h"
#include "AudioOutputI2S.h"


const char* ssid = "ARS44PRO";
const char* password = "ars44profhc";

// Randomly picked URL
const char *URL="http://www.omskfm.ru:8000/1044-128.mp3";

AudioGeneratorMP3 *mp3;
AudioOutputI2S *out;
AudioFileSourceHTTPStream *file;
AudioFileSourceBuffer *buff;


void setup() {
  // Start the serial communication.
  Serial.begin(115200);
  delay(500);

  WiFi.disconnect();
  WiFi.softAPdisconnect(true);
  WiFi.mode(WIFI_STA);

  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
      Serial.println("WiFi Failed");
      while(1) {
          delay(1000);
      }
  }
  Serial.println("All ok!");

  file = new AudioFileSourceHTTPStream(URL);
  // Create a buffer using that stream
  buff = new AudioFileSourceBuffer(file, 2048);
  out = new AudioOutputI2S(0, 1);
  mp3 = new AudioGeneratorMP3();
  // Pass in the *buffer*, not the *http stream* to enable buffering
  out->SetOutputModeMono(false);
  mp3->begin(buff, out);

}

void loop() {
  if (mp3->isRunning()) {
    if (!mp3->loop()) mp3->stop(); 
  } else {
    Serial.printf("MP3 done\n");
    delay(1000);
  }
}