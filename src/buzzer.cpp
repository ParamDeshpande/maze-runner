#include "commons.h"
#include "buzzer.h"

DigitalOut buzzer(buzzer_Pin);     

void buzzer_on(void){
buzzer = HIGH;
}

void buzzer_off(void){
buzzer = LOW;
}
