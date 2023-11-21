#ifndef ULTRASONIC_H
#define ULTRASONIC_H

class Ultrasonic {
  private:
    int echo_pin, trigger_pin;

  public:
    Ultrasonic(int echo_pin, int trigger_pin);
    int get_distance();
};

#endif
