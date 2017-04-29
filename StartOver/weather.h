#ifndef WEATHER_H
#define WEATHER_H
#include "Arduboy2.h"
#include "globals.h"
#include "entities.h"

Arduboy2 arduboy;
Sprites sprites;



void droplet(byte x, byte y){
  if(arduboy.everyXFrames(2)){
    sprites.drawSelfMasked(x,y, rainDrop,0);
  }else{
    sprites.drawSelfMasked(x,y, rainDrop,1);
  }
}

void rain(){

  if(initTrigger){
     for(byte i=0;i<showerSize;i++){
      drop[i].x = random(180)-25;
      drop[i].y = random(120)-63;
    }
  }

  for(byte i=0;i<showerSize;i++){
    if(drop[i].y > 63 || drop[i].x < 0 || drop[i].x > 180){
      drop[i].y = -64;
      drop[i].x = levelX+random(180);
    }else{
      drop[i].y+=3;
      drop[i].x--;
    }
    droplet(drop[i].x, drop[i].y);
  }

}

void clouds(){
  if(initTrigger){
   for(byte i=0;i<cloudCount;i++){
       cloudArray[i].x = random(512);
       cloudArray[i].y = random(24) - 5;
    }
  }

  for(short i=0;i<cloudCount;i++){
    if(cloudArray[i].x*0.3 < -64){
       cloudArray[i].x = 512;
       cloudArray[i].y = random(24);
    }

    cloudArray[i].x--;

//    cloudArray[i].x = levelX + cloudArray[i].x;
    if(cloudArray[i].x*0.3 > -32 || cloudArray[i].x*0.3  < 128){
      arduboy.drawBitmap(cloudArray[i].x*0.3, cloudArray[i].y,cloud,30,10,1);
    }
  }
}


void stars(){
    if(initTrigger){
      for(byte i=0;i<starCount;i++){
        starArray[i].x = random(512); 
        starArray[i].y = random(32); 
      }
    }

    for(byte i=0;i<starCount;i++){
      if(levelX+starArray[i].y > 0 || levelX+starArray[i].y < 128){
        arduboy.drawPixel(levelX/5+starArray[i].x, starArray[i].y);
      }
    }
    
}

#endif
