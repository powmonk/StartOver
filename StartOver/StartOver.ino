//#include "ArdBitmap.h"

//#include "bitmaps.h"
#include "environment.h"
#include "inputs.h"
#include "globals.h"
#include "entities.h"




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

  drawPlayer();

  rain();

  levelX = levelX>0?0:levelX;
  levelX = levelX < 0-(levelWidth*8)+128 ? 0-(levelWidth*8)+128 : levelX;  

  initTrigger = 0;

  // then we finaly we tell the arduboy to display what we just wrote to the display
  arduboy.display();
}
