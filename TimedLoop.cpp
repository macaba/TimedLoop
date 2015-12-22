#include "TimedLoop.h"

void TimedLoop::Setup(uint32_t loopTimeMicros, const char* loopName, bool debugEnabled)
{
  time = loopTimeMicros;
  name = loopName;
  debug = debugEnabled;
  timer = micros();
}

void TimedLoop::Setup(uint32_t loopTimeMicros, const char* loopName)
{
  Setup(loopTimeMicros, loopName, false);
}

void TimedLoop::Setup(uint32_t loopTimeMicros)
{
  Setup(loopTimeMicros, "Unnamed Loop", false);
}

void TimedLoop::SetupMicros(uint32_t loopTime, const char* loopName, bool debugEnabled){
  Setup(loopTime, loopName, debugEnabled);
}

void TimedLoop::SetupMicros(uint32_t loopTime, const char* loopName){
  Setup(loopTime, loopName);
}

void TimedLoop::SetupMicros(uint32_t loopTime){
  Setup(loopTime);
}

void TimedLoop::SetupMillis(uint32_t loopTime, const char* loopName, bool debugEnabled){
  Setup(loopTime * 1000, loopName, debugEnabled);
}

void TimedLoop::SetupMillis(uint32_t loopTime, const char* loopName){
  Setup(loopTime * 1000, loopName);
}

void TimedLoop::SetupMillis(uint32_t loopTime){
  Setup(loopTime * 1000);
}

bool TimedLoop::Iterate()
{
  uint32_t loopIntervals = 0;
  while((micros() - timer) >= time) {     //Discard missing loop iterations
    timer += time;
    loopIntervals++;
  }
  if((loopIntervals > 1) && debug) { 
    Serial.print("Warning: Lost loop iteration(s), Loop name: ");
    Serial.print(name);
    Serial.print(", Iterations lost: ");
    Serial.println(loopIntervals - 1);
  }
  return (loopIntervals > 0);
}

bool TimedLoop::Iterate(bool optionalOverrideCondition){
  if(optionalOverrideCondition)
    return true;
  else
    return Iterate();
}
