// Pinos de controle do display LCD
const int rs = 12;
const int en = 11;
const int d4 = 5;
const int d5 = 4;
const int d6 = 3;
const int d7 = 2;

void setup() {
  // Configuração dos pinos como saída
  pinMode(rs, OUTPUT);
  pinMode(en, OUTPUT);
  pinMode(d4, OUTPUT);
  pinMode(d5, OUTPUT);
  pinMode(d6, OUTPUT);
  pinMode(d7, OUTPUT);

  // Inicialização do display
  lcd_command(0x33); // Inicialização do display
  lcd_command(0x32); // Inicialização do display
  lcd_command(0x28); // 4 bits, 2 linhas, 5x8 font
  lcd_command(0x0C); // Display ligado, cursor e blink desligados
  lcd_command(0x06); // Incrementa cursor
  lcd_command(0x01); // Limpa display
  delay(3);          // Aguarda a limpeza do display
}

void loop() {
  // Escreve no display
  lcd_setCursor(0, 0); // Posiciona o cursor na primeira linha, primeira coluna
  lcd_print("Hello, World!");

  delay(2000); // Aguarda por 2 segundos

  lcd_command(0x01); // Limpa o display
  delay(3);          // Aguarda a limpeza do display

  lcd_setCursor(0, 1); // Posiciona o cursor na segunda linha, primeira coluna
  lcd_print("Arduino!");

  delay(2000); // Aguarda por 2 segundos
}

// Função para enviar um comando para o display
void lcd_command(byte command) {
  digitalWrite(rs, LOW);
  lcd_nibble(command >> 4);
  lcd_nibble(command);
}

// Função para enviar um caractere para o display
void lcd_print(char c) {
  digitalWrite(rs, HIGH);
  lcd_nibble(c >> 4);
  lcd_nibble(c);
}

// Função para enviar 4 bits para o display
void lcd_nibble(byte nibble) {
  digitalWrite(d4, (nibble >> 0) & 0x01);
  digitalWrite(d5, (nibble >> 1) & 0x01);
  digitalWrite(d6, (nibble >> 2) & 0x01);
  digitalWrite(d7, (nibble >> 3) & 0x01);

  digitalWrite(en, HIGH);
  delayMicroseconds(1);
  digitalWrite(en, LOW);
  delayMicroseconds(100);
}

// Função para posicionar o cursor no display
void lcd_setCursor(byte col, byte row) {
  byte offset[] = {0x00, 0x40, 0x14, 0x54}; // Offset para cada linha do display
  lcd_command(0x80 | (col + offset[row]));
}
