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

#include "Time.h"

namespace ohms {

/**
 * @brief 精确时钟。
*/
class Clock final {
public:
	Clock();

	/**
	 * @brief 获取上次restart以来经过的时间
	 * @return 经过的时间
	*/
	Time getElapsedTime() const;
	/**
	 * @brief 重新开始计时（重设开始时间）
	 * @return 经过的时间
	*/
	Time restart();

protected:
	Time m_startTime; // 开始时间
};

} // namespace ohms
