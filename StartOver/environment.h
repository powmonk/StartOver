#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H
#include "globals.h"
#include "entities.h"




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
      drop[i].x = random(180);
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
       cloudArray[i].x = random(128) * (i+1);
       cloudArray[i].y = 28-random(32);
    }
  }

  for(short i=0;i<cloudCount;i++){
    if(cloudArray[i].x*0.3 < -64){
       cloudArray[i].x = random(256)+512;
       cloudArray[i].y = 28-random(32);
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
        starArray[i].x = random(levelWidth*8); 
        starArray[i].y = random(24)+5; 
      }
    }

    for(byte i=0;i<starCount;i++){
      if(levelX+starArray[i].y > 0 || levelX+starArray[i].y < 128){
        arduboy.drawPixel(levelX/5+starArray[i].x, starArray[i].y);
      }
    }
}

void drawStreetLight(short lightX){
  arduboy.fillRect((lightX+levelX+29), 25, 3, 3, 1);

  arduboy.drawFastVLine((lightX+levelX)+25, 26,30,1);
  arduboy.drawFastHLine((lightX+levelX)+26, 26,3,1);
  
  if(arduboy.everyXFrames(random(13))){
    arduboy.fillTriangle((lightX+levelX)+19, 56, (lightX+levelX)+54, 56, (lightX+levelX)+30, 25, 1);
    arduboy.drawFastVLine((lightX+levelX)+24, 26,30,0);
    arduboy.drawFastVLine((lightX+levelX)+29, 25,3,0);
  }else{
    arduboy.drawFastVLine((lightX+levelX)+24, 26,30,1);
    arduboy.drawFastVLine((lightX+levelX)+29, 25,3,1);
  }
}

void drawSkyline(){  
  
  short scrollRate = levelX/2.5; 
  int tile1=0;
  int tile2=128;

  tile1 = scrollRate+tile1<= -128?tile1+=256:tile1;
  tile2 = scrollRate+tile2<= -128?tile2+=256:tile2;
  
  arduboy.drawBitmap(scrollRate+tile1,14,skyLine,128,28,0);
  arduboy.drawBitmap(scrollRate+tile2,14,skyLine,128,28,0);


}



void drawLevel(){
  byte arrayX = levelX / -8;
  
  if(arduboy.everyXFrames(2)){
    sprites.drawSelfMasked(0,-24,sky, 0);
  }else{
    sprites.drawSelfMasked(0,-24,sky, 1);
  }

  drawSkyline();

  for(char x=0;x<17;x++){
    for(char y=0;y<8;y++){
      char temp = pgm_read_byte(&(levelMap[y][x+arrayX]));

      switch(temp){
        case 0: break;
        case 1: sprites.drawOverwrite(levelX+((x+arrayX)*8),y*8,floorTile0,0);break;
        case 2: sprites.drawOverwrite(levelX+((x+arrayX)*8),y*8,floorTile1,0);break;
        case 3: 
          arduboy.fillRect(levelX+((x+arrayX)*8)+1,y*8+1,6,6,0);
          arduboy.drawBitmap(levelX+((x+arrayX)*8),y*8,coinBox,8,8,1);break;
        case -1: coinRotate(levelX+(x+arrayX)*8,y*8);break;
        
      }
    }
  }

  drawStreetLight(levelWidth*8 / 5 * 1);
  drawStreetLight(levelWidth*8 / 5 * 2);
  drawStreetLight(levelWidth*8 / 5 * 3);
  drawStreetLight(levelWidth*8 / 5 * 4);
}

void drawSunMoon(){
  arduboy.fillCircle(levelX/5+160,15, 12, 1);

  arduboy.fillCircle(levelX/5+154,12, 11, 0);

  if(arduboy.everyXFrames(2)){
    arduboy.fillCircle(levelX/5+160,15, 12, 1);
  }

}


#endif
