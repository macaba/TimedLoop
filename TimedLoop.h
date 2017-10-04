#ifndef TimedLoop_h
#define TimedLoop_h

#include <Arduino.h>
#include <stdint.h>

class TimedLoop {
  private:
    uint32_t timer;
    uint32_t time;
    const char* name;
    bool debug;
  public:
    void Setup(uint32_t loopTimeMicros);
    void Setup(uint32_t loopTimeMicros, const char* loopName);
    void Setup(uint32_t loopTimeMicros, const char* loopName, bool debugEnabled);
    void SetupMicros(uint32_t loopTime);
    void SetupMicros(uint32_t loopTime, const char* loopName);
    void SetupMicros(uint32_t loopTime, const char* loopName, bool debugEnabled);
    void SetupMillis(uint32_t loopTime);
    void SetupMillis(uint32_t loopTime, const char* loopName);
    void SetupMillis(uint32_t loopTime, const char* loopName, bool debugEnabled);
	void SetupFrequency(float frequency);
	void SetupFrequency(float frequency, const char* loopName);
	void SetupFrequency(float frequency, const char* loopName, bool debugEnabled);

    bool Iterate();
    bool Iterate(bool optionalOverrideCondition);
};

#endif

/*
To do:
- A setup option to specify behaviour when Iterate(optionalOverrideCondition) is true; do we reset loop timing or still iterate on every loop boundary therefore resulting in additional loops?
- A setup option to specify behaviour when loop iterations are missed; do we reset loop timing or still iterate on every loop boundary (as current), or do we try and catch up by performing faster loop iterations so the long term average is correct?
- A setup option for Absolute Timed Loops where the loop iteration must happen within a defined tolerance of the loop iteration interval, with the option to allow or disallow 'late' loops.
*/