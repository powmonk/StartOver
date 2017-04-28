#ifndef INPUTS_H
#define INPUTS_H
#include "Arduboy2.h"
#include "globals.h"


void handleInput(){

//  arduboy.pollButtons();

//  (levelX+64)-levelX, 32

  //Go Right
  if(arduboy.pressed(RIGHT_BUTTON)){
//    levelX--;
    playerX++;
    if(playerX >=98){
      levelX--;
      playerX--;
    }
    face = true;
    walk = true;
  }

  //Go Left
  if(arduboy.pressed(LEFT_BUTTON)){
//    levelX++;
    playerX--;
    if(playerX <=20){
      levelX++;
      playerX++;
    }
    face = false;
    walk = true;
  }
  
  //Crouch
  if(arduboy.pressed(DOWN_BUTTON)){
    crouch = true;
  }else{
    crouch = false;
  }
  
  //Jump
  if(arduboy.pressed(B_BUTTON) && !jump && !falling){
    jump = true;
    jumpHeight = floorLevel - 50;
  }

  if(jump && !falling){
    playerY-=6;
    if(playerY<=jumpHeight){
      falling = true;
      jump = false;
    }
  }
  if(falling){
    for(byte i=playerY;i<64;i++){
      if(getSolid(playerX+levelX, i)){
        playerY=i-16;
        floorLevel = i;
        falling = false;
        break;
      }
    }
  }

  arduboy.setCursor(0,0);
  arduboy.drawPixel((levelX+64)-levelX, 32);

  
  //Run
  if(arduboy.pressed(A_BUTTON)){
    run = true;
  }else{
    run = false;
  }
  
}

#endif
