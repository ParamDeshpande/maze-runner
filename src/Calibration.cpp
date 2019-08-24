
#include "../include/Calibration.h"
#include "../include/Utils.h"

MPU9250 IMU(Wire,0x68);
int status;

void setup() {
  // serial to display data
  Serial.begin(115200);
  while(!Serial) {}

  // start communication with IMU   
  status = IMU.begin();
  
  if (status < 0) {
    Serial.println("IMU initialization unsuccessful");
    Serial.println("Check IMU wiring or try cycling power");
    Serial.print("Status: ");
    Serial.println(status);
    while(1) {}
  }
  // setting the accelerometer full scale range to +/-8G 
  IMU.setAccelRange(MPU9250::ACCEL_RANGE_8G);
  // setting the gyroscope full scale range to +/-500 deg/s
  IMU.setGyroRange(MPU9250::GYRO_RANGE_500DPS);
  // setting DLPF bandwidth to 20 Hz
  IMU.setDlpfBandwidth(MPU9250::DLPF_BANDWIDTH_20HZ);
  // setting SRD to 19 for a 50 Hz update rate SRD = SAMPLE DATA RATE op=1000 / (1 + SRD)
  IMU.setSrd(19);
}


void calibrate_IMU(void){

  IMU.readSensor();

  float gxb;
  gxb = IMU.getGyroBiasX_rads();
  Serial.print("GYRO BIAS X");
  Serial.println(gxb);
  Serial.println("");

  float gyb;
  gyb = IMU.getGyroBiasY_rads();
  Serial.print("GYRO BIAS Y");
  Serial.println(gyb);
  Serial.println("");

  float gzb;
  gzb = IMU.getGyroBiasZ_rads();
  Serial.print("GYRO BIAS Z");
  Serial.println(gyz);
  Serial.println("");

  Serial.println("Calibrating GYRO KEEP the sensor stable.... PRESS G TO CONTINUE............");  
  wait_for_G_press();

  status = IMU.calibrateGyro();
  Serial.println("GYRO CALIBRATED");  
  Serial.println("");

  ////////////////////////////////////////////////////////
  
  
  float axb;
  axb = IMU.getAccelBiasX_mss();
  Serial.print("ACC BIAS X");
  Serial.println(axb);
  Serial.println("");

  float axs;
  axs = IMU.getAccelScaleFactorX();
  Serial.print("Accelerometer scaled by");
  Serial.println(axs);
  Serial.println("times the current value aka true_acc=reading/Thisvalue");


  float ayb;
  ayb = IMU.getAccelBiasY_mss();
  Serial.print("ACC BIAS Y");
  Serial.println(ayb);
  Serial.println("");

  float ays;
  ays = IMU.getAccelScaleFactorY();
  Serial.print("Accelerometer scaled by");
  Serial.println(ays);
  Serial.println("times the current value aka true_acc=reading/Thisvalue");


  float azb;
  azb = IMU.getAccelBiasZ_mss();
  Serial.print("ACC BIAS Z");
  Serial.println(azb);
  Serial.println("");

  float azs;
  azs = IMU.getAccelScaleFactorZ();
  Serial.print("Accelerometer scaled by");
  Serial.println(azs);
  Serial.println("times the current value aka true_acc=reading/Thisvalue");
  Serial.println("");


  Serial.println("Calibrating ACCELEROMETER MOVE the sensor in all    6 directions.... PRESS G TO CONTINUE............");  
  wait_for_G_press();

  status = IMU.calibrateAccel();
  Serial.println("ACCELEROMETER CALIBRATED");  
  Serial.println("");
  
  /////////////////////////////////////////////////////////////
  
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

  
  Serial.println("Calibrating MAGNETOMETER MOVE the sensor continuously and slowly in a figure 8 while the function is running.... PRESS G TO CONTINUE............");  
  wait_for_G_press();

  status = IMU.calibrateMag();
  
  /*
  float gxb = 0.001; // gyro bias of 0.001 rad/s
  IMU.setGyroBiasX_rads(gxb);

  float gyb = 0.001; // gyro bias of 0.001 rad/s
  IMU.setGyroBiasY_rads(gyb);
  
  float gzb = 0.001; // gyro bias of 0.001 rad/s
  IMU.setGyroBiasZ_rads(gzb);
  
  Serial.println("GYRO CALIBRATED according to new values");  

  float hxb = 10.0; // mag bias of 10 uT
  float hxs = 0.97; // mag scale factor of 0.97
  IMU.setMagCalX(hxb,hxs);

  float hyb = 10.0; // mag bias of 10 uT
  float hys = 0.97; // mag scale factor of 0.97
  IMU.setMagCalY(hyb,hys);

  float hzb = 10.0; // mag bias of 10 uT
  float hzs = 0.97; // mag scale factor of 0.97
  IMU.setMagCalZ(hzb,hzs);
  
  Serial.println("MAGNETOMETER CALIBRATED according to new values");  

  
  */
  
  // display the data
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
  delay(20);

}
void loop() {
  // read the sensor
  calibrate_IMU();
  }
