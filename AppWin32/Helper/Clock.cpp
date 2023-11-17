#include "Clock.h"
#include "../Window/framework.h"

namespace {

LARGE_INTEGER getFrequency() {
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);
	return frequency;
}

ohms::Time getCurrentTime() {
	// Calculate inverse of frequency multiplied by 1000000 to prevent overflow in final calculation
	// Frequency is constant across the program lifetime
	static double inverse = 1000000.0 / static_cast<double>(getFrequency().QuadPart);

	LARGE_INTEGER time;

	// Get the current time
	QueryPerformanceCounter(&time);

	// Return the current time as microseconds
	return ohms::microseconds(static_cast<int64_t>(static_cast<double>(time.QuadPart) * inverse));
}

} // namespace

namespace ohms {

Clock::Clock() :
	m_startTime(::getCurrentTime()) {}

Time Clock::getElapsedTime() const {
	return ::getCurrentTime() - m_startTime;
}

Time Clock::restart() {
	Time now = ::getCurrentTime();
	Time elapsed = now - m_startTime;
	m_startTime = now;
	return elapsed;
}

} // namespace ohms
