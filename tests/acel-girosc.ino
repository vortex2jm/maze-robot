#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

void setup() {
  Serial.begin(9600);
  
  // Inicialização do sensor
  Wire.begin();
  mpu.initialize();
  
  // Verifica se o sensor está conectado corretamente
  if (!mpu.testConnection()) {
    Serial.println("MPU6050 connection failed.");
    while (1);
  }
}

void loop() {
  // Lê os dados do acelerômetro e giroscópio
  mpu.getMotion6();
  
  // Exibe os dados
  Serial.print("Acelerômetro:\t");
  Serial.print(mpu.getAccelerationX());
  Serial.print("\t");
  Serial.print(mpu.getAccelerationY());
  Serial.print("\t");
  Serial.print(mpu.getAccelerationZ());
  Serial.print("\t\tGiroscópio:\t");
  Serial.print(mpu.getRotationX());
  Serial.print("\t");
  Serial.print(mpu.getRotationY());
  Serial.print("\t");
  Serial.println(mpu.getRotationZ());
  
  delay(1000);
}
