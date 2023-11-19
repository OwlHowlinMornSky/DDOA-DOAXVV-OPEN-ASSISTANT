#pragma once

#include <compare>

namespace ohms {

/**
 * @brief 时间。
*/
class Time final {
public:
	Time();

	/**
	 * @brief 转换为秒数
	 * @return 秒数
	*/
	float asSeconds() const;
	/**
	 * @brief 转换为毫秒数
	 * @return 毫秒数
	*/
	long asMilliseconds() const;
	/**
	 * @brief 转换为微秒数
	 * @return 微秒数
	*/
	long long asMicroseconds() const;

	/**
	 * @brief 零时间
	*/
	static const Time Zero;

	/**
	 * @brief 重载比较
	*/
	std::strong_ordering operator<=>(const Time& right) const;
	/**
	 * @brief 重载减法
	*/
	Time operator-(const Time& right) const;
	/**
	 * @brief 重载加法 
	*/
	Time operator+(const Time& right) const;

protected:
	friend Time seconds(float);
	friend Time milliseconds(long);
	friend Time microseconds(long long);

	explicit Time(long long microseconds);

protected:
	long long m_microseconds; // 微秒数
};

/**
 * @brief 秒数转换为Time
 * @param amount 秒数
 * @return Time
*/
Time seconds(float amount);
/**
 * @brief 毫秒数转换为Time
 * @param amount 毫秒数
 * @return Time
*/
Time milliseconds(long amount);
/**
 * @brief 微秒数转换为Time
 * @param amount 微秒数
 * @return Time
*/
Time microseconds(long long amount);

} // namespace ohms
