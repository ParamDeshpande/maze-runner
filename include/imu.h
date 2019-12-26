#ifndef IMU_H
#define IMU_H

//You dont include any other Header files in this.
//Function prototypes
void imu_setup(void) ;
void refresh_imu(void) ;

//Global vars
extern double corrected_yaw;

#endif // !IMU_H