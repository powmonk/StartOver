#ifndef GLOBALS_H
#define GLOBALS_H

#include "entities.h"
#include "globals.h"

bool face = true;
bool walk = false;
bool crouch = false;
bool falling = true;
bool jump = false;
bool run;
byte frame = 0;
short levelX = 0;
byte playerX = 20;
byte playerY =  0;
byte jumpHeight;
short cloudCount =-200;
char screenTiles[17][8];
byte floorLevel;
short cloudX = 500;

bool getSolid(short y, short x){
  
  char temp = pgm_read_byte(&(levelMap[(byte)x/8][(byte)y/8]));
  if(temp!=0){
    return true;
  }
  return false;
}

Player badface;
#endif

