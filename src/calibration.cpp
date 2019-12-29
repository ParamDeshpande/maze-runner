#include "commons.h"
#include "imu.h"
#include "buzzer.h"
#include "actuator.h"
#include "encoder.h"
#include "Utils.h"

#define DEBUG

#define Stable_VARIANCE_YAW 100.0
#define MOTOR_TURN_SPEED 10.0
#define STABLE_BUF_SIZE 150

//PRIVATE FUNCTIONS 
int variance(int [], int); 


int variance(int a[], int n) 
{ 
    // Compute mean (average of elements) 
    int sum = 0; 
    for (int i = 0; i < n; i++) 
        sum += a[i]; 
    double mean = (double)sum /  
                  (double)n; 
  
    // Compute sum squared  
    // differences with mean. 
    double sqDiff = 0; 
    for (int i = 0; i < n; i++)  
        sqDiff += (a[i] - mean) *  
                  (a[i] - mean); 
    return sqDiff / n; 
} 

void self_calib_IMU(void){
   
    //Check if stable readings ?

    int value_buffer[STABLE_BUF_SIZE] = {0};
    for (int i = 0; i < STABLE_BUF_SIZE; i++){
        refresh_imu();
        value_buffer[i] = yaw;
    }
    #ifdef DEBUG
    int test_variance = variance(value_buffer, STABLE_BUF_SIZE);
    pc.printf("the current variance is %d", variance(value_buffer, 10));
    #endif // DEBUG
    //Get the variance if stable move on.

    if(variance(value_buffer, STABLE_BUF_SIZE) < Stable_VARIANCE_YAW){
        buzzer_off();
        yaw_offset = yaw;
        bool turn_90degs = false;
        while (turn_90degs != true )
        {
        feed_enc();    
        //Turn the bot by +90degs.
        if(L_enc_position < 45 *ONE_DEG_YAW_ENC_COUNT){
            l_forward(MOTOR_TURN_SPEED);
        }
        else if(L_enc_position > 45*ONE_DEG_YAW_ENC_COUNT)
        {
          l_forward(0);
        }
        if((-R_enc_position) < (45*ONE_DEG_YAW_ENC_COUNT)){
            r_backward(MOTOR_TURN_SPEED);   
        }
        else if((-R_enc_position) > (45*ONE_DEG_YAW_ENC_COUNT))
        {
            r_backward(0);
        }
        if ((L_enc_position >= 45*ONE_DEG_YAW_ENC_COUNT) && (R_enc_position <= (-45*ONE_DEG_YAW_ENC_COUNT)))
        {
            turn_90degs = true;
        }
        }
        // Now it has turned 90 degs
        refresh_imu();
        wait(0.5);
        imu_calib_factor = (90)/(yaw - yaw_offset);
        pc.printf("The mult factor is %lf ", imu_calib_factor);
    
        
        //Now turn it back to -180 degs
        bool turn_back_180degs = false;
        while (turn_back_180degs != true )
        {   
        feed_enc();
        if(L_enc_position > (-45*ONE_DEG_YAW_ENC_COUNT)){
            l_backward(MOTOR_TURN_SPEED);
        }
        else
        {
            l_forward(0);
        }
        if(R_enc_position < (45*ONE_DEG_YAW_ENC_COUNT)){
            r_forward(MOTOR_TURN_SPEED);   
        }
        else
        {
            r_backward(0);
        }
        if ((L_enc_position <= (-45*ONE_DEG_YAW_ENC_COUNT)) && (R_enc_position >= (45*ONE_DEG_YAW_ENC_COUNT)))
        {
            turn_back_180degs = true;
        }

        }
    
        // Has turned backed 180 degs 
        //Recheck if calib factor gives correct readings 
        // ie if calibration is successful 
        refresh_imu();
        float new_angle = imu_calib_factor*(yaw - yaw_offset); 
        if ((new_angle < -60) && (new_angle > -120))
        {
        //victory beep
        buzzer_on();
        wait_ms(300);
        buzzer_off();
        wait_ms(300);
        
        buzzer_on();
        wait_ms(300);
        buzzer_off();
        wait_ms(300);
        
        }
        
        bool turn_back_0degs = false;
        while (turn_back_0degs != true )
        {   
            feed_enc();
            if(L_enc_position < (0*ONE_DEG_YAW_ENC_COUNT)){
                l_forward(MOTOR_TURN_SPEED);
            }
            else
            {
                l_forward(0);
            }
            if(R_enc_position > (0*ONE_DEG_YAW_ENC_COUNT)){
                r_backward(MOTOR_TURN_SPEED);   
            }
            else
            {
                r_backward(0);
            }
            if ((L_enc_position >= (0*ONE_DEG_YAW_ENC_COUNT)) && (R_enc_position <= (0*ONE_DEG_YAW_ENC_COUNT)))
            {
                turn_back_180degs = true;
            }

            #ifdef DEBUG
            pc.printf("The yaw offset is %lf ,and muly fact is %lf", yaw_offset, imu_calib_factor );
            #endif // DEBUG
        }
    }
    else
    {
        buzzer_on();
        self_calib_IMU();
    }
    
    
}
