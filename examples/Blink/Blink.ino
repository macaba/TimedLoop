#include "TimedLoop.h"

const int ledPin = 25;
const int adcPin = A0;

TimedLoop ledBlinkLoop;
TimedLoop adcAcquireLoop;
TimedLoop serialTxLoop;

void setup() {
  //ledBlinkLoop.Setup(1000000);                              //The shortest way to set up a timed loop. Loop name will be "Unnamed Loop". Number is in units of microseconds.
  //ledBlinkLoop.SetupMicros(1000000, "LED Blink Loop");      //Setup(...) is shorthand for SetupMicros(...)
  //ledBlinkLoop.Setup(1000000, "LED Blink Loop", true);      //Debug = enabled; library will log to Serial if loop iterations are missed
  ledBlinkLoop.SetupMillis(1000, "LED Blink Loop", true);     //SetupMillis(...) might be easier than converting to microseconds.
  adcAcquireLoop.SetupMillis(2000, "ADC Acquire Loop", true); //If this is set to 200ms, then a warning of lost loop iterations will be seen in the Serial output due to LED loop taking too long.
  serialTxLoop.SetupMillis(500, "Serial Tx Loop", true);      //Just another loop to play with
  
  pinMode(ledPin, OUTPUT);
  pinMode(adcPin, INPUT);
}

void loop() {
  if(ledBlinkLoop.Iterate()){
    Serial.println("LED blink");
    digitalWrite(ledPin, HIGH);
    delay(100);
    digitalWrite(ledPin, LOW);
    delay(100);
  }
  
  if(adcAcquireLoop.Iterate()){
    int value = analogRead(adcPin);
    Serial.print("Analog 0 is: ");
    Serial.println(value);
  }
  
  if(serialTxLoop.Iterate()){
    Serial.println("Hello World!");
  }
}