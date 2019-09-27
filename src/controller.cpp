#include"../include/commons.h"

#include "../include/controller.h"
#include "../include/actuator.h"


Motor rightMotor(rme,rmi1,rmi2);
Motor leftMotor(lme,lmi1,lmi2);


//global variables
double current_x = 0;
double current_vel = 0;
double current_x_acc = 0 ;
double current_yaw = 0 ;
double current_w = 0 ;


//Private variables
static double x_pos = 0;
static double x_vel = 0 ;
static double x_acc = 0 ;
static double ang = 0 ;
static double ang_w = 0 ;


static double vel_pwm = 0;
static double w_pwm = 0;
 
static double vel_Error = 0;
static double w_Error = 0; 

static double x_Error = 0;
static double ang_Error = 0;

#ifdef DEBUG_CONTROLLER
static double leftMotorPWM = 0;
static double rightMotorPWM = 0;
#endif // DEBUG_CONTROLLER

void main_controller(double desired_vel, double desired_w ){

    current_vel = x_vel;
    current_w = ang_w;
    
    vel_Error = desired_vel - current_vel;
    w_Error = desired_w - current_w;

    //needs to be clamped.
    x_Error += vel_Error*delT;//Integrating position.
    ang_Error += w_Error*delT;//Integrating angle.

     //x_PD controller.
    vel_pwm = x_Kp*vel_Error +  x_Ki*x_Error +  x_Kd*vel_Error/delT  ;
    w_pwm = w_Kp*w_Error + w_Ki*ang_Error + w_Kd*ang_Error/delT ;
    //RUN NORMALLY
    #ifndef DEBUG_CONTROLLER
    leftMotor.forward(vel_pwm - w_pwm);
    rightMotor.forward(vel_pwm + w_pwm);
    #endif // DEBUG_CONTROLLER


    #ifdef DEBUG_CONTROLLER
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