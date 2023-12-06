#include <robot.h>

// Line sensors pins
#define CENTER_RIGHT_SENSOR 36
#define RIGHT_SENSOR 39
#define CENTER_VERTICAL_SENSOR 34
#define LEFT_SENSOR 35
#define CENTER_LEFT_SENSOR 32

// Engines pins
#define EN_1 33
#define CHA_M1 25
#define EN_2 26
#define CHA_M2 27

// Ultrasonic pins
#define ECHO_PIN  19
#define TRIGGER_PIN 16

Robot robot(
  CENTER_VERTICAL_SENSOR,
  LEFT_SENSOR,
  RIGHT_SENSOR,
  CENTER_LEFT_SENSOR,
  CENTER_RIGHT_SENSOR,
  EN_1,
  EN_2,
  CHA_M1,
  CHA_M2,
  ECHO_PIN,
  TRIGGER_PIN
);

void setup() {
  Serial.begin(9600);
  robot.setup();
}

void loop() {
  robot.read_line_sensors();
  RobotState state = robot.check_line_sensors_states();
  // Serial.println(state);

  switch (state) {
    case GO_FORWARD:
      robot.go_forward();
    break;

    case FOUR_WAY_CROSSING:
      robot.rotate_right_90deg();
      robot.go_forward();
      delay(500);
    break;

    case THREE_WAY_CROSSING:
      robot.rotate_right_90deg();
      robot.go_forward();
      delay(500);
    break;

    case TURN_LEFT:
      robot.rotate_right_90deg();
      robot.go_forward();
      delay(500);
    break;
    case TURN_RIGHT:
      robot.rotate_right_90deg();
      robot.go_forward();
      delay(500);
    break;

    default:
      robot.go_forward();
  }
}
