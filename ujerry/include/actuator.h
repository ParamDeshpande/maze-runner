#ifndef ACTUATOR_H
#define ACTUATOR_H

class Motor{
  public:
    Motor(short int enable,short int input1,short int input2); //constructor
    void forward(unsigned int);

};

#endif // !ACTUATOR_H
