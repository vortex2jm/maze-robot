#include "robot.h"
#include <Arduino.h>

// Right engine - 128 -> 255
// Left engine - 128 -> 0
#define KP 0.005        
#define BASE_PWM_M2 91  //81  old values
#define BASE_PWM_M1 160 //170 old values
#define ENGINE_STOP 128
#define THRESHOLD 2000
#define DISTANCE_LIMIT 40

//CONSTRUCTOR============================================================//
Robot::Robot(
  int center_vertical,
  int left,
  int right,
  int center_left,
  int center_right,
  int en_m1,
  int en_m2,
  int chan_m1,
  int chan_m2,
  int echo,
  int trigger,
  int servo
) : giroscope(Wire), ultrasonic(trigger, echo), servo_motor() {

  this->line_sensors_pins[CENTER_VERTICAL_SENSOR] = center_vertical;
  this->line_sensors_pins[LEFT_SENSOR] =  left;
  this->line_sensors_pins[RIGHT_SENSOR] =  right;
  this->line_sensors_pins[CENTER_LEFT_SENSOR] = center_left;
  this->line_sensors_pins[CENTER_RIGHT_SENSOR] = center_right;
  this->en_m1 = en_m1;
  this->en_m2 = en_m2;
  this->chan_m1 = chan_m1;
  this->chan_m2 = chan_m2;
  this->kp = KP;
  this->sensors_threshold = THRESHOLD;
  this->base_pwm_m1 = BASE_PWM_M1;
  this->base_pwm_m2 = BASE_PWM_M2;
  this->servo_pin = servo;
}

//============================================================//
void Robot::setup() {
  Wire.begin();
  // Setting up pins
  pinMode(this->line_sensors_pins[CENTER_LEFT_SENSOR], INPUT);
  pinMode(this->line_sensors_pins[RIGHT_SENSOR], INPUT);
  pinMode(this->line_sensors_pins[CENTER_VERTICAL_SENSOR], INPUT);
  pinMode(this->line_sensors_pins[LEFT_SENSOR], INPUT);
  pinMode(this->line_sensors_pins[CENTER_RIGHT_SENSOR], INPUT);
  pinMode(this->en_m1, OUTPUT);
  pinMode(this->en_m2, OUTPUT);
  pinMode(this->chan_m1, OUTPUT);
  pinMode(this->chan_m2, OUTPUT);
  
  // Setting up giroscope
  byte status = this->giroscope.begin();
  while(status!=0){ }
  delay(100);
  this->giroscope.calcOffsets(); // gyro and accelero
  
  // Setting up servo motor
  this->servo_motor.attach(this->servo_pin);
  this->servo_rotate_front();

  // Wait 1 second until loop starts
  delay(1000);
  digitalWrite(this->en_m1, HIGH);
  digitalWrite(this->en_m2, HIGH);
}

//============================================================//
void Robot::read_line_sensors() {
  this->line_sensors_values[CENTER_VERTICAL_SENSOR] = analogRead(this->line_sensors_pins[CENTER_VERTICAL_SENSOR]);
  this->line_sensors_values[LEFT_SENSOR] =  analogRead(this->line_sensors_pins[LEFT_SENSOR]);
  this->line_sensors_values[RIGHT_SENSOR] = analogRead(this->line_sensors_pins[RIGHT_SENSOR]);
  this->line_sensors_values[CENTER_LEFT_SENSOR] = analogRead(this->line_sensors_pins[CENTER_LEFT_SENSOR]);
  this->line_sensors_values[CENTER_RIGHT_SENSOR] = analogRead(this->line_sensors_pins[CENTER_RIGHT_SENSOR]);
}

//============================================================//
void Robot::set_engine_pwm(unsigned int right, unsigned int left){
  analogWrite(this->chan_m2, left);
  analogWrite(this->chan_m1, right);
  delay(100);
}

//============================================================//
void Robot::rotate_right_90deg(){
  this->giroscope.update();
  this->previous_rotation_state = this->giroscope.getAngleZ();
  double current_angle = this->previous_rotation_state;
  while(current_angle > (this->previous_rotation_state - 75)){
    this->giroscope.update();
    current_angle = this->giroscope.getAngleZ();
    this->set_engine_pwm(this->base_pwm_m2, this->base_pwm_m2);
    delay(5);
  }
}

