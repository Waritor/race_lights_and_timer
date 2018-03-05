// nur für 24C04 512kB Speicher

#include "Memory.h"
#include <Wire.h>

Memory::Memory(byte i2c_device)
{
  Wire.begin();
  device_1 = i2c_device;
  device_2 = i2c_device+1;
}

boolean Memory::memtest()
{
  Wire.beginTransmission(device_1);
  byte error = Wire.endTransmission();
  if(error != 0)
  {
    return false;
  }
  
  Wire.beginTransmission(device_2);
  error = Wire.endTransmission();
  if(error != 0)
  {
    return false;
  }
  return true;
}

boolean Memory::write(byte device, byte address, byte data)
{
  Wire.beginTransmission(device);
  Wire.write((byte)address);
  Wire.write(data);
  if(Wire.endTransmission()!=0)
  {
    return false;
  }
  return true; 
}

byte Memory::read(byte device, byte address, byte number)
{
  Wire.beginTransmission(device);
  Wire.write(address);
  if(Wire.endTransmission()!=0)
  {
    return false;
  }
  Wire.requestFrom((int)device,number);
  byte data = Wire.read();
  
  return data;
}

boolean Memory::store(int address, byte data)
{
  byte device = device_1;
  if(address>511) //wenn eine zu grosse adresse abgefragt wird
  {
    return false;
  }
  else if(address>255)
  {
    device = device_2;
    address = (byte)address-255;
  }
  return this->write(device, (byte)address, data);
}

byte Memory::read_byte(int address)
{
  byte device = device_1;
  if(address>512) //
  {
    return false;
  }
  else if(address>255)
  {
    device = device_2;
    address = (byte)address-255;
  }
  return this->read(device, (byte)address, 1);
}

boolean Memory::store_long (int address, long data)
{
  byte device = device_1;
  if(address>508)
  {
    return false;
  }
  else if(address>255)
  {
    device = device_2;
    address = (byte)address-255;
  }
  if(this->write(device, (byte)address, ((byte)data>>24)))
  {
    if(this->write(device, (byte)address, ((byte)data>>16)))
    {
      if(this->write(device, (byte)address, ((byte)data>>8)))
      {
        if(this->write(device, (byte)address, ((byte)data)))
        {
          return true;
        }
      }
    }
  }
  return false;
}

long Memory::read_long(int address)
{
  byte device = device_1;
  if(address>508) //
  {
    return false;
  }
  else if(address>255)
  {
    device = device_2;
    address = (byte)address-255;
  }
  long data;
  data  = (this->read(device, (byte)address  , 1) >> 24);
  data += (this->read(device, (byte)address+1, 1) >> 16);
  data += (this->read(device, (byte)address+2, 1) >> 8);
  data += (this->read(device, (byte)address+3, 1) >> 0);
  return data;
}

