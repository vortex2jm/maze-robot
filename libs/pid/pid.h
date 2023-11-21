#ifndef PID_H
#define PID_H

#include "Arduino.h"

class Pid {
  private:
    double kp, ki, kd, integral, last_error;  

  public:
    Pid(double kp, double ki, double kd);
    double calculate(double error);
};

#endif
