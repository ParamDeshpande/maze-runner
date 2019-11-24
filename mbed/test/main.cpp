
#include "mbed.h"

#include "../include/Utils.h"

#define SIZE 200
char ch[SIZE];
 

 
int main() {

  int i = 1;
    bluetooth_setup();
  while(1) { 
      wait(1);
      //bt_str(ch);
      bt.printf("CAN YO UREAD \n");
      bt_nline();

    }
}
 