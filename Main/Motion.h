#ifndef MOTION_H
#define MOTION_H

#include <MeMCore.h>
#include "Proximity.h"

#define DELAY 225
#define LEFT_WALL 550 // IR values less than this indicates the prescence of a left wall
#define RIGHT_WALL 550 // IR values less than this indicates the prescence of a right wall
#define IR_MAX_DISTANCE 6
#define ULTRASOUND_GAP 10

// gradient and intecept values for distance-voltage line
const double GRADIENT_LEFT = 0.0056;
const double INTERCEPT_LEFT = 1.1788;
const double GRADIENT_RIGHT = 0.0066;
const double INTERCEPT_RIGHT = 0.8552;

MeDCMotor motorLeft(M1);
MeDCMotor motorRight(M2);

// checks IR sensors and adjusts mbot
void moveFront();

// checks if mbot is close to either walls and adjusts accordingly
void adjustAngle(int right, int left);

// checks if mbot is close to corresponding wall
bool hasLeftWall(int left);
bool hasRightWall(int right);

// steers the mbot by reducing speed on one wheel
// distance to wall to estimated through the distance-voltage graph of each IR sensor
// the linear portion of each graph (< 5cm) is used to estimate distance and how hard to steer
void steerLeft(int right);
void steerRight(int left);

// no steering, full speed ahead
void steerStraight();

// stops mbot
void halt();

// the following functions are for solving each puzzle case

// fixed 90 degree turns
void turnLeft();
void turnRight();

// fixed 180 degree turn
void uTurn();

// turns, then moves forward until a front wall is detected, where it then turns again
void doubleLeft();
void doubleRight();

void moveFront() {
  int left = readLeft();
  int right = readRight();
  adjustAngle(left, right);
}

void adjustAngle(int left, int right) {
  if (hasRightWall(right)) {
    steerLeft(right);
  } else if (hasLeftWall(left)) {
    steerRight(left);
  } else {
    steerStraight();
  }
}

bool hasLeftWall(int left) {
  return left < LEFT_WALL;
}

bool hasRightWall(int right) {
  return right < RIGHT_WALL;
}

void steerLeft(int right) {
  double ratio = ((GRADIENT_RIGHT * right) + INTERCEPT_RIGHT) / IR_MAX_DISTANCE;
  int i = (int) ratio * -255;
  motorLeft.run(i);
  motorRight.run(255);
}

void steerRight(int left) {
  double ratio = ((GRADIENT_LEFT * left) + INTERCEPT_LEFT) / IR_MAX_DISTANCE;
  int i = (int) ratio * 255;
  motorLeft.run(-255);
  motorRight.run(i);
}

void steerStraight() {
  motorLeft.run(-255);
  motorRight.run(255);
}

void halt() {
  motorLeft.stop();
  motorRight.stop();
}

// puzzle motion

void turnLeft() {
  motorLeft.run(255);
  motorRight.run(255);
  delay(DELAY);
}

void turnRight() {
  motorLeft.run(-255);
  motorRight.run(-255);
  delay(DELAY);
}

void uTurn() {
  if (hasLeftWall(readLeft())) {
    motorLeft.run(-255);
    motorRight.run(-255);
  } else {
    motorLeft.run(255);
    motorRight.run(255);
  }
  delay(250);
}

void doubleLeft() {
  turnLeft();
  while (getFrontDistance() > ULTRASOUND_GAP) {
    moveFront();
  }
  turnLeft();
}

void doubleRight() {
  turnRight();
  while (getFrontDistance() > ULTRASOUND_GAP) {
    moveFront();
  }
  turnRight();
}

#endif
