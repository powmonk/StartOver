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

short levelX = 0;
char screenTiles[17][8];
char coinFrame = 0;
bool initTrigger = 1;
bool flick = 0;
bool doorOpen = 0;
bool levelComplete = 0;
const byte starCount = 10;
const char showerSize = 15;
const char cloudCount = 3;
const char baddieCount = 5;
short levelWidth = sizeof(levelMap[7]);
char levelHeight = 8;
byte coinCount;
byte boxCount;
signed char wind=0-2;
byte coinsCollected=0;

void playCoinTone(){
//  sound.tone(3087, 100,4120, 250);
}
void playDeadTone(){
//  sound.tone(0100, 200, 0700, 200,100, 200);
}
void playJumpTone(){
//  sound.tone(0100, 200,0700, 50);
}


struct Droplet{
  signed char x;
  signed char y;
};

struct Cloud{
  short x;
  signed char y;
};

struct Star{
  signed char x;
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

struct Box{
  short x;
  char  y;
  bool  hit;
};

struct Coin coins[10];

struct Box boxes[10];

//struct mysteryBox{
//  short x;
//  char  y;
//  bool  collected;
//};
//
//struct Coin coins[50];


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

//bool getSolid(short x, short y){
//  x/=8;y/=8;
//  if(y>7 || y<0){return false;}
//  char temp = pgm_read_byte( & (levelMap[y][x]) );
//  if(temp>0){return true;}
//  return false;
//}


signed char getTileType(short x, signed char y){
  x/=8;y/=8;
  signed char temp = pgm_read_byte( & (levelMap[y][x]) );
  return temp;
}

bool getSolid(short x, signed char y){
  if(y/8>7 || y/8<0){return false;}
  char temp = getTileType(x,y);
  if(temp>0){return true;}
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
  float x;
  short y;
  byte  frame;
  int   ceiling;
  float  xSpeed;
  bool  alive;
  bool  xDirection;
  bool  falling;
  bool  jumping;
  bool  crouching;
  
};

struct Player badMan;
struct Rect   badManHit;
struct Point  badManKill;

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

    badManHit.x = badMan.x+1;
    badManHit.y = badMan.y+9;
    badManHit.width = 4;
    badManHit.width = 7;

    badManKill.x  = badMan.x+3;
    badManKill.y  = badMan.y+16;
    
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
    if(flick)
      if(badMan.xDirection){
        sprites.drawSelfMasked(badMan.x,badMan.y,badManFaceRight, 6);
      }else{
        sprites.drawSelfMasked(badMan.x,badMan.y,badManFaceLeft, 6);
      }
  }
}

// BADDIE STRUCT
struct Baddie{
  float x;
  byte  y;
  bool  alive;
  bool  xDirection;
  bool  falling;
};

struct Baddie goon[baddieCount];
struct Rect goonHit[baddieCount];

void baddieInit(){
  byte xPos = (levelWidth*8)/(baddieCount+1);

  for(byte i=0;i<baddieCount;i++){
    goon[i].x          = xPos * i;
    goon[i].y          = 10;
    goon[i].alive      = 1;
    goon[i].xDirection = 1;
    goon[i].falling    = 1;
  }
}

void drawGoons(){
  for(byte i=0;i<baddieCount;i++){
    if(goon[i].alive){

      goonHit[i].x      = (goon[i].x + 1)+levelX;
      goonHit[i].y      = goon[i].y + 2;
      goonHit[i].width  = 14;
      goonHit[i].height = 8;

      if(arduboy.collide(badManHit, goonHit[i])){
//        badMan.frame = 6;
        badMan.alive = false;
      }

      if(arduboy.collide(badManKill, goonHit[i])){
        badMan.falling=false;
        badMan.jumping=true;
        badMan.ceiling = badMan.y - 30 > -20?badMan.y - 30:-20;
//        badMan.y--;
        playDeadTone();
        goon[i].alive = false;
      }
      
      
      arduboy.drawBitmap(goon[i].x+levelX, goon[i].y, baddieBody, 16, 11, 1);
      if(goon[i].xDirection == 0){
        arduboy.drawBitmap(goon[i].x+levelX, goon[i].y, baddieFaceLeft, 11, 11, 0);
      }else{
        arduboy.drawBitmap(goon[i].x+5+levelX, goon[i].y, baddieFaceRight, 11, 11, 0);
      }
  
      if(!getSolid(goon[i].x+8, goon[i].y+11)){
        goon[i].falling == true;
        goon[i].y++;
      }else{
        goon[i].falling = false;
      }

      if(goon[i].y>64){
        goon[i].alive = false;
      }
  
      if(goon[i].falling == false && goon[i].xDirection){
        if(!getSolid(goon[i].x+17, goon[i].y+10) && !getSolid(goon[i].x+17, goon[i].y)){
          goon[i].x+=0.5;
        }else{
          goon[i].xDirection = !goon[i].xDirection;
        }
      }
  
      if(goon[i].falling == false && !goon[i].xDirection){
        if(!getSolid(goon[i].x-1, goon[i].y+10) && !getSolid(goon[i].x-1, goon[i].y)){
          goon[i].x-=0.5;
        }else{
          goon[i].xDirection = !goon[i].xDirection;
        }
      }
    }else{
      if(goon[i].y<70){
        goon[i].y++;
        arduboy.drawBitmap(goon[i].x+levelX, goon[i].y, baddieBody, 16, 11, 1);
        if(goon[i].xDirection == 0){
          arduboy.drawBitmap(goon[i].x+1+levelX, goon[i].y, baddieFaceLeft, 11, 11, 0);
        }else{
          arduboy.drawBitmap(goon[i].x+5+levelX, goon[i].y, baddieFaceRight, 11, 11, 0);
        }
      }

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
//  x*=8;
//  y*=8;
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

bool boxCheck(int x, char y, bool hit){
  for(int i=0;i<boxCount;i++){
    if(boxes[i].x == x && boxes[i].y == y && boxes[i].hit ==  false){
      if(hit == true){
        boxes[i].hit = true;
      }
      return true;
    }
  }
  return false;
}

#endif

