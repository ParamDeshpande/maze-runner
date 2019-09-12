
#include "../include/main.h"
#include "../include/port.h"
#include "../include/constants.h"

#include "../include/MPU9250.h"
#include "../include/imu.h"

// an MPU9250 object with the MPU-9250 sensor on I2C bus 0 with address 0x68
//double x = 0;

  MPU9250 IMU(Wire,0x68);
  int status;
  double yawGyro_rads = 0; 
  double yawMag_rads = 0;
  double yawAccelero_rads = 0;

void init_IMU(void) {

  // start communication with IMU 
  status = IMU.begin();
  if (status < 0) {
    Serial.println("IMU initialization unsuccessful");
    Serial.println("Check IMU wiring or try cycling power");
    Serial.print("Status: ");
    Serial.println(status);
    #ifdef DEBUG
    //while(1) {}
    #endif
  }
  // setting the accelerometer full scale range to +/-8G 
  IMU.setAccelRange(MPU9250::ACCEL_RANGE_8G);
  // setting the gyroscope full scale range to +/-500 deg/s
  IMU.setGyroRange(MPU9250::GYRO_RANGE_500DPS);
  // setting DLPF bandwidth to 20 Hz
  IMU.setDlpfBandwidth(MPU9250::DLPF_BANDWIDTH_20HZ);
  // setting SRD to 19 for a 50 Hz update rate
  IMU.setSrd(19);
}


  void display_IMU(void){

  Serial.print(IMU.getAccelX_mss(),6);
  Serial.print("\t");
  Serial.print(IMU.getAccelY_mss(),6);
  Serial.print("\t");
  Serial.print(IMU.getAccelZ_mss(),6);
  Serial.print("\t");
  Serial.print(IMU.getGyroX_rads(),6);
  Serial.print("\t");
  Serial.print(IMU.getGyroY_rads(),6);
  Serial.print("\t");
  Serial.print(IMU.getGyroZ_rads(),6);
  Serial.print("\t");
  Serial.print(IMU.getMagX_uT(),6);
  Serial.print("\t");
  Serial.print(IMU.getMagY_uT(),6);
  Serial.print("\t");
  Serial.print(IMU.getMagZ_uT(),6);
  Serial.print("\t");
  Serial.println(IMU.getTemperature_C(),6);
}

/*Ideally if everything else fucks up you can always use gyro yaw */
void yawGyro_WC_update(void){
    IMU.readSensor();

    yawGyro_rads +=  (IMU.getGyroZ_rads()*(50000) - angleSumFiftyK)/50000;   
}

/*to calc mag yaw you need roll and pitch which needs to filtered through kalman
All in all 2 kalmans 
*/



double accelX;
double accelY;
double accelZ;
double magReadX;
double magReadY;
double magReadZ;
double roll;
double pitch;
double yaw;
double mag_x;
double mag_y;

void refresh_IMU(void) {
  IMU.readSensor();
  accelX = IMU.getAccelX_mss();
  accelY = IMU.getAccelY_mss();
  accelZ = IMU.getAccelZ_mss();

  magReadX = IMU.getMagX_uT();
  magReadY = IMU.getMagY_uT();
  magReadZ = IMU.getMagZ_uT();

}

void calc_RollPitch(void){
       
       pitch = 180 * atan2(accelX, sqrt(accelY*accelY + accelZ*accelZ))/M_PI;
       roll = 180 * atan2(accelY, sqrt(accelX*accelX + accelZ*accelZ))/M_PI;
       }
        
void yawMag_update(void){
    calc_RollPitch();
    mag_x = magReadX*cos(pitch) + magReadY*sin(roll)*sin(pitch) + magReadZ*cos(roll)*sin(pitch);
    mag_y = magReadY * cos(roll) - magReadZ * sin(roll);
    yawMag_rads = 180 * atan2(-mag_y,mag_x)/M_PI;

}
