#ifndef INPUTS_H
#define INPUTS_H
#include "globals.h"

bool crawl = false;
bool deadBool = false;
unsigned char gameOverY=70;

void handleInput(){  
//  arduboy.print(getSolid((badMan.x-1)-levelX,badMan.y+10));

  


  
if(badMan.alive){  
    if(!getSolid((badMan.x + 1)-levelX, badMan.y+17) && !getSolid((badMan.x + 5)-levelX, badMan.y+17) && !badMan.jumping  || !getSolid((badMan.x+3)-levelX, badMan.y+17) && !badMan.jumping){
      badMan.falling=true;
      badMan.jumping=false;
    }else{
      badMan.falling=false;
    }
  
    if(getSolid((badMan.x + 3)-levelX,badMan.y+9) && badMan.jumping){
      badMan.falling=true;
      badMan.jumping=false;
      if(getCoinBox((badMan.x + 3)-levelX,badMan.y+9)){
        coinBoxAnim((badMan.x + 3)-levelX,badMan.y+9);
      }
      
    }
  
    if(badMan.falling){
        badMan.y += 2;
    }
    if(!getSolid((badMan.x + 6)-levelX, badMan.y+16) && !getSolid((badMan.x)-levelX, badMan.y+16) && !badMan.jumping){
        badMan.y += 1;
    }

  
    if(!badMan.falling && badMan.xSpeed != 0){
      if(arduboy.everyXFrames(4)){
        if(badMan.frame<3){
          badMan.frame++;
        }else{
          if(!badMan.crouching){
            badMan.frame=0;
          }
          badMan.xSpeed = 0;
        }
      }
    }
  
  
    // Move right
    if(arduboy.pressed(RIGHT_BUTTON) && !getSolid((badMan.x+5)-levelX, badMan.y+7) && !getSolid((badMan.x+5)-levelX, badMan.y+10) && !badMan.crouching && badMan.x<levelWidth*8){
  
      if(!arduboy.pressed(A_BUTTON)){
        badMan.xSpeed=1;
      }else{
        badMan.xSpeed=2;
      }
  
      badMan.x+=badMan.xSpeed;
      badMan.xDirection = true;
  
    }
  
    // Move left
    if(arduboy.pressed(LEFT_BUTTON) && !getSolid((badMan.x)-levelX, badMan.y+7) && !getSolid((badMan.x)-levelX, badMan.y+10) && !badMan.crouching && badMan.x>0){
  
      if(!arduboy.pressed(A_BUTTON)){
        badMan.xSpeed=1;
      }else{
        badMan.xSpeed=2;
      }
      
      badMan.x-=badMan.xSpeed;
      badMan.xDirection = false;
  
     
    }
  
    if(arduboy.pressed(UP_BUTTON)){
    }
  
    // Crouching
    if(arduboy.pressed(DOWN_BUTTON) && !badMan.jumping){
      badMan.crouching = true;
      
      if(badMan.frame<4){
        badMan.frame = 4;
      }else if(badMan.frame = 4){
        badMan.frame = 5;  
      }
    }else{
      if(!getSolid((badMan.x+3)-levelX, badMan.y+4)){
        badMan.crouching = false;
      }
      
    }

    //Crawling
    if(badMan.crouching){
      
      if(arduboy.everyXFrames(16)){
        crawl = !crawl;
      }
      if(arduboy.pressed(RIGHT_BUTTON) && !getSolid((badMan.x+5)-levelX, badMan.y+15)  && badMan.x<levelWidth*8 ){
        if(crawl){
          badMan.xSpeed = 1;
          badMan.frame = 7;
        }else{
          badMan.xSpeed = 0;
          badMan.frame = 5;
        }
        badMan.x += badMan.xSpeed;
        badMan.xDirection = true;
  
      }
  
      if(arduboy.pressed(LEFT_BUTTON) && !getSolid((badMan.x)-levelX, badMan.y+15) && badMan.x>0){
        if(crawl){
          badMan.xSpeed = 1;
          badMan.frame = 7;
        }else{
          badMan.xSpeed = 0;
          badMan.frame = 5;
        }
        badMan.x -= badMan.xSpeed;
        badMan.xDirection = false;
  
      }
    }
  
    if(badMan.x>64 && levelX > -levelWidth*8+128){
      levelX   -=badMan.xSpeed;
      badMan.x -=badMan.xSpeed;
    }
    
    //This bit is to check if badMan has collected a coin. I may need to add another parameter to indicated that the state of coins[i].collected should be flipped
//    !getSolid((badMan.x + 1)-levelX, badMan.y+17)
    if(coinCheck((badMan.x-levelX)/8,(badMan.y+13)/8, 1)){
      coinsCollected++;
    }

    arduboy.setCursor(0,0);
    arduboy.print(coinsCollected);

    if(badMan.x<64 && levelX<0){
      levelX   +=badMan.xSpeed;
      badMan.x +=badMan.xSpeed;
    }
    
    if(arduboy.pressed(B_BUTTON) && !badMan.jumping && !badMan.falling && !badMan.crouching && getSolid((badMan.x+3)-levelX, badMan.y+17)){
      badMan.jumping = true;
      badMan.ceiling = badMan.y - 30 > -20?badMan.y - 30:-20;
    }
  
    if(badMan.jumping && !badMan.falling && !badMan.crouching){
      if(badMan.y>badMan.ceiling){
        badMan.y-=3;
      }else{
        badMan.jumping = false;
        badMan.falling = true;
      }
      
    }
  }else{
    if(arduboy.pressed(LEFT_BUTTON) && deadBool == 1 || arduboy.pressed(RIGHT_BUTTON) && deadBool == 0 && gameOverY==10){
      deadBool = !deadBool;
    }
    
    if(arduboy.everyXFrames(2) && gameOverY>10 && badMan.y<5){
      gameOverY--;
    }
    arduboy.drawBitmap(0,gameOverY-1, gameOverBG, 128, 23, 0);
    arduboy.drawBitmap(24,gameOverY+25, yesNoBG, 81, 16, 0);

    arduboy.drawBitmap(81, gameOverY+25,  no, 24, 12, deadBool);
    arduboy.drawBitmap(24, gameOverY+25, yes, 34, 16, !deadBool);
    
    sprites.drawSelfMasked(0,gameOverY-1,gameOver,0);

    if(arduboy.pressed(B_BUTTON) && !deadBool && gameOverY==10){
      levelX=0;
//      badMan.x=20;
//      badMan.y=0;
//      badMan.alive = true; 
//      badMan.xDirection = true;
      coinCount = 0;
      coinsCollected = 0;
      setup();
      playerInit();
      initTrigger = 1;
      gameOverY = 70;
    }
//    else if(arduboy.pressed(B_BUTTON) && deadBool && gameOverY==10){
//      arduboy.clear();
//
//      if(arduboy.everyXFrames(2)){
//        sprites.drawSelfMasked(32,12,dead,0);
//      }else{
//        sprites.drawSelfMasked(32,12,dead,1);
//      }
//        
//    }

    if(badMan.y>-16){
      badMan.y--;
    }
  }
  if(badMan.y+16>=78 || coinsCollected == coinCount){
    badMan.alive = false;
  }

}

#endif
