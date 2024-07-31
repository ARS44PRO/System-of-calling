#include <driver/dac.h>
#include "defin.h"

hw_timer_t * timer = NULL; 
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED; 

int readPointer = 0;

#define max 98216

bool play = false;

void IRAM_ATTR onTimer() {
  portENTER_CRITICAL_ISR(&timerMux);
  
  // play data: 
  if (play) {
    dac_output_voltage(DAC_CHANNEL_1, dataBuffer[readPointer]);
    readPointer++;
  }
  if (readPointer==max){
    readPointer=0;
  }

  portEXIT_CRITICAL_ISR(&timerMux);
}

void setup() {
  Serial.begin(115200);

  dac_output_enable(DAC_CHANNEL_1);

  timer = timerBegin(0, 2, true); // use a prescaler of 2
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 2444, true);
  timerAlarmEnable(timer);
}

void loop() {
  play=true;
}