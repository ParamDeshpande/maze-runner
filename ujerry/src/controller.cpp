#include"../include/main.h"
#include"../include/port.h"
#include"../include/constants.h"

#include "../include/controller.h"
#include "../include/actuator.h"


Motor rightMotor(rme,rmi1,rmi2);
Motor leftMotor(lme,lmi1,lmi2);



//Private variables
double x = 0;
double x_vel = 0 ;
double x_acc = 0 ;
double ang = 0 ;
double ang_w = 0 ;


double vel_pwm = 0;
double w_pwm = 0;

double vel_Error = 0;
double w_Error = 0; 

double x_Error = 0;
double ang_Error = 0;


//global variables
double current_x = 0;
double current_vel = 0;
double current_x_acc = 0 ;
double current_yaw = 0 ;
double current_w = 0 ;

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
    
    leftMotor.forward(vel_pwm - w_pwm);
    rightMotor.forward(vel_pwm + w_pwm);

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