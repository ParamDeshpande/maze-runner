#ifndef IMU_H
#define IMU_H

//You dont include any other Header files in this.

//#include "../lib/MPU9250.h"

//Define global variables
//extern uint8_t whoami;
//extern MPU9250 mpu9250;
//private mag_x
extern float roll;
extern float pitch;
extern float yaw;

//Function proototypes
void imu_setup(void) ;
void refresh_imu(void) ;
//extern double accelX;
//extern double yawGyro_rads;
//extern double yawAccelero_rads;


#endif // !IMU_H