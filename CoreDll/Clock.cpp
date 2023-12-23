/*
*    DDOA-DOAXVV-OPEN-ASSISTANT
*
*     Copyright 2023-2024  Tyler Parret True
*
*    Licensed under the Apache License, Version 2.0 (the "License");
*    you may not use this file except in compliance with the License.
*    You may obtain a copy of the License at
*
*        http://www.apache.org/licenses/LICENSE-2.0
*
*    Unless required by applicable law or agreed to in writing, software
*    distributed under the License is distributed on an "AS IS" BASIS,
*    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*    See the License for the specific language governing permissions and
*    limitations under the License.
*
* @Authors
*    Tyler Parret True <mysteryworldgod@outlook.com><https://github.com/OwlHowlinMornSky>
*/
#include "Clock.h"
#include "framework.h"

namespace {

/**
 * @brief 获取内核速度
*/
LARGE_INTEGER getFrequency() {
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);
	return frequency;
}

/**
 * @brief 获取当前时间
*/
ohms::Time getCurrentTime() {
	// Calculate inverse of frequency multiplied by 1000000 to prevent overflow in final calculation
	// Frequency is constant across the program lifetime
	static double inverse = 1000000.0 / static_cast<double>(getFrequency().QuadPart);

	LARGE_INTEGER time;

	// Get the current time
	QueryPerformanceCounter(&time);

	// Return the current time as microseconds
	return ohms::microseconds(static_cast<long long>(static_cast<double>(time.QuadPart) * inverse));
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
