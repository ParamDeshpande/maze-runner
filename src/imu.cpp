
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

unsigned long int i; 

  void display_IMU(void){
  i++;
  Serial.print("  i   ");
  Serial.print(i);
  
  yawGyro_WC_update();
  Serial.print("  yaw_gyro  ");
  Serial.print("\t");
  Serial.print(yawGyro_rads,6);

  yawMag_update();
  Serial.print("  yaw_mag  ");
  Serial.print("\t");
  Serial.println(yawMag_rads,6);

//*/
  /*Serial.print("  Calibrating magnetometer ");
  Serial.print("\t");
  Serial.println("");
  calibrationMagnetometer();
  //Serial.println(IMU.getGyroZ_rads(),6);
  
  //Serial.println(IMU.getGyroZ_rads(),6);


  /*
  Serial.print(IMU.getAccelX_mss(),6);
  Serial.print("\t");
  Serial.print(IMU.getAccelY_mss(),6);
  Serial.print("\t");
  Serial.print(IMU.getAccelZ_mss(),6);
  Serial.print("\t");
  Serial.print(IMU.getGyroX_rads(),6);
  Serial.print("\t");
  Serial.print(IMU.getGyroY_rads(),6);
  Serial.print("\t  GYRO Z  ");
  Serial.print(IMU.getGyroZ_rads(),6);
  Serial.print("yaw_gyro");
  Serial.print("\t");
  Serial.println(yawGyro_rads);

  Serial.print("\t");
  Serial.print(IMU.getMagX_uT(),6);
  Serial.print("\t");
  Serial.print(IMU.getMagY_uT(),6);
  Serial.print("\t");
  Serial.print(IMU.getMagZ_uT(),6);
  Serial.print("\t");
  Serial.println(IMU.getTemperature_C(),6);//*/
}

/*Ideally if everything else fucks up you can always use gyro yaw */

void yawGyro_WC_update(void){
    IMU.readSensor();

    //yawGyro_rads +=  (IMU.getGyroZ_rads());

    yawGyro_rads +=  (IMU.getGyroZ_rads()*(50000) - angleSumFiftyK)/50000;   

    current_yaw = yawGyro_rads;
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


void calibrationMagnetometer(void){

  float hxb = 19.25; // mag bias of 10 uT
  float hxs = 0.97; // mag scale factor of 0.97
  IMU.setMagCalX(hxb,hxs);

  float hyb = 25.0; // mag bias of 10 uT
  float hys = 0.97; // mag scale factor of 0.97
  IMU.setMagCalY(hyb,hys);

  float hzb = -2.79; // mag bias of 10 uT
  float hzs = 0.97; // mag scale factor of 0.97
  IMU.setMagCalZ(hzb,hzs);
  
  Serial.println("MAGNETOMETER CALIBRATED according to new values");  
//*/
  //Note these values.

  status = IMU.calibrateMag();

/*
  float hxb;
  hxb = IMU.getMagBiasX_uT();
  Serial.print("MAGNETOMETER BIAS X(uT)");
  Serial.println(hxb);
  Serial.println("");

  float hxs;
  hxs = IMU.getMagScaleFactorX();
  Serial.print("MAGNETOMETER X Scaled by (uT)");
  Serial.println(hxb);
  Serial.println("true_val = reading/scale");

  float hyb;
  hyb = IMU.getMagBiasY_uT();
  Serial.print("MAGNETOMETER BIAS Y(uT)");
  Serial.println(hyb);
  Serial.println("");

  float hys;
  hys = IMU.getMagScaleFactorY();
  Serial.print("MAGNETOMETER Y Scaled by (uT)");
  Serial.println(hyb);
  Serial.println("true_val = reading/scale");

  float hzb;
  hzb = IMU.getMagBiasZ_uT();
  Serial.print("MAGNETOMETER BIAS Z(uT)");
  Serial.println(hzb);
  Serial.println("");

  float hzs;
  hzs = IMU.getMagScaleFactorZ();
  Serial.print("MAGNETOMETER Z Scaled by (uT)");
  Serial.println(hzb);
  Serial.println("true_val = reading/scale");
  Serial.println("");

 */ 

}