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


// Function Declarations
static void argInit_2x1_real_T(double result[2]);
static void argInit_5x1_real_T(double result[5]);
static void argInit_5x5_real_T(double result[25]);
static void argInit_6x1_real_T(double result[6]);
static double argInit_real_T();
static void main_kalman6d();

// Function Definitions

//
// Arguments    : double result[2]
// Return Type  : void
//
static void argInit_2x1_real_T(double result[2])
{
  double result_tmp;

  // Loop over the array to initialize each element.
  // Set the value of the array element.
  // Change this value to the value that the application requires.
  result_tmp = argInit_real_T();
  result[0] = result_tmp;

  // Set the value of the array element.
  // Change this value to the value that the application requires.
  result[1] = result_tmp;
}

//
// Arguments    : double result[5]
// Return Type  : void
//
static void argInit_5x1_real_T(double result[5])
{
  int idx0;

  // Loop over the array to initialize each element.
  for (idx0 = 0; idx0 < 5; idx0++) {
    // Set the value of the array element.
    // Change this value to the value that the application requires.
    result[idx0] = argInit_real_T();
  }
}

//
// Arguments    : double result[25]
// Return Type  : void
//
static void argInit_5x5_real_T(double result[25])
{
  int idx0;
  int idx1;

  // Loop over the array to initialize each element.
  for (idx0 = 0; idx0 < 5; idx0++) {
    for (idx1 = 0; idx1 < 5; idx1++) {
      // Set the value of the array element.
      // Change this value to the value that the application requires.
      result[idx0 + 5 * idx1] = argInit_real_T();
    }
  }
}

//
// Arguments    : double result[6]
// Return Type  : void
//
static void argInit_6x1_real_T(double result[6])
{
  int idx0;

  // Loop over the array to initialize each element.
  for (idx0 = 0; idx0 < 6; idx0++) {
    // Set the value of the array element.
    // Change this value to the value that the application requires.
    result[idx0] = argInit_real_T();
  }
}

//
// Arguments    : void
// Return Type  : double
//
static double argInit_real_T()
{
  return 0.0;
}

//
// Arguments    : void
// Return Type  : void
//
static void main_kalman6d()
{
  double dv0[2];
  double dv1[6];
  double dv2[5];
  double dv3[25];
  double dv4[5];
  double dv5[6];
  double XHat_Updated[5];
  double cov_Updated[25];

  // Initialize function 'kalman6d' input arguments.
  // Initialize function input argument 'U'.
  // Initialize function input argument 'Z'.
  // Initialize function input argument 'XHat_Prev'.
  // Initialize function input argument 'cov_Prev'.
  // Initialize function input argument 'uncertVect'.
  // Initialize function input argument 'noiseVect'.
  // Call the entry-point 'kalman6d'.
  argInit_2x1_real_T(dv0);
  argInit_6x1_real_T(dv1);
  argInit_5x1_real_T(dv2);
  argInit_5x5_real_T(dv3);
  argInit_5x1_real_T(dv4);
  argInit_6x1_real_T(dv5);
  kalman6d(dv0, dv1, dv2, dv3, dv4, dv5, argInit_real_T(), XHat_Updated,
           cov_Updated);
}

//
// Arguments    : int argc
//                const char * const argv[]
// Return Type  : int
//
int kalman_testing(void)
{
  // Initialize the application.
  // You do not need to do this more than one time.
  kalman6d_initialize();

  // Invoke the entry-point functions.
  // You can call entry-point functions multiple times.
  main_kalman6d();

  // Terminate the application.
  // You do not need to do this more than one time.
  kalman6d_terminate();
  return 0;
}

//
// File trailer for main.cpp
//
// [EOF]
//
