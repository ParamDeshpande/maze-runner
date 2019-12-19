//DOES PID AND STUFF


#include"../include/commons.h"

#include "../include/controller.h"
#include "../include/actuator.h"


//global variables
double current_x = 0;
double current_vel = 0;
double current_x_acc = 0 ;
double current_yaw = 0 ;
double current_w = 0 ;

//PRIVATE VARS
static float x_Kp = 10;
static float x_Ki = 1e5;
static float x_Kd = 0;
static float w_Kp ;
static float w_Ki ;
static float w_Kd ;

static double vel_pwm = 0;
static double w_pwm = 0;
 
static double vel_Error = 0;
static double w_Error = 0; 

static double x_Error = 0;
static double ang_Error = 0;

#ifndef DEBUG_CONTROLLER 
static double leftMotorPWM = 0;
static double rightMotorPWM = 0;
#endif // DEBUG_CONTROLLER



void main_controller(double desired_vel, double desired_w ){

    
    #ifdef DEBUG_VIA_PRINTF
    pc.printf("delT is %f\n\r", delT);
    #endif // DEBUG
    //current_vel = x_vel;
    //current_w = ang_w;
    
    vel_Error = desired_vel - current_vel;
    w_Error = desired_w - current_w;

    //now clamped. between -100 to 100 value
    if(leftMotorPWM > 100 || leftMotorPWM<(-100) ||  rightMotorPWM > 100 || rightMotorPWM<(-100)){
      //DO NOTHING aka dont integrate passed outer limits
    }
    else{
    //PARAMS WITHIN LIMITS
    x_Error += vel_Error*delT;//Integrating position.
    ang_Error += w_Error*delT;//Integrating angle.
    }

     //x_PD controller.
    vel_pwm = x_Kp*vel_Error +  x_Ki*x_Error +  x_Kd*vel_Error/delT  ;
    w_pwm = w_Kp*w_Error + w_Ki*ang_Error + w_Kd*ang_Error/delT ;
    //RUN NORMALLY
    #ifdef DEBUG_CONTROLLER
    leftMotor.forward(vel_pwm - w_pwm);
    rightMotor.forward(vel_pwm + w_pwm);
    #endif // DEBUG_CONTROLLER


    #ifndef DEBUG_CONTROLLER
    leftMotorPWM = vel_pwm - w_pwm;
    rightMotorPWM = vel_pwm + w_pwm;
    if(leftMotorPWM >0)
      leftMotor.forward(leftMotorPWM);
    else  //If negative
      leftMotor.backward(-leftMotorPWM);
    
    if(rightMotorPWM >0)
      rightMotor.forward(rightMotorPWM);
    else  //If negative
      rightMotor.backward(-rightMotorPWM);

    #endif // DEBUG_CONTROLLER

 
}

void kill_motion(void){
  leftMotor.forward(0);
  rightMotor.forward(0);
}

/*
now = millis();          
  timeChange = (double)(now - lastTime); //* del't' 
  error = position_Error();
  out_Of_Path_Error_Check();
      if((newRPM <75)&&(newRPM > -75)){
      errSum += (error * timeChange);   //*integral is now assumed to be clamped*
      }
      double dErr = (error - lastErr)/timeChange; //* timeChange derivative*
      newRPM = (Kp * error) + (Ki * errSum) + (Kd * dErr);
      lastErr = error;  //*Remember some variables for next time*
      lastTime = now;
      if(newRPM > 75){
        newRPM = 75;
      }
      if(newRPM < -75){
        newRPM = -75;
      }
      return newRPM;
      */