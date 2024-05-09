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
#pragma once

#include "API.h"
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
	friend Time operator"" _sec(long double);
	friend Time operator"" _msec(unsigned long long);
	friend Time operator"" _usec(unsigned long long);

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


Time operator"" _sec(long double x);
Time operator"" _msec(unsigned long long x);
Time operator"" _usec(unsigned long long x);

} // namespace ohms
