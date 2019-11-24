#ifndef IMU_H
#define IMU_H

//You dont include any other Header files in this.

//  Define global variables
//float yawGyro_rads; 
//float yawMag_rads;

//private mag_x
//Function proototypes
void init_IMU(void) ;
void display_IMU(void) ;
void yawGyro_WC_update(void);
void refresh_IMU(void) ;
void calc_RollPitch(void);
void yawMag_update(void) ;

//
//extern double accelX;
//extern double yawGyro_rads;
//extern double yawAccelero_rads;


#endif // !IMU_H