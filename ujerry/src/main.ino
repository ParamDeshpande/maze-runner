#include "../include/main.h"
#include "../include/port.h"
#include "../include/constants.h"

#include "../include/battery_voltage.h"
#include "../include/imu.h"
#include "../include/senFusion.h"
#include "../include/controller.h"
#include "../include/IR.h"
#include "../include/speed_profiler.h"
#include "../include/encoder.h"

#ifdef DEBUG
  void setup()
  {
    Serial.begin(115200);
    while(!Serial) {}
    init_IMU();
    init_STATES();
  }

  void loop()
  {

    IR_module.fire_and_get();
    refresh_IMU();
    display_IMU();

    read_encoder();
    display_encoder_counts(); 
    display_encoder_distance();   
    kalman_Magic();
    
    

    desired_vel = 10;

    const_Speed();
    kalman_testing();
  }




#endif // DEBUG



//Actual Final run code.
#ifndef DEBUG
  void setup()
  {
    Serial.begin(115200);
    while(!Serial) {}
    init_IMU();
    init_STATES();
  }

  void loop()
  {

    IR_module.fire_and_get();
    refresh_IMU();
    read_encoder();
    
    kalman_Magic();
    
    //const_Speed();
    //kalman_testing();
  }
#endif 
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