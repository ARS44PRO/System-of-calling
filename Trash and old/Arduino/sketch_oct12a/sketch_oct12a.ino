#include "AudioOutputI2S.h"
#include "AudioGeneratorMP3.h"
#include "AudioFileSourceSD.h"
#include <SPI.h>
#include <SD.h>

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

  source = new AudioFileSourceSD();
  out = new AudioOutputI2S(0, 1);
  mp3 = new AudioGeneratorMP3();

  Serial.println("Initializing SD card...");
  if (!SD.begin(CS)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  source = new AudioFileSourceSD("/days.mp3");

  mp3->begin(source, out);  
}

void loop() {
  // If the MP3 is running, loop it. Otherwise, stop it.
  if (mp3->isRunning()) {
    if (!mp3->loop()) mp3->stop();
  } 
  // If the MP3 is not running, print a message and wait for 1 second.
  else {
    Serial.println("MP3 done");
    delay(1000);
  }
}
