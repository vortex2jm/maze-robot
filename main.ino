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

#define KP 0.005

int center_vertical_sensor_value=0;
int left_sensor_value=0;
int right_sensor_value=0;
int center_left_sensor_value=0; 
int center_right_sensor_value=0;

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
  center_vertical_sensor_value = analogRead(CENTER_VERTICAL_SENSOR);
  left_sensor_value = analogRead(LEFT_SENSOR);
  right_sensor_value = analogRead(RIGHT_SENSOR);
  center_left_sensor_value = analogRead(CENTER_LEFT_SENSOR);
  center_right_sensor_value = analogRead(CENTER_RIGHT_SENSOR); 

  Serial.println(left_sensor_value, right_sensor_value);

  analogWrite(CHA_M1, 160 + (KP * left_sensor_value));
  analogWrite(CHA_M2,86 - (KP * right_sensor_value));
  delay(100);

  if(center_left_sensor_value > TRESHOLD || center_right_sensor_value > TRESHOLD){
    digitalWrite(EN_1, LOW);
    digitalWrite(EN_2, LOW);
  }
}
