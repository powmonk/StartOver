//#include "ArdBitmap.h"

#include "Arduboy2.h"
#include "bitmaps.h"
#include "weather.h"
#include "inputs.h"
#include "globals.h"
#define PIXEL_SAFE_MODE


int tick = 0;


// This function runs once in your game.
// use it for anything that needs to be set only once in your game.
void setup() {
  // initiate arduboy instance
  arduboy.begin();

  // default 60 > saves battery
  arduboy.setFrameRate(45);
}

short x = 0;
short y = 0;


static const byte levelHeight = 8;
static const byte levelWidth  = sizeof(levelMap[0]);




void drawStreetLight(short lightX){
  arduboy.fillRect((lightX+levelX+29), 25, 3, 3, 1);

  arduboy.drawFastVLine((lightX+levelX)+24, 26,30,0);
  arduboy.drawFastVLine((lightX+levelX)+25, 26,30,1);
  arduboy.drawFastHLine((lightX+levelX)+26, 26,3,1);
  
  if(arduboy.everyXFrames(random(13))){
    arduboy.fillTriangle((lightX+levelX)+19, 56, (lightX+levelX)+54, 56, (lightX+levelX)+30, 25, 1);
  }
  
}

void drawLevel(){
  byte arrayX = levelX / -8;

  short scrollRate = levelX/2.3; 
  int tile1=0;
  int tile2=128;

  tile1 = scrollRate+tile1<= -128?tile1+=256:tile1;
  tile2 = scrollRate+tile2<= -128?tile2+=256:tile2;

  
  if(arduboy.everyXFrames(2)){
    sprites.drawSelfMasked(0,-24,sky, 0);
  }else{
    sprites.drawSelfMasked(0,-24,sky, 1);
  }

//  arduboy.fillRect(0,56,128,16,0);


   arduboy.drawBitmap(scrollRate+tile1,14,skyLine,128,28,0);
   arduboy.drawBitmap(scrollRate+tile2,14,skyLine,128,28,0);


  for(char x=0;x<17;x++){
    for(char y=0;y<8;y++){
      char temp = pgm_read_byte(&(levelMap[y][x+arrayX]));

      switch(temp){
        case 0: break;
        case 1: arduboy.drawBitmap(levelX+((x+arrayX)*8),y*8,floorTile0,8,8,1);break;
        case 2: arduboy.drawBitmap(levelX+((x+arrayX)*8),y*8,floorTile1,8,8,1);break;
        case 3: 
        arduboy.fillRect(levelX+((x+arrayX)*8)+1,y*8+1,6,6,0);
        arduboy.drawBitmap(levelX+((x+arrayX)*8),y*8,coinBox,8,8,1);break;
      }
    }
  }

  drawStreetLight(85);
  drawStreetLight(260);
  drawStreetLight(480);
  drawStreetLight(660);
}

void drawPlayer(){
//  Rect p1Hit = { .x = playerX+1, .y = playerY+7, .width = 4, .height = 9};
  if(!falling && walk){
    if(arduboy.everyXFrames(4)){
      if(frame<3){
        frame++;
      }else{
        frame=0;
        walk = false;
      }
    }
  }
  
  if(face){
    sprites.drawSelfMasked(playerX, playerY, charManFaceRight,frame);
  }else{
    sprites.drawSelfMasked(playerX, playerY, charManFaceLeft, frame);
  }

  if(crouch){
    if(frame<4){
      frame = 4;
    }else if(frame=4){
      frame=5;
    }
  }

}

// our main game loop, this runs once every cycle/frame.
void loop() {
  
  // pause render until it's time for the next frame
  if (!(arduboy.nextFrame()))
    return;

  // first we clear our screen to black
  arduboy.clear();

//  if(arduboy.everyXFrames(2))
    arduboy.fillCircle(levelX/5+160,y+15, 12, 1);

  arduboy.fillCircle(levelX/5+155,y+11, 10, 0);

    cloudX -= 0.0005;
//    if(arduboy.everyXFrames(2)){
      arduboy.drawBitmap(cloudX,-1,cloud,30,10,1);
      arduboy.drawBitmap(cloudX-230,10,cloud,30,10,1);
      arduboy.drawBitmap(cloudX+100,15,cloud,30,10,1);
      arduboy.drawBitmap(cloudX+300,20,cloud,30,10,1);
//    }

  
    if(cloudX<=-30 || cloudX == 0)
      cloudX = 800;

  drawLevel();


  handleInput();



//  droplet(10);

//  if(tick%2==0){
////    arduboy.fillCircle((levelX/3+160)+31, y, 31, WHITE);
//    arduboy.drawBitmap(levelX/3+160,y-30,sun1,64,64,1);
//  }else{
//    arduboy.drawBitmap(levelX/3+160,y-30,sun0,64,64,1);
//  }


  drawPlayer();

  rain(levelX);

  levelX = levelX>0?0:levelX;
  levelX = levelX<0-(levelWidth*8-128)?0-(levelWidth*8-128):levelX;

  tick++;

  // then we finaly we tell the arduboy to display what we just wrote to the display
  arduboy.display();
}
