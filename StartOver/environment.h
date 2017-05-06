#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H
#include "globals.h"
#include "entities.h"

char rainSize;
signed short skyTile0;
signed short skyTile1;


void droplet(byte x, byte y){
  if(arduboy.everyXFrames(2)){
    sprites.drawSelfMasked(x,y, rainDrop,0);
  }else{
    sprites.drawSelfMasked(x,y, rainDrop,1);
  }
}

void rain(){
  rainSize = random(showerSize);

  wind = arduboy.everyXFrames(500)?1-random(2):wind;
  
  if(initTrigger){
     for(byte i=0;i<rainSize;i++){
      drop[i].x = 180-random(260);
      drop[i].y = 64-random(72)-63;
    }
  }

  for(byte i=0;i<rainSize;i++){
    if(drop[i].y > 65 || drop[i].x < -60 || drop[i].x > 180){
      drop[i].y = -32;
      drop[i].x = random(180);
    }else{
      drop[i].y+=3;
      drop[i].x = wind != 0?drop[i].x+=wind:drop[i].x;
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
        arduboy.drawPixel(levelX/8+starArray[i].x, starArray[i].y);
      }
    }
}

void drawStreetLight(short lightX){
  arduboy.fillRect((lightX+levelX+29), 24, 5, 4, 1);
  arduboy.fillRect((lightX+levelX+30), 22, 3, 3, 1);

  arduboy.drawFastVLine((lightX+levelX)+25, 26,30,1);
  arduboy.drawFastHLine((lightX+levelX)+26, 26,3,1);
  
  if(arduboy.everyXFrames(random(13))){
    arduboy.fillTriangle((lightX+levelX)+19, 56, (lightX+levelX)+54, 56, (lightX+levelX)+30, 22, 1);
//    arduboy.fillTriangle((lightX+levelX)+19, 56, (lightX+levelX)+54, 56, (lightX+levelX)+30, 25, 1);
    arduboy.drawFastVLine((lightX+levelX)+24, 26,30,0);
    arduboy.drawFastVLine((lightX+levelX)+29, 24,4,0);
  }else{
//    arduboy.drawBitmap(lightX+levelX+16, 29,  castLight, 33, 33, 1);
    arduboy.drawFastVLine((lightX+levelX)+24, 26,30,1);
    arduboy.drawFastVLine((lightX+levelX)+29, 25,3,1);
  }
}

void drawSkyline(){  
  if(initTrigger){
      skyTile0 = 0;
      skyTile0 = -128;
  }
  
  short scrollRate = levelX/2.5; 

  if(scrollRate < skyTile0-128){
    skyTile0-=256;
  }
  if(scrollRate < skyTile1-128){
    skyTile1-=256;
  }
  if(scrollRate > skyTile0+128){
    skyTile0+=256;
  }
  if(scrollRate > skyTile1+128){
    skyTile1+=256;
  }

  if(skyTile0<-128){
    arduboy.drawBitmap(scrollRate-skyTile0,14,skyLine,128,28,0);
  }else{
    arduboy.drawBitmap(scrollRate-skyTile0,14,skyLineIn,128,28,0);
  }


  if(skyTile1<-128){
    arduboy.drawBitmap(scrollRate-skyTile1,14,skyLine,128,28,0);
  }else{
    arduboy.drawBitmap(scrollRate-skyTile1,14,skyLineTown,128,28,0);
  }
if(arduboy.everyXFrames(2)){
  arduboy.drawBitmap(scrollRate-skyTile0,40,screenDither, 128, 28, 1);
  arduboy.drawBitmap(scrollRate-skyTile1,40,screenDither, 128, 28, 1);
}
//else{
//  if(arduboy.everyXFrames(random(3))){
//    arduboy.drawBitmap(scrollRate-(skyTile0),40,screenDither, 128, 28, 1);
//    arduboy.drawBitmap(scrollRate-(skyTile1),40,screenDither, 128, 28, 1);
//  }
//}


}



const int countCoins(){
  for(short x=0;x<levelWidth;x++){
    for(char y=0;y<levelHeight;y++){
      char temp = pgm_read_byte(&(levelMap[y][x]));
      if(temp == -1){
        coinCount++;
      }
    }
  }
  
  byte tmpCount = coinCount;
  for(short x=levelWidth;x>-1;x--){
    for(char y=levelHeight;y>-1;y--){
      char temp = pgm_read_byte(&(levelMap[y][x]));
      if(temp == -1){
        tmpCount--;
        coins[tmpCount].x=x;
        coins[tmpCount].y=y;
        coins[tmpCount].collected=false;
      }
    }
  }
}



void drawLevel(){
  signed short arrayX = levelX / -8;

  if(arduboy.everyXFrames(2)){
    sprites.drawSelfMasked(0,-22,sky, 0);
  }else{
    sprites.drawSelfMasked(0,-22,sky, 1);
  }

  drawSkyline();

//  if(arduboy.everyXFrames(2)){
//      arduboy.drawBitmap(0,46,screenDither, 128, 28, 1);

//  }

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
        case -1: 
          if(coinCheck(x+arrayX,y,0)){
            coinRotate(levelX+(x+arrayX)*8,y*8);
          };
          break;
        
      }
    }
  }
  drawStreetLight(levelWidth*8 / 10 * 1);
  drawStreetLight(levelWidth*8 / 10 * 2);
  drawStreetLight(levelWidth*8 / 10 * 3);
  drawStreetLight(levelWidth*8 / 10 * 4);
  drawStreetLight(levelWidth*8 / 10 * 5);
  drawStreetLight(levelWidth*8 / 10 * 6);
  drawStreetLight(levelWidth*8 / 10 * 7);
  drawStreetLight(levelWidth*8 / 10 * 8);
  drawStreetLight(levelWidth*8 / 10 * 9);
}

void drawSunMoon(){
  arduboy.fillCircle((levelX/8)+260,15, 12, 1);

  arduboy.fillCircle((levelX/8)+254,12, 11, 0);

  if(arduboy.everyXFrames(2)){
    arduboy.fillCircle((levelX/8)+260,15, 12, 1);
  }

}


#endif
