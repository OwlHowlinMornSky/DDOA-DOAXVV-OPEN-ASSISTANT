#include "Sleep.h"

#include <Windows.h>

namespace ohms {

void sleep(Time time) {
	// Get the supported timer resolutions on this system
	TIMECAPS tc;
	timeGetDevCaps(&tc, sizeof(TIMECAPS));

	// Set the timer resolution to the minimum for the Sleep call
	timeBeginPeriod(tc.wPeriodMin);

	// Wait...
	::Sleep(static_cast<DWORD>(time.asMilliseconds()));

	// Reset the timer resolution back to the system default
	timeEndPeriod(tc.wPeriodMin);
}

}