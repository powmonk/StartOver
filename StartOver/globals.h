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
char screenTiles[17][8];
byte floorLevel;
bool initTrigger = 1;
static const byte levelHeight = 8;
static const byte levelWidth  = sizeof(levelMap[0]);
const byte starCount = (levelWidth/5);
const char showerSize = 10;
const char cloudCount = 3;

struct Droplet drop[showerSize];
struct Cloud cloudArray[cloudCount];
struct Star starArray[starCount];

bool getSolid(short y, short x){
  
  char temp = pgm_read_byte(&(levelMap[(byte)x/8][(byte)y/8]));
  if(temp!=0){
    return true;
  }
  return false;
}

Player badface;
#endif

