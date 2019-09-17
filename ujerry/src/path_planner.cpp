#include "../include/commons.h"

#include "../include/path_planner.h"
#include "../include/IR.h"
#include "../include/controller.h"

bool check_left_wall() {
  if ((side_left_IR > hasLeftWall)){
    return TRUE;
  }
  return FALSE;
}
bool check_right_wall() {
  if ((side_right_IR > hasRightWall)){//need to adjust value  
    
    return TRUE;
  }
  return FALSE;
}
bool check_front_wall() {
  if ((front_right_IR > hasFrontWall && front_left_IR > hasFrontWall) ){ 

    return TRUE;
  }
  return FALSE;
}/*
void path_2_glory(void){
  
  short leftWall = check_left_wall();
  short rightWall = check_right_wall();
  

  if ((front_right_IR > PIDSTOP && front_left_IR > PIDSTOP)) //prevents mouse from crashing into wall due to errors.
  {                                        //if this is called, its a BAD sign....
    main_controller(0,0);//STOP EVERYTHING
    frontwallflag = 1;
    return;
  }

  if(leftWall && rightWall) {
  //    Serial.println("in the middle"); 
    errorP = rightSensor - leftSensor - newOffset;  //how far away from middle we are
    errorD = errorP - oldErrorP;                  //change in error  
  }
  else if(leftWall){
//    Serial.println("only left wall"); 
    errorP = .15 * (LEFTPID - leftSensor);      // old: 200; the error away from center with only a left wall
    errorD = errorP - oldErrorP;           // change in error
  }
  // sensor only reads in right wall
  else if(rightWall){
//    Serial.println("only right wall"); 
    errorP = .15 * (rightSensor - RIGHTPID);      //old: 350 the error away from center with only a right wall
    errorD = errorP - oldErrorP;           // change in error
  }
  
}*/

