#pragma once

#include <chrono>
#include <time.h>

using namespace std::chrono;
// TODO: will this cause a conflict w Includes.h?

class Timer
{
public:
	Timer();
	~Timer() = default;

	void Start();
	void Stop();
	long long Reset();
	// Function returns a 64bit long long int in milliseconds
	long long MilliSPassed();

	float SecondsPassed();

	bool EnoughTimePassed();

private:
	// This is a counter that gets updated every nanosecond
	high_resolution_clock clock; // platform dependent implementation
	time_point<high_resolution_clock> start, stop;
	bool clockStopped = false;
};
