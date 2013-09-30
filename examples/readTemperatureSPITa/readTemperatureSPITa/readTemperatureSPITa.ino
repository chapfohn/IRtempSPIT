 //File:    readTemperatureSIPITino
 //version: 1.0
 //Author:  Andy Gelme (@geekscape)
 //License: GPLv3
 
 //As modified by Colin Chapman [ChapLab]
 
 
 //For more information see www.freetronics.com/irtemp
 
 //IRTemp library uses an Arduino interrupt:
 //If PIN_CLOCK = 2, then Arduino interrupt 0 is used
 //If PIN_CLOCK = 3, then Arduino interrupt 1 is used
 
 //For the control of a relay interface to 12v motor
 //Connect relay to pin 07

#include "IRTemp.h"

static const byte PIN_DATA    = 2;
static const byte PIN_CLOCK   = 3;  // Must be either pin 2 or pin 3
static const byte PIN_ACQUIRE = 4;

int motor = 7;//connect relay for motor control to pin 07, do not connect motor directly

static const bool SCALE=false;  // Celcius: false, Farenheit: true

IRTemp irTemp(PIN_ACQUIRE, PIN_CLOCK, PIN_DATA);

void setup(void) {
  pinMode(motor, OUTPUT);//set motor pin to output
  Serial.begin(9600);//set new baud rate
  Serial.println("IRTemp example");//for the purposes of debug
  Serial.println("~~~~~~~~~~~~~~");//for the purposes of debug
}

void loop(void) {
  float irTemperature = irTemp.getIRTemperature(SCALE);
  printTemperature("IR", irTemperature);//for the purposes of debug

  float ambientTemperature = irTemp.getAmbientTemperature(SCALE);
  printTemperature("Ambient", ambientTemperature);//for the purposes of debug
  
  if (irTemperature < 150)//25% duty cycle
  {
   digitalWrite(motor, HIGH);   // turn the LED on (HIGH is the voltage level)
   delay(15);                   // wait for 15 milliseconds
   digitalWrite(motor, LOW);    // turn the LED off by making the voltage LOW
   delay(45);                   // wait for 45 milliseconds 
  }
  
  else if (irTemperature >= 150 && irTemperature < 200)//30% duty cycle
  {
   digitalWrite(motor, HIGH);   // turn the LED on (HIGH is the voltage level)
   delay(20);                   // wait for 20 milliseconds
   digitalWrite(motor, LOW);    // turn the LED off by making the voltage LOW
   delay(40);                   // wait for 40 milliseconds 
  }
  
  else //50% duty cycle
  {
   digitalWrite(motor, HIGH);   // turn the LED on (HIGH is the voltage level)
   delay(30);                   // wait for 30 milliseconds
   digitalWrite(motor, LOW);    // turn the LED off by making the voltage LOW
   delay(30);                   // wait for 30 milliseconds 
  }
  
  delay(60000);//sample once per second
}

void printTemperature(
  char  *type,
  float  temperature) {

  Serial.print(type);
  Serial.print(" temperature: ");//for the purposes of debug

  if (isnan(temperature)) {
    Serial.println("Failed");//for the purposes of debug
  }
  else {
    Serial.print(temperature);
    Serial.println(SCALE  ?  " F"  :  " C");//for the purposes of debug
  }
}
