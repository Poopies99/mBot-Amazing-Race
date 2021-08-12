#ifndef PUZZLE_H
#define PUZZLE_H

#include "Motion.h"
#include "Proximity.h"
#include "Tune.h"

enum Sign {
  LEFT,
  RIGHT,
  U_TURN,
  DOUBLE_LEFT,
  DOUBLE_RIGHT,
  FINISH
};

// activates puzzle solving motion according to each case
void solve(Sign sign);

void solve(Sign sign) {
  switch(sign) {
    case LEFT:
      turnLeft();
      break;
    
    case RIGHT:
      turnRight();
      break;
    
    case U_TURN:
      uTurn();
      break;
    
    case DOUBLE_RIGHT:
      doubleRight();
      break;
    
    case DOUBLE_LEFT:
      doubleLeft();
      break;
    
    case FINISH: 
      celebrate();
      break;
  }
}



#endif
