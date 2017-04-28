#ifndef WEATHER_H
#define WEATHER_H
#include "Arduboy2.h"
#include "globals.h"

Arduboy2 arduboy;
Sprites sprites;

short xSeed; 
short ySeed=99;
short localLevelX;
const byte showerSize = 5;


struct Droplet{
  byte x;
  short y;
};

struct Droplet drop[showerSize];


void droplet(byte x, byte y){
  if(arduboy.everyXFrames(2)){
    sprites.drawSelfMasked(x,y, rainDrop,0);
  }else{
    sprites.drawSelfMasked(x,y, rainDrop,1);
  }
}

void shower(){


  if(ySeed == 99){
     for(byte i=0;i<showerSize;i++){
      drop[i].x = random(127);
      drop[i].y = random(63);
    }
    ySeed = 0;
  }

//  ((levelX+64)-levelX, 32)

  for(byte i=0;i<showerSize;i++){
    if(drop[i].y > 63 || ((levelX+drop[i].x)-levelX) < 0 ||((levelX+drop[i].x)-levelX) > 127){
      drop[i].y = 0;
      drop[i].x = random(127);
    }else{
      drop[i].y+=2;
//      drop[i].x+=levelX;
    }

    droplet(drop[i].x+levelX, drop[i].y);
  }

  
}


void rain(short levelX){
  localLevelX = levelX;
  shower();
}

struct Cloud{
  byte x;
  byte y;
};

#endif
