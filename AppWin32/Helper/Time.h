#pragma once

#include <stdint.h>
#include <compare>

namespace ohms {

/**
 * @brief 时间。
*/
class Time final {
public:
	Time();

	float asSeconds() const;
	int32_t asMilliseconds() const;
	int64_t asMicroseconds() const;

	static const Time Zero;

	std::strong_ordering operator<=>(const Time& right) const;
	Time operator-(const Time& right) const;
	Time operator+(const Time& right) const;

protected:
	friend Time seconds(float);
	friend Time milliseconds(int32_t);
	friend Time microseconds(int64_t);

	explicit Time(int64_t microseconds);

protected:
	int64_t m_microseconds;
};

Time seconds(float amount);
Time milliseconds(int32_t amount);
Time microseconds(int64_t amount);

} // namespace ohms
