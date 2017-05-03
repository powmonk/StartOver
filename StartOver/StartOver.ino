//#include "ArdBitmap.h"

//#include "bitmaps.h"
#include "environment.h"
#include "inputs.h"
#include "entities.h"
#include "globals.h"




// This function runs once in your game.
// use it for anything that needs to be set only once in your game.
void setup() {
  // initiate arduboy instance
  arduboy.begin();

  // default 60 > saves battery
  arduboy.setFrameRate(45);
}

// our main game loop, this runs once every cycle/frame.
void loop() {

  
  // pause render until it's time for the next frame
  if (!(arduboy.nextFrame()))
    return;

  // first we clear our screen to black
  arduboy.clear();

  stars();

  drawSunMoon();

  clouds();

  drawLevel();

  handleInput();

  if(initTrigger){
    playerInit();
  }

  drawPlayer();

  rain();

//  arduboy.drawPixel(pointX,pointY);
  arduboy.setCursor(0,0);
  //This invocation is sacrosanct
//  arduboy.setCursor(0,8);
//
//  arduboy.print((int)levelX/2.5);

//  arduboy.setCursor(0,8);
//  arduboy.print(pointX-levelX);
//  arduboy.setCursor(24,8);
//  arduboy.print(pointY);
//  arduboy.setCursor(0,16);
//  arduboy.print((pointX-levelX)/8);
//  arduboy.setCursor(16,16);
//  arduboy.print(pointY/8);


  levelX = levelX>0?0:levelX;
  levelX = levelX < 0-(levelWidth*8)+128 ? 0-(levelWidth*8)+128 : levelX;  

  initTrigger = 0;

  // then we finaly we tell the arduboy to display what we just wrote to the display
  arduboy.display();
}
