#include "../include/main.h"
#include "../include/port.h"
#include "../include/constants.h"

#include "../include/imu.h"
#include "../include/senFusion.h"
#include "../include/controller.h"
#include "../include/IR.h"
#include "../include/speed_profiler.h"
#include "../include/encoder.h"

void setup()
{
  Serial.begin(115200);
  //while(!Serial) {}
  init_IMU();
}

void loop()
{

  IR_module.fire_and_get();
  IR_module.display_IR();
  
  refresh_IMU();
  display_IMU();

  //desired_vel = 10;

  //const_Speed();
  read_encoder();
  //kalman_testing();
}

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