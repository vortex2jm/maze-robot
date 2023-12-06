// Sensors
#define CENTER_RIGHT_SENSOR 36
#define RIGHT_SENSOR 39
#define CENTER_VERTICAL_SENSOR 34
#define LEFT_SENSOR 35
#define CENTER_LEFT_SENSOR 32

// Right engine - 128 -> 255
#define EN_1 33
#define CHA_M1 25

// Left engine - 128 -> 0
#define EN_2 26
#define CHA_M2 27

// Medium value between light sensors values
#define TRESHOLD 2000

//SETUP==================================================//
void setup() {
  // Setting up pins
  pinMode(CENTER_LEFT_SENSOR,INPUT);
  pinMode(RIGHT_SENSOR,INPUT);
  pinMode(CENTER_VERTICAL_SENSOR,INPUT);
  pinMode(LEFT_SENSOR,INPUT);
  pinMode(CENTER_RIGHT_SENSOR,INPUT);
  pinMode(CHA_M1, OUTPUT);
  pinMode(EN_1, OUTPUT);
  pinMode(CHA_M2, OUTPUT);
  pinMode(EN_2, OUTPUT);

  // Enabling engines
  digitalWrite(EN_1, HIGH);
  digitalWrite(EN_2, HIGH);

  Serial.begin(9600);
}

//LOOP==================================================//
void loop() {
  int vertical_center_motor_val = analogRead(CENTER_VERTICAL_SENSOR);
  Serial.println(vertical_center_motor_val);
  
  // is on a black cell
  if (vertical_center_motor_val > TRESHOLD) {
    analogWrite(CHA_M1, 170);
    analogWrite(CHA_M2, 80);
    delay(200);
  }else {
    digitalWrite(EN_1, LOW);
    digitalWrite(EN_2, LOW);
  }
}
