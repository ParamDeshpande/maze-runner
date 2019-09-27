//
// File: kalman6d.cpp
//
// MATLAB Coder version            : 4.1
// C/C++ source code generated on  : 05-Sep-2019 11:24:03
//

// Include Files
#include <cmath>
#include <string.h>
#include "../include/kalman6d.h"

// Function Definitions

//
// Arguments    : const double U[2]
//                const double Z[6]
//                const double XHat_Prev[5]
//                const double cov_Prev[25]
//                const double uncertVect[5]
//                const double noiseVect[6]
//                double dt
//                double XHat_Updated[5]
//                double cov_Updated[25]
// Return Type  : void
//
void kalman6d(const double U[2], const double Z[6], const double XHat_Prev[5],
              const double cov_Prev[25], const double uncertVect[5], const
              double noiseVect[6], double dt, double XHat_Updated[5], double
              cov_Updated[25])
{
  double A[25];
  int i0;
  double C[30];
  static const signed char iv0[5] = { 0, 0, 1, 0, 0 };

  static const signed char iv1[5] = { 0, 0, 0, 0, 1 };

  double smax;
  double b_dt[10];
  int k;
  int jA;
  double b_A[25];
  double XHat_Priori[5];
  int iy;
  double s;
  double cov_Priori[25];
  int jp1j;
  double c[36];
  double gain[30];
  double b_noiseVect[36];
  double b_C[30];
  double c_C[36];
  int j;
  signed char ipiv[6];
  int jj;
  signed char p[6];
  int n;
  int ix;
  int i;
  double b_Z[6];
  A[0] = 1.0;
  A[5] = dt;
  A[10] = 0.5 * dt * dt;
  A[15] = 0.0;
  A[20] = 0.0;
  A[1] = 0.0;
  A[6] = 1.0;
  A[11] = dt;
  A[16] = 0.0;
  A[21] = 0.0;
  A[3] = 0.0;
  A[8] = 0.0;
  A[13] = 0.0;
  A[18] = 1.0;
  A[23] = dt;
  for (i0 = 0; i0 < 5; i0++) {
    A[2 + 5 * i0] = iv0[i0];
    A[4 + 5 * i0] = iv1[i0];
  }

  C[0] = 1.0;
  C[6] = dt;
  smax = dt * dt;
  C[12] = smax;
  C[18] = 0.0;
  C[24] = 0.0;
  C[1] = 1.0;
  C[7] = dt;
  C[13] = smax;
  C[19] = 0.0;
  C[25] = 0.0;
  C[2] = 1.0 / smax;
  C[8] = 1.0 / dt;
  C[14] = 0.0;
  C[20] = 0.0;
  C[26] = 0.0;
  C[3] = 0.0;
  C[9] = 0.0;
  C[15] = 0.0;
  C[21] = 1.0;
  C[27] = dt;
  C[4] = 0.0;
  C[10] = 0.0;
  C[16] = 0.0;
  C[22] = 1.0;
  C[28] = dt;
  C[5] = 0.0;
  C[11] = 0.0;
  C[17] = 0.0;
  C[23] = 1.0;
  C[29] = dt;

  // measurement noise matrix
  // represents uncertainty matrix
  // ******equation matrices***********
  // **********state extrapolation********
  b_dt[0] = dt;
  b_dt[5] = 0.0;
  b_dt[2] = 1.0 / dt;
  b_dt[7] = 0.0;
  b_dt[3] = 0.0;
  b_dt[8] = dt;
  b_dt[1] = 1.0;
  b_dt[4] = 0.0;
  b_dt[6] = 0.0;
  b_dt[9] = 1.0;

  // **********covariance extrapolation******
  for (i0 = 0; i0 < 5; i0++) {
    smax = 0.0;
    for (k = 0; k < 5; k++) {
      smax += A[i0 + 5 * k] * XHat_Prev[k];
    }

    for (k = 0; k < 5; k++) {
      jA = i0 + 5 * k;
      b_A[jA] = 0.0;
      s = 0.0;
      for (jp1j = 0; jp1j < 5; jp1j++) {
        s += A[i0 + 5 * jp1j] * cov_Prev[jp1j + 5 * k];
      }

      b_A[jA] = s;
    }

    for (k = 0; k < 5; k++) {
      iy = i0 + 5 * k;
      cov_Priori[iy] = 0.0;
      s = 0.0;
      for (jp1j = 0; jp1j < 5; jp1j++) {
        s += b_A[i0 + 5 * jp1j] * A[k + 5 * jp1j];
      }

      cov_Priori[iy] = s;
    }

    XHat_Priori[i0] = smax + (b_dt[i0] * U[0] + b_dt[i0 + 5] * U[1]);
  }

  A[0] = uncertVect[0] * uncertVect[0];
  A[5] = 0.0;
  A[10] = 0.0;
  A[15] = 0.0;
  A[20] = 0.0;
  A[1] = 0.0;
  A[6] = uncertVect[1] * uncertVect[1];
  A[11] = 0.0;
  A[16] = 0.0;
  A[21] = 0.0;
  A[2] = 0.0;
  A[7] = 0.0;
  A[12] = uncertVect[2] * uncertVect[2];
  A[17] = 0.0;
  A[22] = 0.0;
  A[3] = 0.0;
  A[8] = 0.0;
  A[13] = 0.0;
  A[18] = uncertVect[3] * uncertVect[3];
  A[23] = 0.0;
  A[4] = 0.0;
  A[9] = 0.0;
  A[14] = 0.0;
  A[19] = 0.0;
  A[24] = uncertVect[4] * uncertVect[4];
  for (i0 = 0; i0 < 25; i0++) {
    cov_Priori[i0] += A[i0];
  }

  // ***********Kalman Gain**********
  for (i0 = 0; i0 < 6; i0++) {
    for (k = 0; k < 5; k++) {
      gain[k + 5 * i0] = C[i0 + 6 * k];
    }
  }

  memset(&c[0], 0, 36U * sizeof(double));
  for (i0 = 0; i0 < 6; i0++) {
    for (k = 0; k < 5; k++) {
      iy = i0 + 6 * k;
      b_C[iy] = 0.0;
      s = 0.0;
      for (jp1j = 0; jp1j < 5; jp1j++) {
        s += C[i0 + 6 * jp1j] * cov_Priori[jp1j + 5 * k];
      }

      b_C[iy] = s;
    }

    for (k = 0; k < 6; k++) {
      iy = i0 + 6 * k;
      c_C[iy] = 0.0;
      s = 0.0;
      for (jp1j = 0; jp1j < 5; jp1j++) {
        s += b_C[i0 + 6 * jp1j] * gain[jp1j + 5 * k];
      }

      c_C[iy] = s;
    }
  }

  b_noiseVect[0] = noiseVect[0] * noiseVect[0];
  b_noiseVect[6] = 0.0;
  b_noiseVect[12] = 0.0;
  b_noiseVect[18] = 0.0;
  b_noiseVect[24] = 0.0;
  b_noiseVect[30] = 0.0;
  b_noiseVect[1] = 0.0;
  b_noiseVect[7] = noiseVect[1] * noiseVect[1];
  b_noiseVect[13] = 0.0;
  b_noiseVect[19] = 0.0;
  b_noiseVect[25] = 0.0;
  b_noiseVect[31] = 0.0;
  b_noiseVect[2] = 0.0;
  b_noiseVect[8] = 0.0;
  b_noiseVect[14] = noiseVect[2] * noiseVect[2];
  b_noiseVect[20] = 0.0;
  b_noiseVect[26] = 0.0;
  b_noiseVect[32] = 0.0;
  b_noiseVect[3] = 0.0;
  b_noiseVect[9] = 0.0;
  b_noiseVect[15] = 0.0;
  b_noiseVect[21] = noiseVect[3] * noiseVect[3];
  b_noiseVect[27] = 0.0;
  b_noiseVect[33] = 0.0;
  b_noiseVect[4] = 0.0;
  b_noiseVect[10] = 0.0;
  b_noiseVect[16] = 0.0;
  b_noiseVect[22] = 0.0;
  b_noiseVect[28] = noiseVect[4] * noiseVect[4];
  b_noiseVect[34] = 0.0;
  b_noiseVect[5] = 0.0;
  b_noiseVect[11] = 0.0;
  b_noiseVect[17] = 0.0;
  b_noiseVect[23] = 0.0;
  b_noiseVect[29] = 0.0;
  b_noiseVect[35] = noiseVect[5] * noiseVect[5];
  for (i0 = 0; i0 < 36; i0++) {
    c_C[i0] += b_noiseVect[i0];
  }

  for (i0 = 0; i0 < 6; i0++) {
    ipiv[i0] = (signed char)(1 + i0);
  }

  for (j = 0; j < 5; j++) {
    jA = j * 7;
    jj = j * 7;
    jp1j = jA + 2;
    n = 6 - j;
    iy = 0;
    ix = jA;
    smax = std::abs(c_C[jA]);
    for (k = 2; k <= n; k++) {
      ix++;
      s = std::abs(c_C[ix]);
      if (s > smax) {
        iy = k - 1;
        smax = s;
      }
    }

    if (c_C[jj + iy] != 0.0) {
      if (iy != 0) {
        iy += j;
        ipiv[j] = (signed char)(iy + 1);
        ix = j;
        for (k = 0; k < 6; k++) {
          smax = c_C[ix];
          c_C[ix] = c_C[iy];
          c_C[iy] = smax;
          ix += 6;
          iy += 6;
        }
      }

      i0 = (jj - j) + 6;
      for (i = jp1j; i <= i0; i++) {
        c_C[i - 1] /= c_C[jj];
      }
    }

    n = 4 - j;
    iy = jA + 6;
    jA = jj;
    for (jp1j = 0; jp1j <= n; jp1j++) {
      smax = c_C[iy];
      if (c_C[iy] != 0.0) {
        ix = jj + 1;
        i0 = jA + 8;
        k = (jA - j) + 12;
        for (i = i0; i <= k; i++) {
          c_C[i - 1] += c_C[ix] * -smax;
          ix++;
        }
      }

      iy += 6;
      jA += 6;
    }
  }

  for (i0 = 0; i0 < 6; i0++) {
    p[i0] = (signed char)(1 + i0);
  }

  for (k = 0; k < 5; k++) {
    if (ipiv[k] > 1 + k) {
      jA = ipiv[k] - 1;
      iy = p[jA];
      p[jA] = p[k];
      p[k] = (signed char)iy;
    }
  }

  for (k = 0; k < 6; k++) {
    jp1j = p[k] - 1;
    c[k + 6 * jp1j] = 1.0;
    for (j = k + 1; j < 7; j++) {
      if (c[(j + 6 * jp1j) - 1] != 0.0) {
        i0 = j + 1;
        for (i = i0; i < 7; i++) {
          iy = (i + 6 * jp1j) - 1;
          c[iy] -= c[(j + 6 * jp1j) - 1] * c_C[(i + 6 * (j - 1)) - 1];
        }
      }
    }
  }

  for (j = 0; j < 6; j++) {
    jA = 6 * j;
    for (k = 5; k >= 0; k--) {
      iy = 6 * k;
      i0 = k + jA;
      if (c[i0] != 0.0) {
        c[i0] /= c_C[k + iy];
        for (i = 0; i < k; i++) {
          jp1j = i + jA;
          c[jp1j] -= c[i0] * c_C[i + iy];
        }
      }
    }
  }

  for (i0 = 0; i0 < 5; i0++) {
    for (k = 0; k < 6; k++) {
      iy = i0 + 5 * k;
      b_C[iy] = 0.0;
      s = 0.0;
      for (jp1j = 0; jp1j < 5; jp1j++) {
        s += cov_Priori[i0 + 5 * jp1j] * gain[jp1j + 5 * k];
      }

      b_C[iy] = s;
    }
  }

  for (i0 = 0; i0 < 5; i0++) {
    for (k = 0; k < 6; k++) {
      iy = i0 + 5 * k;
      gain[iy] = 0.0;
      s = 0.0;
      for (jp1j = 0; jp1j < 6; jp1j++) {
        s += b_C[i0 + 5 * jp1j] * c[jp1j + 6 * k];
      }

      gain[iy] = s;
    }
  }

  // ********State update equation*******
  for (i0 = 0; i0 < 6; i0++) {
    s = 0.0;
    for (k = 0; k < 5; k++) {
      s += C[i0 + 6 * k] * XHat_Priori[k];
    }

    b_Z[i0] = Z[i0] - s;
  }

  for (i0 = 0; i0 < 5; i0++) {
    s = 0.0;
    for (k = 0; k < 6; k++) {
      s += gain[i0 + 5 * k] * b_Z[k];
    }

    XHat_Updated[i0] = XHat_Priori[i0] + s;
  }

  // ********Covariance update equation********
  memset(&A[0], 0, 25U * sizeof(double));
  for (k = 0; k < 5; k++) {
    A[k + 5 * k] = 1.0;
  }

  for (i0 = 0; i0 < 5; i0++) {
    for (k = 0; k < 5; k++) {
      s = 0.0;
      for (jp1j = 0; jp1j < 6; jp1j++) {
        s += gain[i0 + 5 * jp1j] * C[jp1j + 6 * k];
      }

      jA = i0 + 5 * k;
      b_A[jA] = A[jA] - s;
    }

    for (k = 0; k < 5; k++) {
      iy = i0 + 5 * k;
      cov_Updated[iy] = 0.0;
      s = 0.0;
      for (jp1j = 0; jp1j < 5; jp1j++) {
        s += b_A[i0 + 5 * jp1j] * cov_Priori[jp1j + 5 * k];
      }

      cov_Updated[iy] = s;
    }
  }
}

//
// File trailer for kalman6d.cpp
//
// [EOF]
//
