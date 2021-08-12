#ifndef PROXIMITY_H
#define PROXIMITY_H

#include <MeMCore.h>

MePort IR(PORT_3);
MeUltrasonicSensor ultrasonic(PORT_2);

// set IR sensors to high
void onIR();

// reads IR sensor reading on corresponding side
int readLeft();
int readRight();

// gets distance from front wall using ultrasonic sensor
double getFrontDistance();

void onIR() {
  IR.dWrite1(HIGH);
  IR.dWrite2(HIGH);
}

int readLeft() {
  return IR.aRead1();
}

int readRight() {
  return IR.aRead2();
}

double getFrontDistance() {
  return ultrasonic.distanceCm();
}

#endif
