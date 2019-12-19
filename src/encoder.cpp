
#include "../include/commons.h"
#include "../include/encoder.h"

//GLOBAL VARS
int16_t EncoderPosition_TIM1 ;
int16_t EncoderPosition_TIM2 ;



/* 
    Connections Encoder 2
    PA_0 = Encoder_2 A   A0
    PA_1 = Encoder_2 B   A1
   
    Connections Encoder 1   
    PA_8 = Encoder_1 A   D7
    PA_9 = Encoder_1 B   D8 
*/



void EncoderInitialise_TIM2(void) {
    // configure GPIO PA0 & PA1 as inputs for Encoder
    RCC->AHB1ENR |= 0x00000001;  // Enable clock for GPIOA
 
    GPIOA->MODER   |= GPIO_MODER_MODER0_1 | GPIO_MODER_MODER1_1 ;           //PA0 & PA1 as Alternate Function   /*!< GPIO port mode register,               Address offset: 0x00      */
    GPIOA->OTYPER  |= GPIO_OTYPER_OT_0 | GPIO_OTYPER_OT_1 ;                 //PA0 & PA1 as Inputs               /*!< GPIO port output type register,        Address offset: 0x04      */
    GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR0 | GPIO_OSPEEDER_OSPEEDR1 ;     // Low speed                        /*!< GPIO port output speed register,       Address offset: 0x08      */
    GPIOA->PUPDR   |= GPIO_PUPDR_PUPDR0_1 | GPIO_PUPDR_PUPDR1_1 ;           // Pull Down                        /*!< GPIO port pull-up/pull-down register,  Address offset: 0x0C      */
    GPIOA->AFR[0]  |= 0x00000011 ;                                          //  AF01 for PA0 & PA1              /*!< GPIO alternate function registers,     Address offset: 0x20-0x24 */
    GPIOA->AFR[1]  |= 0x00000000 ;                                          //                                  /*!< GPIO alternate function registers,     Address offset: 0x20-0x24 */
   
    // configure TIM2 as Encoder input
    RCC->APB1ENR |= 0x00000001;  // Enable clock for TIM2
 
    TIM2->CR1   = 0x0001;     // CEN(Counter ENable)='1'     < TIM control register 1
    TIM2->SMCR  = 0x0003;     // SMS='011' (Encoder mode 3)  < TIM slave mode control register
    TIM2->CCMR1 = 0xF1F1;     // CC1S='01' CC2S='01'         < TIM capture/compare mode register 1
    TIM2->CCMR2 = 0x0000;     //                             < TIM capture/compare mode register 2
    TIM2->CCER  = 0x0011;     // CC1P CC2P                   < TIM capture/compare enable register
    TIM2->PSC   = 0x0000;     // Prescaler = (0+1)           < TIM prescaler
    TIM2->ARR   = 0xffffffff; // reload at 0xfffffff         < TIM auto-reload register
  
    TIM2->CNT = 0x0000;  //reset the counter before we use it  
}

void ZeroEncoderCount_TIM2() {
    TIM2->CNT=0 ; //reset count to zero
} 

void ZeroEncoderCount_TIM1() {
    TIM1->CNT=0 ; //reset count to zero
}

void EncoderInitialise_TIM1(void) {
    // configure GPIO PA8 & PA9 aka D7 & D8 as inputs for Encoder
    // Enable clock for GPIOA
    __GPIOA_CLK_ENABLE(); //equivalent from _hal_rcc.h
 
    //stm32f4xx.h 
    GPIOA->MODER   |= GPIO_MODER_MODER8_1 | GPIO_MODER_MODER9_1 ;           //PA8 & PA9 as Alternate Function   /*!< GPIO port mode register,               Address offset: 0x00      */
    GPIOA->OTYPER  |= GPIO_OTYPER_OT_8 | GPIO_OTYPER_OT_9 ;                 //PA8 & PA9 as Inputs               /*!< GPIO port output type register,        Address offset: 0x04      */
    GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR8 | GPIO_OSPEEDER_OSPEEDR9 ;     // Low speed                        /*!< GPIO port output speed register,       Address offset: 0x08      */
    GPIOA->PUPDR   |= GPIO_PUPDR_PUPDR8_1 | GPIO_PUPDR_PUPDR9_1 ;           // Pull Down                        /*!< GPIO port pull-up/pull-down register,  Address offset: 0x0C      */
    GPIOA->AFR[0]  |= 0x00000000 ;                                          //  AF01 for PA8 & PA9              /*!< GPIO alternate function registers,     Address offset: 0x20-0x24 */
    GPIOA->AFR[1]  |= 0x00000011 ;                                          //  bits here refer to gpio8..15    /*!< GPIO alternate function registers,     Address offset: 0x20-0x24 */
   
    // configure TIM2 as Encoder input
    //RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; //0x00000001;  // Enable clock for TIM2
    __TIM1_CLK_ENABLE();
 
    TIM1->CR1   = 0x0001;     // CEN(Counter ENable)='1'     < TIM control register 1
    TIM1->SMCR  = 0x0003;     // SMS='011' (Encoder mode 3)  < TIM slave mode control register
    TIM1->CCMR1 = 0xF1F1;     // CC1S='01' CC2S='01'         < TIM capture/compare mode register 1
    TIM1->CCMR2 = 0x0000;     //                             < TIM capture/compare mode register 2
    TIM1->CCER  = 0x0011;     // CC1P CC2P                   < TIM capture/compare enable register
    TIM1->PSC   = 0x0000;     // Prescaler = (0+1)           < TIM prescaler
    TIM1->ARR   = 0xffff;     // reload at 0xfffffff         < TIM auto-reload register
  
    TIM1->CNT = 0x0000;  //reset the counter before we use it  
}


void encoder_init(void){
    
    EncoderInitialise_TIM2() ;
    EncoderInitialise_TIM1() ;
  
}

int8_t encoder_cycle_count = 0; 

void cycle_slayer(int n_th_cycle, int tim1, int tim2){
    tim1 = tim1 + n_th_cycle*65535;
    tim2 = tim2 + n_th_cycle*65535;

}

#define DEBUG_VIA_PRINTF

void feed_enc(void) {
    
        
        //if( (EncoderPosition_TIM1 == 65536) || (EncoderPosition_TIM2 == 65536) ){
        //    ZeroEncoderCount_TIM1();
        //    ZeroEncoderCount_TIM2();
        //    encoder_cycle_count++;
        //}
        // Print Encoder Quadrature count to debug port every 0.5 seconds
        EncoderPosition_TIM1 = TIM1->CNT ; // Get current position from Encoder
        EncoderPosition_TIM2 = TIM2->CNT ; // Get current position from Encoder
        
        //cycle_slayer(encoder_cycle_count,EncoderPosition_TIM1,EncoderPosition_TIM2);

        #ifdef DEBUG_VIA_PRINTF
        printf("Left count = %i \n", EncoderPosition_TIM1); // Position of Left Encoder
        printf("Right count = %i \n", EncoderPosition_TIM2); // Position of Right Encoder
        #endif  
             
}