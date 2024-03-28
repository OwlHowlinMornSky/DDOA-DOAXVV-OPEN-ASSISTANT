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
#include "Helper.h"

#include "Clock.h"
#include "AskedForStop.h"

namespace ohms {

bool Helper::Step_KeepClickingUntil(const cv::Point clkPt, const MatchTemplate& _temp, Time maxTime, Time clkTime) {
	if (clkTime < milliseconds(10)) // 点击时间不能小于10毫秒（规定的）
		clkTime = milliseconds(10);
	cv::Rect rect;
	Clock clock;
	do {
		if (maxTime > Time::Zero && clock.getElapsedTime() >= maxTime) // 应用超时
			return false;
		//Step_Click(clkPt); // 点击
		m_handler->ClickAt(clkPt);
	} while (!g_askedForStop && (-1 == m_handler->WaitFor(_temp, clkTime)));
	if (g_askedForStop)
		throw 0;
	return true;
}

bool Helper::Step_KeepClickingUntilNo(const cv::Point clkPt, const MatchTemplate& _temp, Time maxTime, Time clkTime) {
	if (clkTime < milliseconds(10)) // 点击时间不能小于10毫秒（规定的）
		clkTime = milliseconds(10);
	cv::Rect rect;
	Clock clock;
	do {
		if (maxTime > Time::Zero && clock.getElapsedTime() >= maxTime) // 应用超时
			return false;
		//Step_Click(clkPt); // 点击
		m_handler->ClickAt(clkPt);
	} while (!g_askedForStop && (0 == m_handler->WaitFor(_temp, clkTime)));
	if (g_askedForStop)
		throw 0;
	return true;
}

void Helper::Step_TaskError(unsigned long type) {
	PushMsgCode(HelperReturnMessage::LOG_TaskError, type);
	throw 0; // 要求停止
}

} // namespace ohms
