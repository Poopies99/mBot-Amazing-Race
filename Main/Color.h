#define COLOR_H
#define LDRWait 10

#include <MeMCore.h>
#include "Puzzle.h"

MeRGBLed led(0, 30);
MeLightSensor lightSensor(PORT_8);

#define LDR 0   //LDR sensor pin at A0
#define LED 13  //Check Indicator to signal Calibration Completed
#define SCANTIMES 50
#define LDRwait 5

long RGBvalues[3] = {};
long total = 0;
long blackvalues[3] = {118, 114, 127}; //black values for near full charge

// Gets the average RGB values of the detected color
void updateRGB();
// Using the detected RGB values, return the enum value for the detected color
Sign detectColor();

void updateRGB() {
  for (long cycle = 0; cycle < 3; cycle += 1) {
    switch(cycle) {
      case 0:
        led.setColor(255, 0, 0);
        break;
      case 1:
        led.setColor(0, 255, 0);
        break;
      case 2:
        led.setColor(0, 0, 255);
        break;
      }
    led.show(); //Must use .show() to make new colour take effect.
    for (long i = 0; i < SCANTIMES; i += 1) {
      total += lightSensor.read();
      delay(LDRwait);
    }
    RGBvalues[cycle] = (long)((double)total / SCANTIMES - blackvalues[cycle]);
    total = 0;
  }
}

Sign detectColor() {
  updateRGB();
  if (RGBvalues[0] >= 65) { //if red exceeds 65 it is yellow
    return U_TURN; // color = 2 (yellow);
  }
  else if (RGBvalues[0] >= 45) { //if red is between 45 and 65 it is red
    return LEFT; // color = 1 (red);
  }
  else if (RGBvalues[0] >= 20) { //if red is between 20 and 45 it could be either purple or blue
    if (RGBvalues[1] >= 30) { //blue has a green value exceeding 30
      return DOUBLE_RIGHT; // color = 5 (blue);
    } else { //purple's green value is less than 30
      return DOUBLE_LEFT; // color = 4 (purple);
    }
  } 
  else { //if red is less than 20 it could either be black or green
    if (RGBvalues[1] >= 20) { //green has a green value exceeding 30
      return RIGHT; //color = 3 (green);
    }
    else { //black's green value is close to 0
      return FINISH; // color = 0 (black);
    }
  }
}
