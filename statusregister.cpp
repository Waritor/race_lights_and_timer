#include "Arduino.h"
#include "StatusRegister.h"

StatusRegister::StatusRegister(byte latch, byte clock, byte data)
{
  _latch = latch;
  _clock = clock;
  _data  = data;
}

void StatusRegister::init()
{
  pinMode(_data , OUTPUT);
  pinMode(_clock, OUTPUT);
  pinMode(_latch, OUTPUT);
  
  runStatus(true);
}

/**
 * Setze die Relais auf offen oder geschlossen, je nach übergebenem Status
 */
void StatusRegister::runStatus(boolean running)
{
  _running = running;
  for (int i=4 ; i<8; i++) {
    bitWrite(_statusregister, i, _running);
  }
  bitWrite(_statusregister, 0, !_running);
  bitWrite(_statusregister, 1, _running);
  updateStatusRegister();
}

boolean StatusRegister::getRunning()
{
  return _running;
}

void StatusRegister::updateStatusRegister()
{
  updateStatusRegister(_statusregister);
}

void StatusRegister::updateStatusRegister(byte shiftregister)
{
  digitalWrite(_latch, LOW);//
  shiftOut(_data, _clock, MSBFIRST, shiftregister);//Serial data output, high priority
  digitalWrite(_latch, HIGH);//Latch
}



