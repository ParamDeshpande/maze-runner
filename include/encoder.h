#ifndef ENCODER_H
#define ENCODER_H


//void EncoderInitialise_TIM2(void) ;
//void ZeroEncoderCount_TIM2() ;
//void ZeroEncoderCount_TIM1() ;
//void EncoderInitialise_TIM1(void) ;
void read_encoder() ;

#ifdef DEBUG
void display_encoder_counts(void) ;
void display_encoder_distance(void);
#endif //* DEBUG

#endif // !1