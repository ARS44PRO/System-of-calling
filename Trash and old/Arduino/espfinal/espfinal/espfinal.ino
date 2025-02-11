#include <Arduino.h>
#include <WiFi.h>
#include <driver/dac.h>
#include <HTTPClient.h>
#include "soc/rtc_wdt.h"

HTTPClient http;

const char* ssid     = "ARS44PRO";
const char* password = "ars44profhc";

hw_timer_t * timer = NULL; 
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED; 

#define BUFFERMAX 8000 //8000

uint8_t dataBuffer[BUFFERMAX];
int readPointer = 0, writePointer = 1;

bool play = false;

void IRAM_ATTR onTimer() {
  portENTER_CRITICAL_ISR(&timerMux);
  
  // play data: 
  if (play) {
    dac_output_voltage(DAC_CHANNEL_1, dataBuffer[readPointer]);
    Serial.println("ok");

    readPointer++;
    if (readPointer == BUFFERMAX) {
      readPointer = 0;
    }

    if ( getAbstand() == 0 ) {
      Serial.println("Buffer underrun!!!");
      play = false;
      writePointer = 1;
      readPointer = 0;
    }
  }

  portEXIT_CRITICAL_ISR(&timerMux);
}

int getAbstand() {
  int abstand = 0;
  if (readPointer < writePointer ) abstand =  BUFFERMAX - writePointer + readPointer;
  else if (readPointer > writePointer ) abstand = readPointer - writePointer;
  return abstand; 
}

void setup() {
  Serial.begin(115200);

  dac_output_enable(DAC_CHANNEL_1);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  rtc_wdt_protect_off();
  rtc_wdt_disable();
  
  timer = timerBegin(0, 2, true); // use a prescaler of 2
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 5000, true);
  timerAlarmEnable(timer);
}

void loop() {
  int abstand = getAbstand();
  if (abstand < 800) play = true;
  if (writePointer-readPointer>800 || readPointer-writePointer>800) play = true;
  if ( abstand >= 800) {
    http.begin("http://172.20.10.2:8090/getaudio"); 
    http.GET();
    uint8_t value = http.getString().toInt();
    dataBuffer[writePointer] = value;
    writePointer++;
    if (writePointer == BUFFERMAX) writePointer = 0;
    http.end();
  }
  Serial.println(writePointer);
}


