#ifndef WAYPOINT_H
#define WAYPOINT_H

MeLineFollower lineFinder(PORT_1);

// check if there is a line
bool bothLineIn();

// adjusts mbot based on line sensor
bool atWaypoint();

// turns mbot to be perpendicular to the waypoint strip
void adjustWaypointLeft();
void adjustWaypointRight();

bool bothLineIn() {
  if (lineFinder.readSensors() == S1_IN_S2_IN) {
    return true;
  }
  return false;
}

bool atWaypoint() {
  int sensorState = lineFinder.readSensors();
  
  switch(sensorState)
  {
    case S1_IN_S2_IN:
      return true;
      break;
    case S1_IN_S2_OUT:
       adjustWaypointRight(); 
      return false; 
      break;
    case S1_OUT_S2_IN:
       adjustWaypointLeft();
      return false; 
      break;
    case S1_OUT_S2_OUT: 
      return false;
      break;   
    default:
      return false;
      break;
  }
}

void adjustWaypointLeft() {
  while (!bothLineIn()) {
    motorLeft.stop();
    motorRight.run(255);
  }
  motorRight.stop();
}

void adjustWaypointRight() {
  while (!bothLineIn()) {
    motorLeft.run(-255);
    motorRight.stop();
  }
  motorLeft.stop();
}

#endif
