#ifndef ROBOT_H
#define ROBOT_H
#include "Wire.h"
#include <MPU6050_light.h>
#include <Ultrasonic.h>

enum Sensor {
  CENTER_VERTICAL_SENSOR,
  LEFT_SENSOR,
  RIGHT_SENSOR,
  CENTER_LEFT_SENSOR,
  CENTER_RIGHT_SENSOR
};

enum RobotState {
  FOUR_WAY_CROSSING,
  THREE_WAY_CROSSING,
  TURN_LEFT,
  TURN_RIGHT,
  GO_FORWARD
};

class Robot {
  private:
    int line_sensors_pins[5];
    int line_sensors_values[5] = {0};
    int en_m1, en_m2, chan_m1, chan_m2;
    int sensors_threshold, base_pwm_m1, base_pwm_m2;
    int echo_pin, trigger_pin;
    double kp;
    double previous_rotation_state;
    MPU6050 giroscope;
    Ultrasonic ultrasonic;

  public:
    Robot(
      int center_vertical,
      int left,
      int right,
      int center_left,
      int center_right,
      int en1_m1,
      int en_m2,
      int chan_m1,
      int chan_m2,
      int echo,
      int trigger
    );

    void stop();
    void setup();
    void go_forward();
    void read_line_sensors();
    void set_kp(double new_kp);
    void set_base_pwm_m2(int new_pwm);
    void set_base_pwm_m1(int new_pwm);
    bool is_on_black_cell(int sensor_val);
    RobotState check_line_sensors_states();
    void set_sensors_threshold(int new_threshold);
    void set_engine_pwm(unsigned int right, unsigned int left);
    void rotate_right_90deg();
    void rotate_left_90deg();
    void rotate_180deg();
    void read_distance();
};  

#endif
