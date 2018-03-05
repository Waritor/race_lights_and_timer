/*
 * 
 */

#ifndef SerialReading_h
#define SerialReading_h

#include "Arduino.h"
#include <HardwareSerial.h>

class SerialReading
{
  public:
    SerialReading(int baudrate);
    void init(HardwareSerial *serial);
    boolean serialRead();
    String getMessage();
    void deleteMessage();
    void serialPrintln(String message);
  private:
    int BAUDRATE;
    HardwareSerial * _serial;
    String inString;
};


#endif
