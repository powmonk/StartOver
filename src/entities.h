#ifndef ENTITIES_H
#define ENTITIES_H
#include "globals.h"

struct Player{
  byte x;
  byte frame;
  byte speed;
  bool direction;
  bool falling;
  bool jumping;
  
};

#endif

