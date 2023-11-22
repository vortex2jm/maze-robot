#ifndef LCD_4BIT_H
#define LCD_4BIT_H

#include "Arduino.h"

class Lcd4bit {
  private: 
    int rs, en, rl_lcd;
    int dbs[4];

    void command(byte c);
    void write_4bits(byte nibble);
    void pulse_enable();
    void print_char(char c);

  public:
    Lcd4bit(int rs, int en, int db4, int db5, int db6, int db7, int rl_lcd);
    void init();
    void print(char *c);
};

#endif
