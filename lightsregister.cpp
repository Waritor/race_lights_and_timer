#include "Arduino.h"
#include "LightsRegister.h"

LightsRegister::LightsRegister(byte latch, byte clock, byte data)
{
  _latch = latch;
  _clock = clock;
  _data  = data;
}

void LightsRegister::init()
{
  pinMode(_data , OUTPUT);
  pinMode(_clock, OUTPUT);
  pinMode(_latch, OUTPUT);

  _lightsregister = GREEN;
  updateLightRegister();
}

void LightsRegister::updateLightRegister() 
{
  updateLightRegister(_lightsregister);
}

void LightsRegister::updateLightRegister(byte shiftregister)
{
  digitalWrite(_latch, LOW);//
  shiftOut(_data, _clock, MSBFIRST, shiftregister);//Serial data output, high priority
  digitalWrite(_latch, HIGH);//Latch
}

/**
 * Setze die Variable lights
 */
void LightsRegister::setLights(byte color) 
{
  _lightsregister = color;
  updateLightRegister();
}

void LightsRegister::startLights(byte startphase)
{
  switch (startphase) {
    case 0: 
      setLights(YELLOW);
      break;
    case MAXSTARTPHASE-6:
      setLights(NONE);
      break;
    case MAXSTARTPHASE-5:
      setLights(RED1);
      break;
    case MAXSTARTPHASE-4: 
      setLights(RED2);
      break;
    case MAXSTARTPHASE-3:
      setLights(RED3);
      break;
    case MAXSTARTPHASE-2: 
      setLights(RED4);
      break;
    case MAXSTARTPHASE-1: 
      setLights(RED5);
      break;
    case MAXSTARTPHASE-0: 
      setLights(GREEN);
      break;
  }//endswitch(startphase) 
}
 
