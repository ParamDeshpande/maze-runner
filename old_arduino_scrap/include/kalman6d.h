//
// File: kalman6d.h
//
// MATLAB Coder version            : 4.1
// C/C++ source code generated on  : 06-Sep-2019 11:24:46
//
#ifndef KALMAN6D_H
#define KALMAN6D_H

// Include Files
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "kalman6d_types.h"

// Function Declarations
extern void kalman6d(const double U[2], const double Z[6], const double
                     XHat_Prev[5], const double cov_Prev[25], const double
                     uncertVect[5], const double noiseVect[6], double dt, double
                     XHat_Updated[5], double cov_Updated[25]);

#endif

//
// File trailer for kalman6d.h
//
// [EOF]
//
