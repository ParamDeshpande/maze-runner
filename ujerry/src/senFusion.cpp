//
// File: main.cpp
//
// MATLAB Coder version            : 4.1
// C/C++ source code generated on  : 05-Sep-2019 11:24:03
//

//***********************************************************************
// This automatically generated example C main file shows how to call
// entry-point functions that MATLAB Coder generated. You must customize
// this file for your application. Do not modify this file directly.
// Instead, make a copy of this file, modify it, and integrate it into
// your development environment.
//
// This file initializes entry-point function arguments to a default
// size and value before calling the entry-point functions. It does
// not store or use any values returned from the entry-point functions.
// If necessary, it does pre-allocate memory for returned values.
// You can use this file as a starting point for a main function that
// you can deploy in your application.
//
// After you copy the file, and before you deploy it, you must make the
// following changes:
// * For variable-size function arguments, change the example sizes to
// the sizes that your application requires.
// * Change the example values of function arguments to the values that
// your application requires.
// * If the entry-point functions return values, store these values or
// otherwise use them as required by your application.
//
//***********************************************************************
// Include Files
#include"../include/main.h"
#include"../include/port.h"
#include"../include/constants.h"

#include "../include/kalman6d.h"
#include "../include/senFusion.h"
#include "../include/kalman6d_terminate.h"
#include "../include/kalman6d_initialize.h"
#include "../include/imu.h"

// Function Declarations
double inputs[2] = {desired_vel,desired_w};

double measurements[6] = {left_enc_dist,right_enc_dist,accelX,yawGyro_rads,yawAccelero_rads,yawMag_rads};

double previous_states[5] = {0};

double cov_Matrix_Old[25] = {0};

double uncertainty_Vector[5] = {calc_var_x,calc_var_vel,calc_var_x_acc,calc_var_yaw,calc_var_w};

double noise_Vector[6] = {measure_var_l_enc,measure_var_r_enc,measure_var_accelX,measure_var_yawGyro,measure_var_yawAccel,measure_var_yawMag};


double current_states[5] = {current_x,current_vel, current_x_acc, current_yaw, current_w};

double cov_Matrix_Current[25] = {0};

//Prototype
void main_kalman6d();
void init_KALMAN(void);
static void update_kalman_vars(void);

void init_STATES(void){

  //HOPE THIS FUNCTION WORKS!!!
  FILLARRAY(inputs,0);
  FILLARRAY(measurements,0);
  FILLARRAY(previous_states,0);
  FILLARRAY(current_states,0);

}

static void update_kalman_vars(void){

  inputs[0] = desired_vel;
  inputs[1] = desired_w;

  measurements[0] = left_enc_dist;
  measurements[1] = right_enc_dist;
  measurements[2] = accelX;
  measurements[3] = yawGyro_rads;
  measurements[4] = yawAccelero_rads;
  measurements[5] = yawMag_rads;
}

void main_kalman6d()
{
  update_kalman_vars();

  // Initialize function 'kalman6d' input arguments.
  // Initialize function input argument 'U'.
  // Initialize function input argument 'Z'.
  // Initialize function input argument 'XHat_Prev'.
  // Initialize function input argument 'cov_Prev'.
  // Initialize function input argument 'uncertVect'.
  // Initialize function input argument 'noiseVect'.
  // Call the entry-point 'kalman6d'.
 kalman6d(inputs, measurements, previous_states, cov_Matrix_Old, uncertainty_Vector,noise_Vector , delT, current_states,
           cov_Matrix_Current);

  memcpy( previous_states, current_states, sizeof(previous_states) );
  memcpy(cov_Matrix_Old, cov_Matrix_Current, sizeof(cov_Matrix_Old) );
  //previous_states[5] = current_states[5];
  //cov_Matrix_Old[25] = cov_Matrix_Current[25];

}

//
// Arguments    : int argc
//                const char * const argv[]
// Return Type  : int
//
void kalman_Magic(void)
{
  main_kalman6d();
}

//
// File trailer for main.cpp
//
// [EOF]
//
