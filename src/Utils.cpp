#include "../include/Utils.h"

void wait_for_G_press(void){

    while(true) // remain here until told to break
{
  if(Serial.available() > 0) // did something come in?
    if(Serial.read() == 'G') // is that something the char G?
      break;
}
}