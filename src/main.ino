
//#include <../include/SoftwareSerial.h>
//SoftwareSerial Bluetooth(10, 9); // RX, TX
Serial uart1(D10 /* TX */, D2 /* RX */);
/*int LED = 13; // the on-board LED
int Data; // the data received
 
void setup() {
  Bluetooth.begin(9600);
  Serial.begin(9600);
  Serial.println("Waiting for command...");
  Bluetooth.println("Send 1 to turn on the LED. Send 0 to turn Off");
  pinMode(LED,OUTPUT);
 
}
 
void loop() {
  if (Bluetooth.available()){ //wait for data received
    Data=Bluetooth.read();
    if(Data=='1'){  
      digitalWrite(LED,1);
      Serial.println("LED On!");
      Bluetooth.println("LED On!");
    }
    else if(Data=='0'){
       digitalWrite(LED,0);
       Serial.println("LED Off!");
       Bluetooth.println("LED  On D13 Off ! ");
    }
    else{;}
  }
delay(100);
}
/*SoftwareSerial Bluetooth(10, 9); // RX, TX
int LED = builtin_led_Pin; // the on-board LED
int Data; // the data received
 
void setup() {
  Bluetooth.begin(9600);
  Serial.begin(9600);
  Serial.println("Waiting for command...");
  Bluetooth.println("Send 1 to turn on the LED. Send 0 to turn Off");
  pinMode(LED,OUTPUT);
 
}
 
void loop() {
  if (Bluetooth.available()){ //wait for data received
    Data=Bluetooth.read();
    if(Data=='1'){  
      digitalWrite(LED,1);
      Serial.println("LED On!");
      Bluetooth.println("LED On!");
    }
    else if(Data=='0'){
       digitalWrite(LED,0);
       Serial.println("LED Off!");
       Bluetooth.println("LED  On D13 Off ! ");
    }
    else{;}
  }
delay(100);
}





































/*#include "../include/commons.h"

#include "../include/battery_voltage.h"
#include "../include/imu.h"
#include "../include/senFusion.h"
#include "../include/controller.h"
#include "../include/IR.h"
#include "../include/speed_profiler.h"
#include "../include/encoder.h"

#include "../include/path_planner.h"
#include "../include/test_run.h"
//#define DEBUG 

/*
short frontwallflag; //global flag that is set when PID finds a front wall
short noWall;  //global flag to detect scenario with no walls
struct Maze * my_maze; //maze that keeps track of flood fill values and walls
struct Stack * my_stack; //stack used for flood fill
struct Node * temp; //node used for in-between start->goal, goal->start transition
short found_dest; //flag if goal is reached
short direction; //direction that the mouse is facing
short x, y; //current coordinates of the mouse in the maze

short goal_x, goal_y; //goal coordinates once found
*/
/*
#ifndef DEBUG
  void setup(){
    Serial.begin(115200);
    while(!Serial) {}

    init_IMU();
    init_STATES();
  }

  void loop()
  {

    //IR_module.fire_and_get();
    swipe_to_begin();
    refresh_IMU();
    display_IMU();

    read_encoder();
    display_encoder_counts(); 
    display_encoder_distance();   
    kalman_Magic();
    
    desired_vel = 10;

    //const_Speed();
   // kalman_testing();
  }




#endif // DEBUG

*///

//Actual Final run code.
//#ifndef DEBUG
  /*void setup()
  {
    Serial.begin(9600);
    //Serial.println("reached ");
    //while(!Serial) {}
    pinMode(builtin_led_Pin, OUTPUT);
    pinMode(rme, OUTPUT);
    pinMode(rmi1, OUTPUT);
    pinMode(rmi2, OUTPUT);

    //init_IMU();
    //calibrationMagnet ometer();
    //init_STATES();
  //  init_MAZE();
    
  }

  void loop()
  {
  //  move_single_cell();
    //desired_vel = 10;

    //const_Speed();
    //read_encoder();
    Serial.println("reached ");
    
    //IR_module.fire_and_get();
    //IR_module.display_IR();
    //refresh_IMU();
    //yawGyro_WC_update();
    //display_IMU();
//
    //read_encoder();
    //display_encoder_counts(); 
    //display_encoder_distance();   
    //kalman_Magic();
    //display_states();
    //
    //desired_vel = 10;

    //const_Speed();
   // kalman_testing();

    digitalWrite(rme,HIGH);
    digitalWrite(rmi1,HIGH);
    digitalWrite(rmi2,LOW);

    //digitalWrite(builtin_led_Pin,HIGH);
    //delay(1000);
    //digitalWrite(builtin_led_Pin,LOW);
    //delay(1000);
    //check_low_battery();
    //IR_module.fire_and_get();
    //refresh_IMU();
    //read_encoder();
    
    //IMU TESTING FAILED
    //refresh_IMU();
   //display_IMU();

    //kalman_Magic();
    //display_states();

    //const_Speed();z
    //kalman_testing();
  }
//#endif

/*
*Get sensor ops 
          ...IR Done.. 
          ..Converting encoder counts

*Feed it to kalman, path_planner, solver.
          Path_planner rem.
          Solver rem.

*Get directions from all of these above.

*Controller/actuator goop.
    ...Done...

To do ?
code merging for kalman , path planner.
Write code for battery voltage checker.
Converting encoder counts.
Epoch testing.



REPEAT
*/

//
// File trailer for main.cpp
//
// [EOF]
//


/*

*/