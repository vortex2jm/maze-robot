#include "pid.h"

Pid::Pid(double kp, double ki, double kd) {
  this->kp = kp;
  this->ki = ki;
  this->kd = kd;
  this->integral = 0;
  this->last_error = 0;
}

double Pid::calculate(double error) {
  double proportional = error;

  this->integral += error;

  double derivative = error - last_error;
  this->last_error = error;

  double output = (kp * proportional) + (ki * this->integral) + (kd * derivative);
  return output;
}
