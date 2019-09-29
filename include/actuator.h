#ifndef ACTUATOR_H
#define ACTUATOR_H
#include "../include/commons.h"

class Motor{
  public:
    Motor(PinName enable,PinName input1,PinName input2); //constructor
    void forward(float);
    void backward(float);

};

#endif // !ACTUATOR_H
