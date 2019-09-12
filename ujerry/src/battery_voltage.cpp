#include"../include/main.h"
#include"../include/port.h"
#include"../include/constants.h"

void check_low_battery(void){
    int sensorValue = analogRead(A0);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 12V):
  //MCU get 1/3rd the battery voltage
  float battery_voltage = (sensorValue * (5.0 / 1023.0))*3;
  
    if(battery_voltage < minimum_battery_voltage){
        while(1){
            digitalWrite(builtin_led_Pin, LOW);
            delay(1000);
            digitalWrite(builtin_led_Pin, HIGH);
            delay(1000);
        }
    }
}
