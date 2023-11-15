#include <Wire.h>

#define LCD_ADDR 0x27 // Endereço I2C do LCD

void lcdSendCommand(uint8_t command) {
  Wire.beginTransmission(LCD_ADDR);
  Wire.write(0x00); // Modo de comando
  Wire.write(command);
  Wire.endTransmission();
  delay(2); // Aguarda o LCD processar o comando
}

void lcdSendData(uint8_t data) {
  Wire.beginTransmission(LCD_ADDR);
  Wire.write(0x40); // Modo de dados
  Wire.write(data);
  Wire.endTransmission();
}

void lcdInit() {
  lcdSendCommand(0x38); // Configuração de 2 linhas e 5x8 matriz de pontos
  lcdSendCommand(0x0C); // Display ligado, cursor e blink desligados
  lcdSendCommand(0x06); // Incrementa o cursor automaticamente
  lcdSendCommand(0x01); // Limpa o display
  delay(2);
}

void lcdSetCursor(uint8_t col, uint8_t row) {
  uint8_t row_offsets[] = { 0x00, 0x40, 0x14, 0x54 };
  lcdSendCommand(0x80 | (col + row_offsets[row]));
}

void lcdPrint(char* str) {
  while (*str) {
    lcdSendData(*str);
    str++;
  }
}

void setup() {
  Wire.begin();
  lcdInit();
}

void loop() {
  lcdSetCursor(0, 0);
  lcdPrint("Hello, Arduino!");
  delay(2000);
  lcdSendCommand(0x01); // Limpa o display
  delay(500);
}
