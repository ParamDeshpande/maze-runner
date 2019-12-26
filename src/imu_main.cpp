/* MPU9250 Basic Example Code
 by: Kris Winer
 date: April 1, 2014
 license: Beerware - Use this code however you'd like. If you 
 find it useful you can buy me a beer some time.
 
 Demonstrate basic MPU-9250 functionality including parameterizing the register addresses, initializing the sensor, 
 getting properly scaled accelerometer, gyroscope, and magnetometer data out. Added display functions to 
 allow display to on breadboard monitor. Addition of 9 DoF sensor fusion using open source Madgwick and 
 Mahony filter algorithms. Sketch runs on the 3.3 V 8 MHz Pro Mini and the Teensy 3.1.
 
 SDA and SCL should have external pull-up resistors (to 3.3V).
 10k resistors are on the EMSENSR-9250 breakout board.
 
 Hardware setup:
 MPU9250 Breakout --------- Arduino
 VDD ---------------------- 3.3V
 VDDI --------------------- 3.3V
 SDA ----------------------- A4
 SCL ----------------------- A5
 GND ---------------------- GND
 */
#include "commons.h"
#include "../lib/MPU9250.h"
#include "imu.h"

#define angleSumFiftyK -373.6619743981135 
#define calib_factor 2.65

//Global vars
double corrected_yaw = -1000;


// PRIVATE VARS
static float sum = 0;
static uint32_t sumCount = 0;
static char buffer[14];
static int Countt = 0;
double yawGyro_rads =0;
static int8_t wait_10_yaw_vals = 10;
static double yaw_offset = -1.0;
MPU9250 mpu9250;

Timer t;

void imu_setup(void){
  
  //Set up I2C
  i2c.frequency(400000);  // use fast (400 kHz) I2C  
  
  bt.printf("CPU SystemCoreClock is %d Hz\r\n", SystemCoreClock);   
  
  t.start();        
  
  uint8_t whoami = mpu9250.readByte(MPU9250_ADDRESS, WHO_AM_I_MPU9250);  // Read WHO_AM_I register for MPU-9250
  bt.printf("I AM 0x%x\n\r", whoami); bt.printf("I SHOULD BE 0x71\n\r");


  // Read the WHO_AM_I register, this is a good test of communication
  
  if (whoami == 0x71) // WHO_AM_I should always be 0x68
  {  
    
    #ifdef DEBUG
    bt.printf("MPU9250 WHO_AM_I is 0x%x\n\r", whoami);
    bt.printf("MPU9250 is online...\n\r");
    
    #endif // DEBUG
    
    wait(1);
    mpu9250.resetMPU9250(); // Reset registers to default in preparation for device calibration
    mpu9250.MPU9250SelfTest(SelfTest); // Start by performing self test and reporting values
    
    #ifdef DEBUG
    bt.printf("x-axis self test: acceleration trim within : %f % of factory value\n\r", SelfTest[0]);  
    bt.printf("y-axis self test: acceleration trim within : %f % of factory value\n\r", SelfTest[1]);  
    bt.printf("z-axis self test: acceleration trim within : %f % of factory value\n\r", SelfTest[2]);  
    bt.printf("x-axis self test: gyration trim within : %f % of factory value\n\r", SelfTest[3]);  
    bt.printf("y-axis self test: gyration trim within : %f % of factory value\n\r", SelfTest[4]);  
    bt.printf("z-axis self test: gyration trim within : %f % of factory value\n\r", SelfTest[5]);  
    #endif // DEBUG
    mpu9250.calibrateMPU9250(gyroBias, accelBias); // Calibrate gyro and accelerometers, load biases in bias registers  
    
    #ifdef DEBUG
    bt.printf("x gyro bias = %f\n\r", gyroBias[0]);
    bt.printf("y gyro bias = %f\n\r", gyroBias[1]);
    bt.printf("z gyro bias = %f\n\r", gyroBias[2]);
    bt.printf("x accel bias = %f\n\r", accelBias[0]);
    bt.printf("y accel bias = %f\n\r", accelBias[1]);
    bt.printf("z accel bias = %f\n\r", accelBias[2]);
    
    #endif // DEBUG
    
    
    wait(2);
    mpu9250.initMPU9250(); 

    #ifdef DEBUG
    bt.printf("MPU9250 initialized for active data mode....\n\r"); // Initialize device for active mode read of acclerometer, gyroscope, and temperature
    #endif // DEBUG
    
    mpu9250.initAK8963(magCalibration);
    
    #ifdef DEBUG
    bt.printf("AK8963 initialized for active data mode....\n\r"); // Initialize device for active mode read of magnetometer
    bt.printf("Accelerometer full-scale range = %f  g\n\r", 2.0f*(float)(1<<Ascale));
    bt.printf("Gyroscope full-scale range = %f  deg/s\n\r", 250.0f*(float)(1<<Gscale));
    #endif // DEBUG
    
    if(Mscale == 0) bt.printf("Magnetometer resolution = 14  bits\n\r");
    if(Mscale == 1) bt.printf("Magnetometer resolution = 16  bits\n\r");
    if(Mmode == 2) bt.printf("Magnetometer ODR = 8 Hz\n\r");
    if(Mmode == 6) bt.printf("Magnetometer ODR = 100 Hz\n\r");
    wait(1);
   }
   else
   {
    #ifdef DEBUG
    bt.printf("Could not connect to MPU9250: \n\r");
    bt.printf("%#x \n",  whoami);
    #endif // DEBUG

    }

}   

