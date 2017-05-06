#ifndef GLOBALS_H
#define GLOBALS_H



#include <Arduboy2.h>
#include <ArduboyTones.h>
//#include <ArduboyTonesPitches.h>
//#include <list>
#include "entities.h"
#include "environment.h"
#include "bitmaps.h"

//#define VOLUME_IN_TONE 0
#define PIXEL_SAFE_MODE



Arduboy2 arduboy;
ArduboyTones sound(arduboy.audio.enabled);
Sprites sprites;

long levelX = 0;
char screenTiles[17][8];
char coinFrame = 0;
bool initTrigger = 1;
const byte starCount = 50;
const char showerSize = 25;
const char cloudCount = 3;
short levelWidth = sizeof(levelMap[7]);
char levelHeight = 8;
int coinCount;
signed char wind=0-2;
byte coinsCollected=0;



struct Droplet{
  signed short x;
  signed char y;
};

struct Cloud{
  short x;
  signed char y;
};

struct Star{
  short x;
  signed char y;
};


struct Background{
  signed short x;
};

struct Coin{
  short x;
  char  y;
  bool  collected;
};

struct Coin coins[50];


//struct Coin coins[];

//void declareCoins(byte i){
//  struct Coin coins[i];
//}
struct Droplet drop[showerSize];
struct Cloud cloudArray[cloudCount];
struct Star starArray[starCount];
struct Background skyline;

// This method returns a boolean solid/not solid for the foreground
// and takes x/y co-ords as parameters.

bool getSolid(short x, short y){
  x/=8;
  y/=8;

  if(y>7 || y<0){
    return false;
  }


  char temp = pgm_read_byte( & (levelMap[y][x]) );

  if(temp>0){
    return true;
  }
  return false;
}


bool getCoinBox(short x, short y){
  x/=8;
  y/=8;

  char temp = pgm_read_byte( & (levelMap[y][x]) );

  if(temp==3){
    return true;
  }
  return false;
}


//PLAYER STRUCT

struct Player{
  short x;
  short y;
  byte frame;
  int ceiling;
  char xSpeed;
  bool alive;
  bool xDirection;
  bool falling;
  bool jumping;
  bool crouching;
  
};

struct Player badMan;

void playerInit(){
  badMan.x          = 20;
  badMan.y          = 0;
  badMan.frame      = 0;
  badMan.xDirection = 1;
  badMan.falling    = true;
  badMan.jumping    = false;
  badMan.alive      = true;
}

void drawPlayer(){
  if(badMan.alive){
    if(badMan.frame<5){
      arduboy.drawFastHLine(badMan.x+1,badMan.y+9,4,0);
      arduboy.drawFastHLine(badMan.x+1,badMan.y+10,4,0);
    }
    
    if(badMan.frame==5){
      arduboy.drawFastHLine(badMan.x+1,badMan.y+13,4,0);
    }

    if(badMan.frame==7){
      arduboy.drawFastHLine(badMan.x+badMan.xDirection*2,badMan.y+13,4,0);
    }


    

    if(badMan.xDirection){
      sprites.drawSelfMasked(badMan.x,badMan.y,badManFaceRight, badMan.frame);
    }else{
      sprites.drawSelfMasked(badMan.x,badMan.y,badManFaceLeft, badMan.frame);
    }
  }else{
    if(arduboy.everyXFrames(2)){
      sprites.drawSelfMasked(badMan.x,badMan.y,badManFaceRight, 0);
    }
  }
}

void coinRotate(signed char x, signed char y){
  
  sprites.drawSelfMasked(x+1,y-2,coinAnim,coinFrame);
  
  if(arduboy.everyXFrames(10)){
    coinFrame++;
  }
  if(coinFrame >= 3){
    coinFrame = 0;
  }

}

///

void coinBoxAnim(char x, char y){
  bool done = false;
  
//  while(!done){
//    if(!getSolid(x,y)){
//      x++;
//      done = true;
//      break;
//    }
//    x--;
//  }
//
//  done = false;
//  
//  while(!done){
//    if(!getSolid(x,y)){
//      y-=17;
//      done = true;
//      break;
//    }
//    y--;
//  }
  x/=8;
  y/=8;
  x*=8;
  y*=8;
  coinRotate(x+64, y-8);  
  
}

bool coinCheck(int x, char y, bool collect){
  for(int i=0;i<coinCount;i++){
    if(coins[i].x == x && coins[i].y == y && coins[i].collected ==  false){
      if(collect == true){
        coins[i].collected = true;
      }
      return true;
    }
  }
  return false;
}

void playCoinTone(){
  sound.tone(3087, 100,4120, 250);
//  sound.tone(1000);
}
void playDeadTone(){
  sound.tone(0100, 200, 0700, 200,100, 200);
//  playDeadTone();
//  sound.tone(1000);
}
void playJumpTone(){
  sound.tone(0100, 200,0700, 50);
//  sound.tone(1000);
}

    

#endif

