#define DEBUG_VIA_PRINTF 

//Kalman Parameters
#define calc_var_x 1000UL
#define calc_var_vel 1000UL
#define calc_var_x_acc 1000UL
#define calc_var_yaw D_2_RAD(0.05)
#define calc_var_w 1000UL

#define measure_var_l_enc 1000UL
#define measure_var_r_enc 1000UL
#define measure_var_accelX 1000UL
#define measure_var_yawGyro D_2_RAD(0.05)
#define measure_var_yawAccel D_2_RAD(500000)
#define measure_var_yawMag D_2_RAD(1500000)

#define constVel_speed 0UL
#define pivot_w 0UL
#define pivot_turn_Speed 0UL


#include "../include/commons.h"
#include "../include/sen_fusion.h"
#include "../include/encoder.h"
#include "../include/imu.h"

//PRIVATE VARS
static double prev_x = 0;
static double prev_yaw = 0;

void calc_state(void){
feed_enc();
current_x = ((EncoderPosition_TIM1 + EncoderPosition_TIM2)/(2.0*61.4444*100.0)); //DIST IN METERS (61.444 counts = 1cm)
current_vel = (current_x - prev_x)/delT;
current_yaw = yawGyro_rads;
current_w = (current_yaw - prev_yaw)/delT;
#ifdef DEBUG_VIA_PRINTF
pc.printf("Current time diff is %f \n\r", delT);
pc.printf("My current vel is %f \n\r", current_vel  );
pc.printf("My current w is %f \n\r",   current_yaw  );
#endif // DEBUG
prev_x = current_x;
prev_yaw = current_yaw;
}