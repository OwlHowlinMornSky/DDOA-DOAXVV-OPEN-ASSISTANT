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

} // namespace ohms
