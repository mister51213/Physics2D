#include "Timer.h"

Timer::Timer()
{
	Start();
}

void Timer::Start()
{
	// Number of seconds since 00:00 hours, Jan 1, 1970 UTC 
	// set current time
	start = clock.now();
	clockStopped = false;
}

void Timer::Stop()
{
	// TODO: CHECK FOR COUNTING OVERFLOW POSSIBILITY
	stop = clock.now();
	clockStopped = true;
}

long long Timer::Reset()
{
	// TODO: CHECK FOR COUNTING OVERFLOW POSSIBILITY
	Stop();
	const long long elapsed = MilliSPassed();
	Start();

	return elapsed;
}

long long Timer::MilliSPassed()
{
	return clockStopped ?
		duration_cast< milliseconds >( stop - start ).count() :
		duration_cast< milliseconds >( clock.now() - start ).count();	
}

float Timer::SecondsPassed()
{
	int mPassed = MilliSPassed();
	float seconds = (float)mPassed * 0.001f;
	return seconds;
}

bool Timer::EnoughTimePassed()
{
	// see if more than .250 seconds passed since last time
	if ( MilliSPassed() > 250 ) // milliseconds
	{
		Reset();
		return true;
	}
	return false;
}

