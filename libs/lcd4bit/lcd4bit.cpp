#include "lcd4bit.h"

Lcd4bit::Lcd4bit(int rs, int en, int db4, int db5, int db6, int db7, int rl_lcd) {
  this->rs = rs;
  this->en = en;
  this->rl_lcd = rl_lcd;
  this->dbs[0] = db4;
  this->dbs[1] = db5;
  this->dbs[2] = db6;
  this->dbs[3] = db7;
}

void Lcd4bit::init() {
  pinMode(this->rs, OUTPUT); 
  pinMode(this->en, OUTPUT); 
  pinMode(this->rl_lcd, OUTPUT); 
  digitalWrite(this->rl_lcd, HIGH);

  for (int i = 0; i < 4; i++) {
    pinMode(this->dbs[i], OUTPUT);
  }

  delay(20);		/* LCD Power ON Initialization time >15ms */

	this->command(0x02);	/* 4bit mode */
	this->command(0x28);	/* Initialization of 16X2 LCD in 4bit mode */
	this->command(0x0C);	/* Display ON Cursor OFF */
	this->command(0x06);	/* Auto Increment cursor */
	this->command(0x01);	/* Clear display */
	this->command(0x80);	/* Cursor at home position */
}

void Lcd4bit::command(byte command) {
  digitalWrite(this->rs, LOW);
  this->write_4bits(command >> 4);
  this->write_4bits(command);
}

void Lcd4bit::pulse_enable() {
  digitalWrite(this->en, LOW);
  delayMicroseconds(1);    
  digitalWrite(this->en, HIGH);
  delayMicroseconds(1);    // enable pulse must be >450 ns
  digitalWrite(this->en, LOW);
  delayMicroseconds(100);   // commands need >37 us to settle
}

void Lcd4bit::write_4bits(byte nibble) {
  for (int i = 0; i < 4; i++) {
    digitalWrite(this->dbs[i], (nibble >> i) & 0x01);
  }
  this->pulse_enable();
}

void Lcd4bit::print_char(char c) {
  digitalWrite(this->rs, HIGH);
  this->write_4bits(c >> 4);
  this->write_4bits(c);
}

void Lcd4bit::print(char *str) {
  char c; 
  while ((c = *str++)) {
    this->print_char(c);
  }
}
