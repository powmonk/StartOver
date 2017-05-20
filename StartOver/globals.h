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
short levelWidth = sizeof(levelMap0[7]);
char levelHeight = 8;
byte coinCount;
byte boxCount;
signed char wind=0-2;
byte coinsCollected=0;
byte totalCoins;
byte levelCount = 0;
byte bubbleInitSize = 18;
const byte MAX_BUBS = 10;

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

struct Spear{
  byte x;
  float y;
  bool alive;
  struct Rect spear;
};

struct Bubble{
  byte x;
  byte y;
  byte bubbleSize;
  bool xDirection;
  bool yDirection;
  bool alive;
  struct Rect hitBox;
};

struct Bubble bubbles[MAX_BUBS];


void newBubble(byte arrayPos, byte bubbleSize, bool xDir, byte x, byte y){
  bubbles[arrayPos].bubbleSize  = bubbleSize;
  bubbles[arrayPos].xDirection  = xDir;
  bubbles[arrayPos].yDirection  = 1;
  bubbles[arrayPos].alive       = 1;
  bubbles[arrayPos].x           = x;
  bubbles[arrayPos].y           = y;
}

void bubbleInit(){
  for(byte i=0;i<MAX_BUBS;i++){
    bubbles[i].alive = false;
  }
  newBubble(0, bubbleInitSize, 1, 64, 32);
}


//void drawShape(){
//  int size = 10;
//  
//  if(x==128-size){
//    flipX=false;
//  }else if(x==0+size){
//    flipX=true;
//  }
//  x = flipX?x+=1:x-=1;
//
//  if(y==48-size){
//    flipY=false;
//  }else if(y==0+size){
//    flipY=true;
//  }
//  y = flipY?y+=1:y-=1;
//  
//  arduboy.fillCircle(x, y, size, BLACK);
//  arduboy.drawCircle(x, y, size, WHITE);
//  arduboy.fillCircle(x-2,y-2, size/2, WHITE);
//  arduboy.fillCircle(x,y, size/1.5, BLACK);
//  if(flick){arduboy.fillCircle(x, y, size, WHITE);}
//
//
//}


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

signed char getTileType(short x, signed char y, bool divide){
  if(divide){x/=8;y/=8;}
  char temp;
//        temp = pgm_read_byte(&(levelMap0[y][x+arrayX]));

  switch(levelCount%2){
    case 0: temp = pgm_read_byte(&(levelMap0[y][x]));break;
    default: temp = pgm_read_byte(&(levelMap1[y][x]));break;
  }
  return temp;
}

bool getSolid(short x, signed char y){
  if(y/8>7 || y/8<0){return false;}
  if(x<1 || x>(levelWidth*8)){return true;}

  char temp = getTileType(x,y, 1);
  if(temp>0){return true;}
  return false;
}

bool getCoinBox(short x, byte y){
  char temp = getTileType(x, y, 1);

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
  bool  jumpCooldown;
  bool  crouching;
};

struct Player badMan;
struct Rect   badManHit;
struct Point  badManKill;

void playerInit(){
  badMan.x             = 20;
  badMan.y             = 0;
  badMan.frame         = 0;
  badMan.xDirection    = 1;
  badMan.falling       = true;
  badMan.jumping       = false;
  badMan.jumpCooldown  = false;
  badMan.alive         = true;
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
          arduboy.drawBitmap(goon[i].x+2+levelX, goon[i].y, baddieFaceLeftDead, 11, 11, 0);
        }else{
          arduboy.drawBitmap(goon[i].x+3+levelX, goon[i].y, baddieFaceRightDead, 11, 11, 0);
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

struct Spear BMSpear;

void spearInit(){
  BMSpear.alive = true;
  BMSpear.x = badMan.x +3;
  BMSpear.y = badMan.y +8;

}

void launchSpear(){
  if(BMSpear.alive){
    BMSpear.y-=1.3;
    sprites.drawSelfMasked(BMSpear.x-2,BMSpear.y, spearTip, 0);
    BMSpear.spear.x      = BMSpear.x-1;
    BMSpear.spear.y      = BMSpear.y;
    BMSpear.spear.width  = 1;
    BMSpear.spear.height = 56;
    for(byte i=7;i<56;i+=8){
      sprites.drawSelfMasked(BMSpear.x-1,BMSpear.y+i, rope, 0);
    }
  }

  if(BMSpear.y<=-4){
    BMSpear.alive = false;
    BMSpear.spear.y = 64;

  }
}

void drawBubbles(){
  for(byte i = 0;i<MAX_BUBS;i++){
    byte radius = bubbles[i].bubbleSize;

    if(bubbles[i].alive == true){
      arduboy.fillCircle(bubbles[i].x, bubbles[i].y, bubbles[i].bubbleSize, BLACK);
      arduboy.fillCircle(bubbles[i].x, bubbles[i].y, bubbles[i].bubbleSize/2, BLACK);
      arduboy.drawCircle(bubbles[i].x, bubbles[i].y, bubbles[i].bubbleSize, WHITE);
      arduboy.fillCircle(bubbles[i].x-2,bubbles[i].y-2, bubbles[i].bubbleSize/2, WHITE);
      arduboy.fillCircle(bubbles[i].x,bubbles[i].y, bubbles[i].bubbleSize/1.5, BLACK);
//      if(!flick){arduboy.fillCircle(bubbles[i].x, bubbles[i].y, bubbles[i].bubbleSize, WHITE);}
      
//      arduboy.fillRect(bubbles[i].x-radius/1.4,bubbles[i].y-radius/1.4, bubbles[i].bubbleSize*1.58, bubbles[i].bubbleSize*1.58, WHITE);
      bubbles[i].hitBox.x      = bubbles[i].x-radius/1.4,
      bubbles[i].hitBox.y      = bubbles[i].y-radius/1.4,
      bubbles[i].hitBox.width  = bubbles[i].bubbleSize*1.58, 
      bubbles[i].hitBox.height = bubbles[i].bubbleSize*1.58;
    }

    if(bubbles[i].xDirection){
      bubbles[i].x++;
    }else{
      bubbles[i].x--;
    }

    if(bubbles[i].yDirection){
      bubbles[i].y++;
    }else{
      bubbles[i].y--;
    }


    if(bubbles[i].x >= 128 - radius || bubbles[i].x <= radius){
      bubbles[i].xDirection=!bubbles[i].xDirection;
    }

    if(bubbles[i].y >= 56 - radius || bubbles[i].y <= radius){
      bubbles[i].yDirection=!bubbles[i].yDirection;
    }

    if(arduboy.collide(bubbles[i].hitBox, badManHit) && bubbles[i].alive){
      badMan.alive = false;
    }

    if(arduboy.collide(bubbles[i].hitBox, BMSpear.spear) && bubbles[i].alive){
      byte loopCount=0;
      for(byte j = 0; j<MAX_BUBS;j++){
        if(!bubbles[j].alive){
          if(bubbles[i].bubbleSize /1.7 > 2 && loopCount<2){
            newBubble(j, bubbles[i].bubbleSize /1.7, loopCount, bubbles[i].x, bubbles[i].y);
            loopCount++;
          }          
        }
      }
//      newBubble(byte arrayPos, byte bubbleSize, bool xDir, byte x, byte y)
      bubbles[i].alive = false;
      BMSpear.alive = false;
      BMSpear.spear.y = 64;
    }
    
  }
//  arduboy.setCursor(0,0);
//  arduboy.print(sizeof(bubbles));
}

boolean noBubbles(){
  for(byte j = 0; j<MAX_BUBS;j++){
    if(bubbles[j].alive)
      return false;
  }

  return true;
}


#endif

