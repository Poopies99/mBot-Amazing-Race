#ifndef TUNE_H
#define TUNE_H

#include "Motion.h"

MeBuzzer buzzer;

// stops, plays a tune, then enters an infinite loop to prevent any further action
void celebrate();

void celebrate() {
  halt();
  buzzer.tone(600, 1000);
  delay(2000);
  buzzer.tone(1200, 1000);
  delay(2000);
  
  noInterrupts();
  while(true) {}
}

#endif
