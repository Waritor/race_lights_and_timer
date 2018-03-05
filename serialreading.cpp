#include "Arduino.h"
#include "SerialReading.h"
#include <HardwareSerial.h>

SerialReading::SerialReading(int baudrate)
{
  BAUDRATE= baudrate;
}

void SerialReading::init(HardwareSerial *serial)
{
  _serial = serial;
  inString = "";
}

/**
 * liest serial aus, wird ein \n gelesen, wird true zurückgegeben
 */
boolean SerialReading::serialRead()
{
  char inChar;
  if(_serial->available()>0) {    // Abfrage ob zeichen vorhanden
    inChar = _serial->read();     //lese Zeichen
    if(inChar != '\n'){         // solange keine Endzeichen
      inString += inChar;       // füge zum String hinzu
    }
    else {
      return true;
    }
  }//endif (serialavailable)
  return false;
}

String SerialReading::getMessage() 
{
  return inString;
}

void SerialReading::deleteMessage()
{
  inString="";
}

void SerialReading::serialPrintln(String message)
{
  _serial->println(message);
  _serial->flush();
}

