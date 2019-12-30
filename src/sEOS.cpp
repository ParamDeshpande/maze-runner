#include "commons.h"
#include "sch_isr.h"

#include "stm32f4xx.h"

#include "sen_fusion.h"
#include "IR.h"
#include "imu.h"
#include "encoder.h"
#include "motor_commons.h"
#include "actuator.h"
#include "buzzer.h"
#include "../include/sen_fusion.h"
#include "calibration.h"
#include "sch_isr.h"


#define NUM_OF_TASKS 2
#define TICK_MS 5.0

uint32_t Task_count_G[NUM_OF_TASKS] = {0};

//TASK VECTOR 
// task 0  : calc state
// task 1  : printf
// task 2  :
// task 3  :
// task 4  :
// task 5  :
// task   :
// task   :
// task   :
// task   :
// task   :
// task   :
// task   :

//tick size 5MS

#define CALC_STATE_PERIOD (2)
#define PRINTF_PERIOD (200)

//Function prototypes
void sEOS_Update(void);
void toggle_LED(void);



volatile uint32_t ticks;
extern "C" void SysTick_Handler (void)
 {
//   ticks++;
   sEOS_Update();
 }

void sEOS_Init(void){
  
   SysTick_Config((SystemCoreClock / 1000)*TICK_MS);      /* Configure SysTick to generate an interrupt every millisecond */
  
  

}

void sEOS_Update(void){
    if(++Task_count_G[0] == CALC_STATE_PERIOD){
        calc_state();
        main_controller(1,0);   //rate of 1cm/sec
        Task_count_G[0] = 0;
    }

    if(++Task_count_G[1] == PRINTF_PERIOD){
        //calc_state();
        //pc.printf("and muly fact is %lf and yaw is %lf and delT is %llf ms \n\r", yaw_offset, imu_calib_factor, corrected_yaw , (delT/1000.0));
    
    }
}

DigitalOut myled3(LED1);
void toggle_LED(void){
    myled3= !myled3;
}
