#ifndef INPUTS_H
#define INPUTS_H
#include "globals.h"

bool crawl = false;
unsigned char gameOverY=70;

void handleInput(){  
//  arduboy.print(getSolid((badMan.x-1)-levelX,badMan.y+10));
  arduboy.print(badMan.alive);
  
  
if(badMan.alive){  
    if(!getSolid((badMan.x + 1)-levelX, badMan.y+17) && !getSolid((badMan.x + 5)-levelX, badMan.y+17) && !badMan.jumping){
      badMan.falling=true;
  //    badMan.jumping=false;
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
      badMan.y+=2;
    }
  
    if(!badMan.falling && badMan.xSpeed != 0){
      if(arduboy.everyXFrames(4)){
        if(badMan.frame<3){
          badMan.frame++;
        }else{
          badMan.frame=0;
          badMan.xSpeed = 0;
        }
      }
    }
  
  
    // Move right
    if(arduboy.pressed(RIGHT_BUTTON) && !getSolid((badMan.x+5)-levelX, badMan.y+10)  && !badMan.crouching && badMan.x<levelWidth*8){
  
      if(!arduboy.pressed(A_BUTTON)){
        badMan.xSpeed=1;
      }else{
        badMan.xSpeed=2;
      }
  
      badMan.x+=badMan.xSpeed;
      badMan.xDirection = true;
  
    }
  
    // Move left
    if(arduboy.pressed(LEFT_BUTTON) && !getSolid((badMan.x)-levelX, badMan.y+10) && !badMan.crouching && badMan.x>0){
  
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
  
      
      
    }else{
      badMan.crouching = false;
      
    }
  
    if(badMan.x>64 && levelX > -levelWidth*8+128){
      levelX   -=badMan.xSpeed;
      badMan.x -=badMan.xSpeed;
    }
  
    arduboy.setCursor(0,8);
    arduboy.print(0-(levelWidth*8)-64);
  
  
   if(badMan.x<64 && levelX<0){
      levelX   +=badMan.xSpeed;
      badMan.x +=badMan.xSpeed;
    }
    
    if(arduboy.pressed(B_BUTTON) && !badMan.jumping && !badMan.falling && !badMan.crouching){
      badMan.jumping = true;
      badMan.ceiling = badMan.y - 30 > -20?badMan.y - 30:-20;
    }
  
    if(badMan.jumping){
      if(badMan.y>badMan.ceiling){
        badMan.y-=3;
      }else{
        badMan.jumping = false;
        badMan.falling = true;
      }
      
    }
  }else{
    if(arduboy.everyXFrames(2) && gameOverY>20 && badMan.y<5){
      gameOverY--;
    }
    arduboy.drawBitmap(0,gameOverY-3, gameOverBG, 128, 23, 0);
    sprites.drawSelfMasked(4,gameOverY,gameOver,0);
    badMan.y--;
  }
  if(badMan.y>=64-16){
    badMan.alive = false;
  }

}

#endif
