/*
 * Steuert die Relais zum schalten der Bahnen
 * Bahnrelais an Pin 4, 5, 6, 7
 * Rote Stop LED an Pin 0
 * Grüne LED an Pin 1
 * Pin 2 und 3 frei für weitere StatusLEDs oder Relais
 */

#ifndef StatusRegister_h
#define StatusRegister_h

#include "Arduino.h"

class StatusRegister
{
  public:
    StatusRegister(byte latch, byte clock, byte data);
    void init();
    void runStatus(boolean running);
    boolean getRunning();
    
  private:
    byte _latch;
    byte _clock;
    byte _data;
    byte _statusregister;
    boolean _running;
    
    void updateStatusRegister();
    void updateStatusRegister(byte shiftregister);
};

#endif
