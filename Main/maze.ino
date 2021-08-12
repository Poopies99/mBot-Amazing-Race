#include "Proximity.h"
#include "Motion.h"
#include "Waypoint.h"
#include "Color.h"
#include "Puzzle.h"

// sets up led and ir sensors
void setup() {
  Serial.begin(9600);
  led.setpin(13);
  onIR();
}

// checks if mbot is at a waypoint
// if at waypoint, stop and solve the puzzle
// if not, mbot drives forward
void loop() {
  if (atWaypoint()) {
    halt();
    solve(detectColor());
  } 
  else {
    moveFront();
  }
}
