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
#include "Time.h"

namespace ohms {

const Time Time::Zero{};

Time::Time() :
	m_microseconds(0) {}

float Time::asSeconds() const {
	return static_cast<float>(static_cast<double>(m_microseconds) / 1000000.0);
}

long Time::asMilliseconds() const {
	return static_cast<long>(m_microseconds / 1000);
}

long long Time::asMicroseconds() const {
	return m_microseconds;
}

std::strong_ordering Time::operator<=>(const Time& right) const {
	return (m_microseconds <=> right.m_microseconds);
}

Time Time::operator-(const Time& right) const {
	return Time(m_microseconds - right.m_microseconds);
}

Time Time::operator+(const Time& right) const {
	return Time(m_microseconds + right.m_microseconds);
}

Time::Time(long long microseconds) :
	m_microseconds(microseconds) {}

Time seconds(float amount) {
	return Time(static_cast<long long>(amount * 1000000));
}

Time milliseconds(long amount) {
	return Time(static_cast<long long>(amount) * 1000);
}

Time microseconds(long long amount) {
	return Time(amount);
}

Time operator"" _sec(long double x) {
	return Time(static_cast<long long>(x * 1000000));
}

Time operator""_msec(unsigned long long x) {
    return Time(static_cast<long long>(x) * 1000);
}

Time operator""_usec(unsigned long long x) {
	return Time(x);
}

} // namespace ohms
