#include "Arduino.h"
#include "Timetracking.h"


unsigned long millisnew1;
unsigned long millisold1;
unsigned long time1;
String time1string;

unsigned long millisnew2;
unsigned long millisold2;
unsigned long time2;
String time2string;

void starttimetracking()
{
  unsigned long time = millis();
  millisold1=time;
  millisold2=time;
}

void timetracking(int track, unsigned long time)
{
  if(track==1)
  {
    time1 = longtoTime(time,millisold1);
    time1string= millistoString(time1);
    millisold1=time;
  } 
  else if(track==2)
  {
    time2 = longtoTime(time,millisold2);
    time2string= millistoString(time2);
    millisold2=time;
  }
}

unsigned long getTime(int track)
{
  if(track==1)
  {
    return time1;
  }
  else if(track==2)
  {
    return time2;
  }
}

String getTimeString(int track)
{
  if(track==1)
  {
    return time1string;
  }
  else if(track==2)
  {
    return time2string;
  }
}

unsigned long longtoTime(unsigned long newmil, unsigned long oldmil)
{
  return newmil-oldmil;
}

String millistoString(unsigned long period)
{  
  int ms  = period %1000; // calc milliseconds
  period=period/1000;
  int sek  = period %60; // calc seconds
  period=period/60;
  int minu  = period %60; // calc minutes

  String sep0 = ":";  //Seperator, if ms <10/<100
  if(ms<10)
  {
    sep0 = ":00";
  }
  if(ms<100)
  {
    sep0 = ":0";
  }
  String sep1 = ":"; //seperator, if seconds <10
  if(sek<10)
  {
    sep1 = ":0";
  }
  String sep2 = ""; //seperator, if minutes <10
  if(minu<10)
  {
    sep2="0";
  }
  // assemble and return String
  return sep2 + (String)minu + sep1 + (String)sek + sep0 + (String)ms;
}
