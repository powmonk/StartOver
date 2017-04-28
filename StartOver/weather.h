#ifndef WEATHER_H
#define WEATHER_H
#include "Arduboy2.h"
#include "globals.h"

Arduboy2 arduboy;
Sprites sprites;

short xSeed; 
short ySeed=99;
short localLevelX;
const byte showerSize = 20;


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
      drop[i].x = random(180)-25;
      drop[i].y = random(120)+63;
    }
    ySeed = -16;
  }

//  ((levelX+64)-levelX, 32)

  for(byte i=0;i<showerSize;i++){
    if(drop[i].y > 63 || drop[i].x < 0 || drop[i].x > 180){
      drop[i].y = -64;
      drop[i].x = random(180);
    }else{
      drop[i].y+=3;
      drop[i].x--;
    }
//    drop[i].x-=levelX/1024;


    droplet(drop[i].x, drop[i].y);
  }

  arduboy.setCursor(0,0);
  arduboy.print(32-levelX);

  
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
