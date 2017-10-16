#include "TimedLoop.h"

void TimedLoop::SetupMicros(uint32_t loopTimeMicros, const char* loopName, bool debugEnabled)
{
  time = loopTimeMicros;
  name = loopName;
  debug = debugEnabled;
  timer = micros();
}

void TimedLoop::SetupMicros(uint32_t loopTimeMicros, const char* loopName)
{
  SetupMicros(loopTimeMicros, loopName, false);
}

void TimedLoop::SetupMicros(uint32_t loopTimeMicros)
{
  SetupMicros(loopTimeMicros, "Unnamed Loop", false);
}

void TimedLoop::SetupMillis(uint32_t loopTime, const char* loopName, bool debugEnabled){
  SetupMicros(loopTime * 1000, loopName, debugEnabled);
}

void TimedLoop::SetupMillis(uint32_t loopTime, const char* loopName){
  SetupMicros(loopTime * 1000, loopName);
}

void TimedLoop::SetupMillis(uint32_t loopTime){
  SetupMicros(loopTime * 1000);
}

void TimedLoop::SetupFrequency(float frequency, const char* loopName, bool debugEnabled){
  SetupMicros(1000000/frequency, loopName, debugEnabled);
}

void TimedLoop::SetupFrequency(float frequency, const char* loopName){
  SetupMicros(1000000/frequency, loopName);
}

void TimedLoop::SetupFrequency(float frequency){
  SetupMicros(1000000/frequency);
}

void TimedLoop::UpdateFrequency(float frequency){
  time = (uint32_t)(1000000/frequency);
  timer = micros();
}

void TimedLoop::SetDebugCallback(void (*debugCallback)(char *)){
  _debugCallback = debugCallback;
}

bool TimedLoop::Iterate()
{
  uint32_t loopIntervals = 0;
  while((micros() - timer) >= time) {     //Discard missing loop iterations
    timer += time;
    loopIntervals++;
  }
  if((loopIntervals > 1) && debug) { 
	if(_debugCallback){
		_debugCallback((char*)printf("Warning: Lost loop iteration(s), Loop name: %s, Iterations lost: %i\n", name, (int)loopIntervals - 1));
	}
	else{
      Serial.printf("Warning: Lost loop iteration(s), Loop name: %s, Iterations lost: %i\n", name, (int)loopIntervals - 1);
	}
  }
  return (loopIntervals > 0);
}

bool TimedLoop::IterateWithOverride(bool optionalOverrideCondition){
  if(optionalOverrideCondition)
    return true;
  else
    return Iterate();
}

bool TimedLoop::IterateWithIgnore(bool optionalIgnoreCondition){
  if(optionalIgnoreCondition)
    return false;
  else
    return Iterate();
}
