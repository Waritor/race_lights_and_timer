/*
 * Steuert die Ampel
 * Gelbe LED  an 0
 * Grüne LEDs an 6, 7
 * Rote  LEDs an 1, 2, 3, 4, 5
 */

#ifndef LightsRegister_h
#define LightsRegister_h

#include "Arduino.h"

const byte NONE  = 0;  //0
const byte GREEN = 192;//64+128
const byte YELLOW= 1;  //1
const byte RED1  = 2;  //2
const byte RED2  = 6;  //2+4
const byte RED3  = 14; //2+4+8
const byte RED4  = 30; //2+4+8+16
const byte RED5  = 62; //2+4+8+16+32
const byte ALL   = 255;// 1+2+4+8+16+32+64+128

const byte MAXSTARTPHASE = 7;

class LightsRegister
{
  public:
    LightsRegister(byte latch, byte clock, byte data);
    void init();
    void setLights(byte color);
    void startLights( byte startphase);

  private:
    byte _latch;
    byte _clock;
    byte _data;
    byte _lightsregister;
    
    void updateLightRegister();
    void updateLightRegister(byte shiftregister);
};

#endif
