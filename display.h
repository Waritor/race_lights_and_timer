/*
 * Einfach eine Maske für mich
 */

#ifndef Display_h
#define Display_h

#include "Arduino.h"
//#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

class Display : public LiquidCrystal_I2C
{
  public:
    Display(byte address, byte cols, byte rows);
    void init();
    void setbacklight(boolean light);
    void setCursor(byte col, byte line);
    void print(String );
    void clear();
  private:
    //LiquidCrystal_I2C * _lcd();
};

#endif