void refresh_imu(void)
{
    mpu9250.getAres(); // Get accelerometer sensitivity
    mpu9250.getGres(); // Get gyro sensitivity
    mpu9250.getMres(); // Get magnetometer sensitivity
    magbias[0] = +470.;  // User environmental x-axis correction in milliGauss, should be automatically calculated
    magbias[1] = +120.;  // User environmental x-axis correction in milliGauss
    magbias[2] = +125.;  // User environmental x-axis correction in milliGauss



  
  // If intPin goes high, all data registers have new data
  if(mpu9250.readByte(MPU9250_ADDRESS, INT_STATUS) & 0x01) {  // On interrupt, check if data ready interrupt

    mpu9250.readAccelData(accelCount);  // Read the x/y/z adc values   
    // Now we'll calculate the accleration value into actual g's
    ax = (float)accelCount[0]*aRes - accelBias[0];  // get actual g value, this depends on scale being set
    ay = (float)accelCount[1]*aRes - accelBias[1];   
    az = (float)accelCount[2]*aRes - accelBias[2];  
   
    mpu9250.readGyroData(gyroCount);  // Read the x/y/z adc values
    // Calculate the gyro value into actual degrees per second
    gx = (float)gyroCount[0]*gRes - gyroBias[0];  // get actual gyro value, this depends on scale being set
    gy = (float)gyroCount[1]*gRes - gyroBias[1];  
    gz = (float)gyroCount[2]*gRes - gyroBias[2];   
  
    mpu9250.readMagData(magCount);  // Read the x/y/z adc values   
    // Calculate the magnetometer values in milliGauss
    // Include factory calibration per data sheet and user environmental corrections
    mx = (float)magCount[0]*mRes*magCalibration[0] - magbias[0];  // get actual magnetometer value, this depends on scale being set
    my = (float)magCount[1]*mRes*magCalibration[1] - magbias[1];  
    mz = (float)magCount[2]*mRes*magCalibration[2] - magbias[2];   
  }
   
    Now = t.read_us();
    deltat = (float)((Now - lastUpdate)/1000000.0f) ; // set integration time by time elapsed since last filter update
    lastUpdate = Now;
    
    sum += deltat;
    sumCount++;
    // Pass gyro rate as rad/s
    //  mpu9250.MadgwickQuaternionUpdate(ax, ay, az, gx*PI/180.0f, gy*PI/180.0f, gz*PI/180.0f,  my,  mx, mz);
    mpu9250.MahonyQuaternionUpdate(ax, ay, az, gx*PI/180.0f, gy*PI/180.0f, gz*PI/180.0f, my, mx, mz);

    // Serial print and/or display at 0.5 s rate independent of data rates
    delt_t = t.read_ms() - imu_count;
    yaw   = atan2(2.0f * (q[1] * q[2] + q[0] * q[3]), q[0] * q[0] + q[1] * q[1] - q[2] * q[2] - q[3] * q[3]);   

    yawGyro_rads +=  (gz*(50000) - angleSumFiftyK)/50000;
    pitch = -asin(2.0f * (q[1] * q[3] - q[0] * q[2]));
    roll  = atan2(2.0f * (q[0] * q[1] + q[2] * q[3]), q[0] * q[0] - q[1] * q[1] - q[2] * q[2] + q[3] * q[3]);
    pitch *= 180.0f / PI;
    yaw   *= 180.0f / PI; 
    yaw *= calib_factor;
    //yaw -= yaw_offset ;
    if(wait_10_yaw_vals > 0){
      wait_10_yaw_vals--;
    }
    if(wait_10_yaw_vals == 0){
      yaw_offset = yaw;
      wait_10_yaw_vals--;
      corrected_yaw = 00;
    }
    corrected_yaw =  -(yaw - yaw_offset) ; 
    //yaw   -= 13.8f; // Declination at Danville, California is 13 degrees 48 minutes and 47 seconds on 2014-04-04 (magnetic degs)
    // MUMBAI IT IS 0deg 3mins    
    roll  *= 180.0f / PI;

    //countt 
    #ifdef DEBUG
    bt.printf(" i = %d , corYaw: %f , yaw :%f  \n\r",Countt, corrected_yaw, yaw);
    printf(" i = %d , cor Yaw: %f , yaw :%f  ",Countt, corrected_yaw, yaw);
    #endif // DEBUG
    
    myled= !myled;
    imu_count = t.read_ms(); 

    if(imu_count > 1<<21) {
        t.start(); // start the timer over again if ~30 minutes has passed
        imu_count = 0;
        deltat= 0;
        lastUpdate = t.read_us();
    }
    sum = 0;
    sumCount = 0;

 
}