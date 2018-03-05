#ifndef Timetracking_h
#define Timetracking_h

#include "Arduino.h"

void starttimetracking();
void timetracking(int track, unsigned long time);
unsigned long getTime(int track);
String getTimeString(int track);

unsigned long longtoTime(unsigned long newmil, unsigned long oldmil);
String millistoString(unsigned long period);

#endif

