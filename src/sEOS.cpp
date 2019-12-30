#include "commons.h"
#include "sch_isr.h"

#include "stm32f4xx.h"


uint32_t Task_count_G[NUM_OF_TASKS] = {0};

#define X_PERIOD 8

//Function prototypes
void sEOS_Update(void);
void toggle_LED(void);



volatile uint32_t ticks;
extern "C" void SysTick_Handler (void)
 {
//   ticks++;
   sEOS_Update();
 }

void sEOS_Init(const uint32_t TICK_MS){
  
   SysTick_Config((SystemCoreClock / 1000)*TICK_MS);      /* Configure SysTick to generate an interrupt every millisecond */
  
  

}

void sEOS_Update(void){
    if(++Task_count_G[0] == X_PERIOD){
        toggle_LED();
        Task_count_G[0] = 0;
    }
    // LED BLINKY CODE
  
}



DigitalOut myled3(LED1);
void toggle_LED(void){
    myled3= !myled3;
}
