#include <Servo.h>

Servo meuServo;  // Cria um objeto Servo para controlar um servo

#define servoPin 13;  // Especifique o pino PWM ao qual o servo está conectado

void setup() {
  meuServo.attach(servoPin);  // Inicializa o objeto Servo
}

void loop() {
  // Mova o servo de 0 a 180 graus
  for (int grau = 0; grau <= 180; grau++) {
    meuServo.write(grau);  // Define a posição do servo
    delay(15);  // Aguarda um curto período para o servo atingir a posição
  }

  delay(1000);  // Aguarda 1 segundo

  // Mova o servo de 180 a 0 graus
  for (int grau = 180; grau >= 0; grau--) {
    meuServo.write(grau);  // Define a posição do servo
    delay(15);  // Aguarda um curto período para o servo atingir a posição
  }
  delay(1000);  // Aguarda 1 segundo
}


// void loop() {
  // Move o servo motor para a posição inicial
  // meuServo.write(0);
  // delay(1000);
// 
  // Move o servo motor para a posição central
  // meuServo.write(90);
  // delay(1000);
// 
  // Move o servo motor para a posição final
  // meuServo.write(180);
  // delay(1000);
// }