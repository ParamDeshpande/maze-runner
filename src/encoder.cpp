//#include "Arduino.h"
#include "../include/commons.h"

#include "../include/encoder.h"
#include "mbed.h"

// Hardware Quadrature Encoder ABZ for Nucleo F401RE
// Output on debug port to host PC @ 9600 baud
// 
// By Nigel Webb, November 2014

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


void read_encoder() {
    
    EncoderInitialise_TIM2() ;
    EncoderInitialise_TIM1() ;
       
    int16_t EncoderPosition_TIM1 ;
    int16_t EncoderPosition_TIM2 ;
    
    
    
        // Print Encoder Quadrature count to debug port every 0.01 seconds 10ms
        EncoderPosition_TIM1 = TIM1->CNT ; // Get current position from Encoder
        EncoderPosition_TIM2 = TIM2->CNT ; // Get current position from Encoder
        bt.printf("Left count = %d ", EncoderPosition_TIM1); // Position of Left Encoder
        bt.printf("Right count = %d \r\n", EncoderPosition_TIM2); // Position of Right Encoder
        //wait(0.01);
    
       
}








#ifdef DEBUG_ENCODERSS
/* 
    Connections Encoder 2 aka RIGHT
    PA_0 = Encoder_2 A   A0
    PA_1 = Encoder_2 B   A1
   
    Connections Encoder 1  aka LEFT 
    PA_8 = Encoder_1 A   D7
    PA_9 = Encoder_1 B   D8 
//*/

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

double left_enc_dist =  0;
double right_enc_dist = 0;

void read_encoder() {
    
    EncoderInitialise_TIM2() ;
    EncoderInitialise_TIM1() ;
       
    int16_t EncoderPosition_TIM1 ;
    int16_t EncoderPosition_TIM2 ;
    
        // Print Encoder Quadrature count to debug port every 0.5 seconds
        EncoderPosition_TIM1 = TIM1->CNT ; // Get current position from Encoder
        EncoderPosition_TIM2 = TIM2->CNT ; // Get current position from Encoder
        left_enc_dist = EncoderPosition_TIM1;
        right_enc_dist = EncoderPosition_TIM2;
        bt.printf("Left count = %i  ", EncoderPosition_TIM1); // Position of Left Encoder
        bt.printf("Right count = %i \r\n", EncoderPosition_TIM2); // Position of Right Encoder
        
        /*printf("Left count = %i \n", EncoderPosition_TIM1); // Position of Left Encoder
        Serial.print("Left count =");
        Serial.println(EncoderPosition_TIM1);

        Serial.print("right count =");
        Serial.println(EncoderPosition_TIM2);
        */
        //delay(10);//10Ms delay added by Param   
}       
void display_encoder_counts(void){
        Serial.print("Left count =");
        Serial.println(EncoderPosition_TIM1);

        Serial.print("right count =");
        Serial.println(EncoderPosition_TIM2);
}


void display_encoder_distance(void){
        Serial.print("Left distance =");
        Serial.println(left_enc_dist);

        Serial.print("right distance =");
        Serial.println(right_enc_dist);
}
#endif // DEBUG
