#ifndef CONSTANTS_H
#define CONSTANTS_H

//STARTING WITH UTILS AKA
//BLUETOOTH

// Serial bt(PA_11, PA_12);  // This one works
// Serial pc(USBTX, USBRX); 

extern Serial pc;


//#define DEBUG

#define HIGH 1
#define LOW 0

#define TRUE true
#define FALSE false

extern float front_left_IR  ;  
extern float front_right_IR ;  
extern float diag_left_IR   ;  
extern float diag_right_IR  ;  
extern float side_left_IR   ;  
extern float side_right_IR  ;  


#define MAX_W_ACLKWISE -4*M_PI //rads per sec
#define MAX_W_CLKWISE 4*M_PI //rads per sec


//Super important dont change UL.

#define FILLARRAY(a,n) a[0]=n, memcpy( ((char*)a)+sizeof(a[0]), a, sizeof(a)-sizeof(a[0]) );


#define D_2_RAD(degrees) degrees*M_PI/180.0f
#define RADS_2_D(rads) rads*180.0f/M_PI

#define angleSumFiftyK 0   //14.671313 //DO edit after analysis 50K samples.

#define minimum_battery_voltage 7

#define delT 1e-3


//constants for encoder to turn right/left/180
#define TURN_RIGHT_COUNT 1900      //1900 for fake maze
#define TURN_LEFT_COUNT 1850      //1850 for fake maze +/- 50
#define TURN_AROUND_COUNT 3000    //3000 for fake maze
#define ONECELL 0.25//  M          //7200 for fake maze


// infinity values

//
//
//
//
//
//
//
//

//constants for wall sensing left/right/front
#define hasLeftWall 0.7//% //190 for fake maze
#define hasRightWall 10.0 //  //220 for fake maze; 120 for real maze
#define hasFrontWall 7  //300 for fake maze; 
//IR THRESHOLD min dist before stopping
#define PIDSTOP 600    //600 for fake maze;
#define LEFTPID 200    //200 for fake maze
#define RIGHTPID 350  //350 for fake maze
//maybe define new ones for wall sensing for the floodfill


//MOTOR


//Change these values
//PID GAINS 
#define x_Kp 0UL
#define x_Ki 0UL
#define x_Kd 0UL
#define w_Kp 0UL
#define w_Ki 0UL
#define w_Kd 0UL

//Kalman Parameters
#define calc_var_x 1000UL
#define calc_var_vel 1000UL
#define calc_var_x_acc 1000UL
#define calc_var_yaw D_2_RAD(0.05)
#define calc_var_w 1000UL

#define measure_var_l_enc 1000UL
#define measure_var_r_enc 1000UL
#define measure_var_accelX 1000UL
#define measure_var_yawGyro D_2_RAD(0.05)
#define measure_var_yawAccel D_2_RAD(500000)
#define measure_var_yawMag D_2_RAD(1500000)

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

extern double left_enc_dist ;
extern double right_enc_dist;

extern double accelX;
extern double yawGyro_rads;
extern double yawAccelero_rads;
  
extern double yawMag_rads;
//ADDED A GYRO ACC IN MEASUREMENT SET TO ZERO

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
 extern double inputs[2]; //aka U

    //lenc dist , renc dist , accx(meters travelled), <yaw_gyro_WC_rads , <yaw_Acc , <yawMag_rads  
 extern  double measurements[6] ;//Write iniitial values of sall sensors here

    //State variable x, xDOT , xDOTDOT , w , wDOT
 extern  double previous_states[5] ;

    //Shit that takes care of itself init as zero.
 extern  double cov_Matrix_Old[25] ;

    //Write uncertainty variances of State_variable
    //*PLEASE CHANGE THESE VALUES*
 extern  double uncertainty_Vect[5] ;
    
    // Write uncertainty variances of measurements
    //*PLEASE CHANGE THESE VALUES*
  extern double noise_Vector[6];
    

    //Updated / current state estimates
  extern double current_states[5];

    //shit that will supposedly take care of itself.
 extern  double cov_Matrix_Current[25] ;


extern int IR_readings[3][2];
extern int irArray[4][4];

//FLOOD FILL / MAZE SOLVING


//Define Driving Direction
#define BACKWARD 0
#define FORWARD 1


// Directions
#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

extern short frontwallflag; //global flag that is set when PID finds a front wall
extern short noWall;  //global flag to detect scenario with no walls
extern struct Maze * my_maze; //maze that keeps track of flood fill values and walls
extern struct Stack * my_stack; //stack used for flood fill
extern struct Node * temp; //node used for in-between start->goal, goal->start transition
extern short found_dest; //flag if goal is reached
extern short direction; //direction that the mouse is facing
extern short x, y; //current coordinates of the mouse in the maze

extern short goal_x, goal_y; //goal coordinates once found



//*/
#endif // !CONSTANTS_H