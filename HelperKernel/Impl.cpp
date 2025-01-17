#include "Impl.h"

#include <Windows.h>

namespace HelperKernel {

void HelperKernel::Impl::sleep(unsigned int milliseconds) {
	// Get the supported timer resolutions on this system
	TIMECAPS tc;
	timeGetDevCaps(&tc, sizeof(TIMECAPS));

	// Set the timer resolution to the minimum for the Sleep call
	timeBeginPeriod(tc.wPeriodMin);

	// Wait...
	::Sleep(static_cast<DWORD>(milliseconds));

	// Reset the timer resolution back to the system default
	timeEndPeriod(tc.wPeriodMin);
}

}