//============================================================//
void Robot::rotate_left_90deg(){
  this->giroscope.update();
  this->previous_rotation_state = this->giroscope.getAngleZ();
  double current_angle = this->previous_rotation_state;
  while(current_angle < (this->previous_rotation_state + 75)){
    this->giroscope.update();
    current_angle = this->giroscope.getAngleZ();
    this->set_engine_pwm(this->base_pwm_m1, this->base_pwm_m1);
    delay(5);
  }
}

//============================================================//
void Robot::rotate_180deg(){
  this->giroscope.update();
  this->previous_rotation_state = this->giroscope.getAngleZ();
  double current_angle = this->previous_rotation_state;
  while(current_angle > (this->previous_rotation_state - 165)){
    this->giroscope.update();
    current_angle = this->giroscope.getAngleZ();
    this->set_engine_pwm(this->base_pwm_m2, this->base_pwm_m2);
    delay(5);
  }
}

//============================================================//
float Robot::read_distance(){
  float distance = this->ultrasonic.read(CM);
  delay(200);
  return distance;
}

//============================================================//
void Robot::servo_rotate_front(){
  this->servo_motor.write(90);
}

//============================================================//
bool Robot::check_wall(WallDirection d){
  switch (d) {
    case RIGHT:
      this->servo_motor.write(0);
      break;
    case LEFT:
      this->servo_motor.write(180);
      break;
    case FRONT:
      this->servo_motor.write(90);
      break;
    default:
      break;
    }
  delay(500);
  float distance = this->read_distance();
  if((int)distance < DISTANCE_LIMIT){
    return true;
  }
  return false;
}

//============================================================//
bool Robot::is_on_black_cell(int sensor_val) {
  return (sensor_val > this->sensors_threshold);
}

//============================================================//
void Robot::stop() {
  this->set_engine_pwm(ENGINE_STOP, ENGINE_STOP);
}

//============================================================//
RobotState Robot::check_line_sensors_states() {
  bool is_four_way_crossing = 
    this->is_on_black_cell(this->line_sensors_values[CENTER_LEFT_SENSOR]) 
    && this->is_on_black_cell(this->line_sensors_values[CENTER_RIGHT_SENSOR]) 
    && this->is_on_black_cell(this->line_sensors_values[CENTER_VERTICAL_SENSOR]);

  bool is_three_way_crossing = 
    this->is_on_black_cell(this->line_sensors_values[CENTER_LEFT_SENSOR])
    && this->is_on_black_cell(this->line_sensors_values[CENTER_RIGHT_SENSOR]);

  bool is_left_turn = this->is_on_black_cell(this->line_sensors_values[CENTER_LEFT_SENSOR]);

  bool is_right_turn = this->is_on_black_cell(this->line_sensors_values[CENTER_RIGHT_SENSOR]);

  if(is_four_way_crossing) return FOUR_WAY_CROSSING;
  if(is_three_way_crossing) return THREE_WAY_CROSSING;
  if(is_left_turn) return TURN_LEFT;
  if(is_right_turn) return TURN_RIGHT;
  
  return GO_FORWARD;
}

//============================================================//
void Robot::go_forward() {
  int pwm_m1 = this->base_pwm_m1 + (this->kp * this->line_sensors_values[LEFT_SENSOR]);
  int pwm_m2 = this->base_pwm_m2 - (this->kp * this->line_sensors_values[RIGHT_SENSOR]);
  this->set_engine_pwm(pwm_m1, pwm_m2);
}

//============================================================//
void Robot::set_kp(double new_kp) {
  this->kp = new_kp;
}

//============================================================//
void Robot::set_sensors_threshold(int new_threshold) {
  this->sensors_threshold = new_threshold;
}

//============================================================//
void Robot::set_base_pwm_m1(int new_pwm) {
  this->base_pwm_m1 = new_pwm;
}

//============================================================//
void Robot::set_base_pwm_m2(int new_pwm) {
  this->base_pwm_m1 = new_pwm;
}
