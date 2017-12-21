#pragma once

#include "mbed.h"

namespace Seeed {

/////////////////////////////////////////////////////////////////////
// Debug

class Debug {

public:
	static void Print(const char* format, ...);
	static void Println(const char* format, ...);

};

/////////////////////////////////////////////////////////////////////
// Stopwatch

class Stopwatch : private Timer {

public:
	Stopwatch() : Timer()
	{
	}

	void Restart()
	{
		stop();
		reset();
		start();
	}

	int ElapsedMilliseconds()
	{
		return read_ms();
	}

};

/////////////////////////////////////////////////////////////////////

} // namespace seeed
