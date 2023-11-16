#include "Time.h"

namespace ohms {

const Time Time::Zero{};

Time::Time() :
	m_microseconds(0) {}

float Time::asSeconds() const {
	return static_cast<float>(static_cast<double>(m_microseconds) / 1000000.0);
}

int32_t Time::asMilliseconds() const {
	return static_cast<int32_t>(m_microseconds / 1000);
}

int64_t Time::asMicroseconds() const {
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

Time::Time(int64_t microseconds) :
	m_microseconds(microseconds) {}

Time seconds(float amount) {
	return Time(static_cast<int64_t>(amount * 1000000));
}

Time milliseconds(int32_t amount) {
	return Time(static_cast<int64_t>(amount) * 1000);
}

Time microseconds(int64_t amount) {
	return Time(amount);
}

}
