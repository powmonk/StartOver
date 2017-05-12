#ifndef INPUTS_H
#define INPUTS_H
#include "globals.h"

bool crawl = false;
bool deadBool = false;
unsigned char gameOverY=70;

void handleInput(){  
//  arduboy.print(getSolid((badMan.x-1)-levelX,badMan.y+10));

  


  
if(badMan.alive && !levelComplete){  
    if(!getSolid((badMan.x + 1)-levelX, badMan.y+17) && !getSolid((badMan.x + 5)-levelX, badMan.y+17) && !badMan.jumping  || !getSolid((badMan.x+3)-levelX, badMan.y+17) && !badMan.jumping){
      badMan.falling=true;
      badMan.jumping=false;
    }else{
      badMan.falling=false;
    }
  
    if(getSolid((badMan.x + 3)-levelX,badMan.y+9) && badMan.jumping){
      if(boxCheck(((badMan.x + 3)-levelX)/8, (badMan.y+9)/8, 1)){
        coinsCollected++;  
        playCoinTone();
        coinBoxAnim(((badMan.x + 3)-levelX)/8, (badMan.y+9)/8);
      }
      badMan.falling=true;
      badMan.jumping=false;
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
          if(!badMan.crouching && badMan.alive){
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
    
    // UP button. Doesn't really do anything too specific. Goes through doors.
    if(arduboy.pressed(UP_BUTTON)){
      badMan.crouching = false;
      if(badMan.frame == 5 && badMan.alive){
        badMan.frame = 0;
      }
      if(doorOpen == true && getTileType(badMan.x+3-levelX, badMan.y+5) == -3){
        levelComplete = true;
      }
    }

    if(arduboy.pressed(UP_BUTTON) && doorOpen == true && getTileType(badMan.x+3-levelX, badMan.y+5) == -3){
              levelComplete = true;

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
        if(badMan.frame == 5 && badMan.alive){
          badMan.frame = 0;
        }
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
    
    //This bit is to check if badMan has collected a coin
//    !getSolid((badMan.x + 1)-levelX, badMan.y+17)
    if(coinCheck((badMan.x-levelX)/8,(badMan.y+13)/8, 1)){
      coinsCollected++;
      playCoinTone();
    }

//    sprites.drawSelfMasked(0,1,coinAnim, 1);
//    arduboy.setCursor(6,0);
//    arduboy.print("=");
    arduboy.setCursor(124,1);
    arduboy.print(coinsCollected);
    coinRotate(116,2);

//    arduboy.print(boxCount);

    if(badMan.x<64 && levelX<0){
      levelX   +=badMan.xSpeed;
      badMan.x +=badMan.xSpeed;
    }
    
    if(arduboy.pressed(B_BUTTON) && !badMan.jumpCooldown && !badMan.jumping && !badMan.falling && !badMan.crouching && getSolid((badMan.x+3)-levelX, badMan.y+17)){
      badMan.jumping = true;
      badMan.jumpCooldown = true;
      playJumpTone();
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

    if(arduboy.justReleased(B_BUTTON)){
      badMan.jumpCooldown = false;
      
    }
  }else{
    if(!badMan.alive){
      if(arduboy.pressed(LEFT_BUTTON) && deadBool == 1 || arduboy.pressed(RIGHT_BUTTON) && deadBool == 0 && gameOverY==10){
        deadBool = !deadBool;
      }
      
      if(gameOverY>10 && badMan.y<5){
        gameOverY--;
      }
      arduboy.drawBitmap(0,gameOverY-1, gameOverBG, 128, 23, 0);
      arduboy.drawBitmap(24,gameOverY+25, yesNoBG, 81, 16, 0);
  
      arduboy.drawBitmap(81, gameOverY+25,  no, 24, 12, deadBool);
      arduboy.drawBitmap(24, gameOverY+25, yes, 34, 16, !deadBool);
      
      sprites.drawSelfMasked(0,gameOverY-1,gameOver,0);
  
      if(arduboy.pressed(B_BUTTON) && !deadBool && gameOverY==10){
        gameOverY = 70;
        setup();
        initTrigger = 1;
      }
  
      if(badMan.y>-16){
        badMan.y--;
      }
    }
    if(levelComplete){
      if(gameOverY>18){
        gameOverY--;
      }else{
        if(arduboy.pressed(B_BUTTON) || arduboy.pressed(A_BUTTON)){
          levelComplete = 0;
          levelCount++;
          gameOverY = 70;
          setup();
          initTrigger = 1;
        }
      }
      arduboy.drawBitmap(10,gameOverY, wellDoneBG, 111, 16, 0);
      arduboy.drawBitmap(10,gameOverY, wellDone,   111, 16, 1);
    }
  }
  if(badMan.y+16>=78 || getTileType((badMan.x+3)-levelX,badMan.y+16) == 4){
//    badMan.frame = 6;
    badMan.alive = false;
    playDeadTone();
  }

  if(coinsCollected == coinCount ){
    doorOpen = 1;
  }

}

#endif
