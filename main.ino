#define SLC 3
#define SR 4
#define SC 5
#define SL 6
#define SRC 7
#define E_CHI 8
#define CHA_MI 9
#define E_CH2 10
#define CHA_M2 11
#define BUZZER 12
#define RL_LCD 13
#define SERVO 15
#define MOSI 37
#define SCL_MPU 36
#define TX0 35
#define RX0 34
#define SDA_MPU 33
#define MISO_ECHO 31
#define CLK 30
#define CS_SENSORS 29
#define RS 28
#define EN_TRIG 27
#define DB7 26
#define DB6 25
#define DB5 24
#define DB4 23

#define KP 
#define KI 
#define KD 

#define LEFT_MOTOR_SPEED
#define RIGHT_MOTOR_SPEED

int previous_error = 0;

double pid(double error);

void setup() {
}

void loop() {
  int error = calculate_error();
  pid_output = pid(error);
  previous_error = error;

  // NOTE: define pins
  analogWrite(OUT_PIN_LEFT_MOTOR, LEFT_MOTOR_SPEED + pid_output);
  analogWrite(OUT_PIN_RIGHT_MOTOR, RIGHT_MOTOR_SPEED - pid_output);

  delay(300);
}

double pid(double error) {
  double proportional = error;
  integral += error * dt; 
  double derivative = error - previous_error;
  previous = error;
  double output = (KP * proportional) + (KI * integral) + (KD * derivative);
  return output;
}

// the sensor values will be saved on the lsb positions
// the mask will be like: 000<SLC><SR><SC><SL><SRC>
unsigned char get_line_sensors_bitmask() {
  // change to analogRead
  int slc_val = digitalRead(SLC);
  int sr_val = digitalRead(SR);
  int sc_val = digitalRead(SC);
  int sl_val = digitalRead(SL);
  int src_val = digitalRead(SRC);
  
  return (slc_val << 4) | (sr_val << 3) | (sc_val << 2) | (sl_val << 1) | src_val;
}

int calculate_error() {
  int error = 0;
  unsigned char bitmask = get_line_sensors_bitmask();

  // think about the possible cases
  switch (bitmask) {
  }

  return error;
}
