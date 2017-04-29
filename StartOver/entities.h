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

struct Droplet{
  unsigned char x;
  short y;
};

struct Cloud{
  short x;
  signed char y;
};

struct Star{
  short x;
  signed char y;
};

#endif

