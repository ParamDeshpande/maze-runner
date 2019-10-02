/* xej-Nucleo-F401RE-and-HC05-Bluetooth.cpp
  Test Nucleo-F401RE with HC05 Bluetooth adapter
  
  Wanted to use it for upload of telemetry
  type a command and bt port and it will be echoed back
  
  
  pin-HC05  Pin-MBed
   TX   --- PA_12
   RX   --- PA_11
   +5V  --- +5 on CN6
               Also worked on 3.3V on CN6
   GND  --- GND on CN6
   STATE--- NC - not connected
   EN   --- NC - not connected
  
   If you cycle power on mbed you may need to close 
   and re-open the port connection which
   is pretty easy when using RealTerm.
  
   tested with Honbay® Wireless Bluetooth Host Serial Transceiver Module   
   Draws about 30mA when starting then drops back
   to 10mA when idle with a jump to about 20 mA 
   when transmitting.
   
   ***
  * By Joseph Ellsworth CTO of A2WH
  * Take a look at A2WH.com Producing Water from Air using Solar Energy
  * March-2016 License: https://developer.mbed.org/handbook/MIT-Licence 
  * Please contact us http://a2wh.com for help with custom design projects.
  ***
  
*/
#include "commons.h"
#include "multi-serial-command-listener.h"
#include "IR.h"
#include "imu.h"
#include "motor_commons.h"

char myCommand[SCMD_MAX_CMD_LEN+1];


//------------------------------------
// RealTerm or Teraterm config
// 9600 bauds, 8-bit data, no parity
//------------------------------------

//Serial hc05(D1, D0); // PA_2, PA_3 This one does not work because redirected to USBTX, USBRX
//                     //  can be fixed by changing solder bridges                      
Serial bt(PA_11, PA_12);  // This one works
Serial pc(USBTX, USBRX); 
 
//DigitalOut myled(LED1); DEFINED ELSEWHERE


//FUNCTION PROTOTYPES
void commandCallback(char *, void *); 


int main() {
  /*MAIN SETUP BEGINS HERE*/
  pc.baud(9600);
  bt.baud(9600);

  int i = 1;
  struct SCMD *cmdProc = scMake(&bt, commandCallback, NULL)  ;

  pc.printf("Test HC05 Bluetooth Connection !\r\n");
  imu_setup();
  
  /*MAIN SETUP ENDS HERE*/
  
  while(1) { 
    /*LOOP CODE BEGINS HERE*/
      wait(1);
      //IR_module.fire_and_get();
      refresh_imu();  
      
      bt.printf("PA_11/PA_12 %d seconds\r\n", i);
      /*bt.printf("front_left_IR value %d \r\n", front_left_IR);
      myled = !myled;
      if (myCommand[0] != 0) {     
          pc.printf("Command Recieved =%s\r\n", myCommand);
          bt.printf("\r\nCommand Recieved =%s\r\n", myCommand);
          if (strcmp(myCommand,"clear") == 0) {
            i = 0;
          }
          myCommand[0] = 0; // clear until we recieve the next command
      }        
    /*LOOP CODE ENDS HERE*/
  }

}




//UTILITY FUNCTION
void commandCallback(char *cmdIn, void *extraContext) {
  strcpy(myCommand, cmdIn);
  // all our commands will be recieved async in commandCallback
  // we don't want to do time consuming things since it could
  // block the reader and allow the uart to overflow so we simply 
  // copy it out in the callback and then process it latter. 
  
  // See data_log one of dependants of this library for example 
  // of using *extraContext
}
