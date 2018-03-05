#include "Arduino.h"
#include "display.h"

//#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

Display::Display(byte address, byte cols, byte rows):LiquidCrystal_I2C(address, cols, rows)
{
  //:LiquidCrystal_I2C(address, cols, rows);
  //_lcd = &lcd;
}

void Display::init()
{
    LiquidCrystal_I2C::init();
    LiquidCrystal_I2C::setBacklight(false);
}

void Display::setbacklight(boolean light)
{
  LiquidCrystal_I2C::setBacklight(light);
}

void Display::setCursor(byte col, byte row)
{
  LiquidCrystal_I2C::setCursor(col, row);
}
void Display::print(String message)
{
  LiquidCrystal_I2C::print(message);
}

void Display::clear()
{
  LiquidCrystal_I2C::clear();
}

