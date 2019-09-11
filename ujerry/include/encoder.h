#ifndef ENCODER_H
#define ENCODER_H


void EncoderInitialise_TIM2(void) ;
void ZeroEncoderCount_TIM2() ;
void ZeroEncoderCount_TIM1() ;
void EncoderInitialise_TIM1(void) ;
int read_encoder() ;

#endif // !1