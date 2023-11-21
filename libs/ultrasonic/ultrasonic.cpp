#include "ultrasonic.h"

Ultrasonic::Ultrasonic(int echo_pin, int trigger_pin) {
  this->echo_pin = echo_pin;
  this->trigger_pin = trigger_pin;

  pinMode(trigger_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
}

int Ultrasonic::get_distance() {
  // Clears the trigPin
  digitalWrite(this->trigger_pin, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(this->trigger_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(this->trigger_pin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  long duration = pulseIn(this->echo_pin, HIGH);

  // Calculating the distance
  int distance = duration * 0.034 / 2;

  return distance;
}
