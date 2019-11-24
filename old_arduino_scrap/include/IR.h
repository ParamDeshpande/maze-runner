
#ifndef IR_h
#define IR_h

#include "Arduino.h"
//*
class IR{

	int front_l_tx;
	int front_r_tx;
    int diag_l_tx;
	int diag_r_tx;
	int side_l_tx;
	int side_r_tx ;
	int front_l_rx;
	int front_r_rx;
	int side_l_rx;
	int side_r_rx;
	int diag_l_rx;
	int diag_r_rx;

	//DEfined for the class STATIC OR PRIVATE ?
	public:
		IR(int front_l_tx_Pin, int front_r_tx_Pin, int diag_l_tx_Pin, int diag_r_tx_Pin, int side_l_tx_Pin,int side_r_tx_Pin ,int front_l_rx_Pin, int front_r_rx_Pin, int side_l_rx_Pin, int side_r_rx_Pin, int diag_l_rx_Pin, int diag_r_rx_Pin);
		int irArray[3][4];
		int IR_readings[3][2];
		void powerUP_Tx(int ledPin);
		void powerDOWN_Tx(int ledPin);		
		float get_Rx(int rx_Pin);
		void reset_params(void);
		void map_IR(void) ;
		void fire_and_get(void);
		void display_IR(void) ;
//*/
};


extern IR IR_module;
extern int IR_readings[3][2];
void display_IMU(void);
//void init_IR(void);
#endif