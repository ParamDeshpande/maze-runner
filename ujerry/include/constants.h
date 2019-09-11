#ifndef CONSTANTS_H
#define CONSTANTS_H

#define angleSumFiftyK 12000UL //DO edit after analysis 50K samples.


#define delT 1UL

//Change these values
//PID GAINS 
#define x_Kp 0
#define x_Ki 0
#define x_Kd 0
#define w_Kp 0
#define w_Ki 0
#define w_Kd 0

#define constVel_speed 0UL
#define pivot_w 0UL
#define pivot_turn_Speed 0UL

extern double desired_vel ;
extern double desired_x_acc ;
extern double desired_w  ;


extern double current_x;
extern double current_vel;
extern double current_x_acc ;

extern double current_yaw ;
extern double current_w;

#ifdef DEBUG


#endif
//State variables for kalman

  // Initialize function 'kalman6d' input arguments.
  // Initialize function input argument 'U'.
  // Initialize function input argument 'Z'.
  // Initialize function input argument 'XHat_Prev'.
  // Initialize function input argument 'cov_Prev'.
  // Initialize function input argument 'uncertVect'.
  // Initialize function input argument 'noiseVect'.
  // Call the entry-point 'kalman6d'.

    // two inputs x and w 
 extern double inputs[2];

    //lenc dist , renc dist , accx(meters travelled), <yaw_gyro_WC_rads , <yaw_Acc , <yawMag_rads  
 extern  double measurements[6] ;//Write iniitial values of sall sensors here

    //State variable x, xDOT , xDOTDOT , w , wDOT
 extern  double state_Vector_Old[5] ;

    //Shit that takes care of itself init as zero.
 extern  double cov_Matrix_Old[25] ;

    //Write uncertainty variances of State_variable
    //*PLEASE CHANGE THESE VALUES*
 extern  double uncertainty_Vector[5] ;
    
    // Write uncertainty variances of measurements
    //*PLEASE CHANGE THESE VALUES*
  extern double noise_Vector[6];
    

    //Updated / current state estimates
  extern double state_Vector_Current[5];

    //shit that will supposedly take care of itself.
 extern  double cov_Matrix_Current[25] ;


extern int IR_readings[3][2];
extern int irArray[4][4];

//*/
#endif // !CONSTANTS_H