#include "LightsRegister.h"
#include "StatusRegister.h"
#include "SerialReading.h"
#include "Display.h"
#include "Timetracking.h"
#include "Memory.h"

//PINS 
// pin 4,5,6 und 10,11,12 bereits von Registern belegt //nicht als Variablen, um Speicher zu sparen
// pin A4(SDA) und A5(SCL) für I2C (Displays) belegt   //nciht als Variablen, um Speicher zu sparen
const byte chaostaster = 8; //pin chaostaster
const byte starttaster = 9; //pin starttaster
const byte intsensor1 = 2;  // Pins for interrupt 2,3 auf uno
const byte intsensor2 = 3;

//CONST
const int BAUDRATE = 19200;

//Startvariablen
boolean starting = false;
byte startphase = 0;
long startbegin = 0;
long chaostime  = 0;
long starttime  = 0;
int startinterval = 1000;

//Variablen Zeitnahme
volatile unsigned long millis1=0;
volatile bool newtime1=false;
volatile unsigned long millis2=0;
volatile bool newtime2=false;

//Klassen
SerialReading serial(BAUDRATE);
StatusRegister sreg(11,12,10); //(latchpin, clockpin, datapin) //Status und Relaisregister
LightsRegister lreg(5 ,6 ,4 ); //(latchpin, clockpin, datapin) //Ampelregister
Display display1(0x27,16,2);   // set the LCD address to 0x27 for a 16 chars and 2 line display
Display display2(0x3F,16,2);   // set the LCD address to 0x3f for a 16 chars and 2 line display
Memory mem(0x50);

//Interrupts
void interrupt1()
{
  millis1=millis();
  newtime1=true;
}

void interrupt2()
{
  millis2=millis();
  newtime2=true;
}

//Setup-Routine
void setup() 
{
  //Serial initialisieren
  Serial.begin(BAUDRATE);
  serial.init(&Serial);
  serial.serialPrintln("Initialisierung");

  //Register initialisieren
  sreg.init();
  lreg.init();

  //Displays initialisieren
  display1.init();
  display1.setbacklight(true);
  display1.clear();
  display1.setCursor(0,0);
  //display1.print("Bereit");  //Test
  
  display2.init();
  display2.setbacklight(true);
  display2.clear();
  display2.setCursor(0,0);
  //display2.print("Bereit"); //Test
  
  //Interrupts initialisieren
  pinMode(intsensor1,INPUT);
  attachInterrupt(digitalPinToInterrupt(intsensor1), interrupt1, RISING);
  pinMode(intsensor2,INPUT);
  attachInterrupt(digitalPinToInterrupt(intsensor2), interrupt2, RISING);

  //Taster initialisieren
  pinMode(chaostaster, INPUT);
  pinMode(starttaster, INPUT);

  //Register aus Start setzen
  lreg.setLights(GREEN); //Ampel auf grün
  sreg.runStatus(true); // Schalte die Fahrbahnen/Statuslichter an
  
  serial.serialPrintln("ready");
}

//Loop
void loop() 
{
  if(serial.serialRead())
  {
    String command = serial.getMessage();
    serial.deleteMessage();
    //TODO command
  }

  if(digitalRead(chaostaster) && sreg.getRunning()) // Stoppe alles, Ampel rot, ...
  {
    sreg.runStatus(false);
    chaostime = millis();
    lreg.setLights(YELLOW+RED5);
    serial.serialPrintln("chaos_trigger");
  } //endif Chaostaster
  
  if(digitalRead(starttaster) && !sreg.getRunning() && !starting)
  {
    starting = true;
    serial.serialPrintln("start_trigger");
  } //endif Starttaster
  
  if(starting)
  {
    if(startbegin+startphase*startinterval < millis())
    {
      startlights();
    }
    if(startphase>MAXSTARTPHASE) //Wenn die Startphase vorbei ist, und die Ampel grün zeigt
    {
      sreg.runStatus(true); // Relais wieder einschalten
      starttime = millis(); // Restartzeit merken
      serial.serialPrintln("restart"); // nach aussen mitteilen
      //racetimingstart(); 
      
      starting = false;
      startphase = 0;
      startbegin = 0;
    }//endif(startphase);
  }//endif(starting);

  if(newtime1)
  {
    timetracking(1, millis1);
    newtime1=false;
    display1.setCursor(0,1);
    display1.print("Track1: " + getTimeString(1));
    serial.serialPrintln("track1_" + getTime(1));
  }
  if(newtime2)
  {
    timetracking(2, millis2);
    newtime2=false;
    display2.setCursor(0,1);
    display2.print("Track2: " + getTimeString(2));
    serial.serialPrintln("track2_" + getTime(2));
  }
  
}

void startlights() 
{
  if(startphase == 0)
  {
    sreg.runStatus(false);
    startbegin = millis();
  }
  lreg.startLights(startphase);
  startphase++;
}






