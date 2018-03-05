/*
 * Memory-Ansteuerung
 */

#ifndef Memory_h
#define Memory_h

#include "Arduino.h"
#include <Wire.h>

class Memory
{
  public:
    Memory(byte i2c_address);
    boolean memtest();
    boolean store(int address, byte data);
    byte read_byte(int address);
    boolean store_long(int address, long data);
    long read_long(int address);
  private:
    boolean write(byte device, byte address, byte data); 
    byte read(byte device, byte adress, byte number);
    byte device_1;
    byte device_2;
};

#endif
