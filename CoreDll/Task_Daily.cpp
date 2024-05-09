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
#include "Task_Daily.h"

#include "Clock.h"
#include "AskedForStop.h"
#include "Sleep.h"
#include "Task_Navigate.h"

namespace ohms {

Task_Daily::Task_Daily() :
	r_handler(nullptr),
	r_helper(nullptr) {}

Task_Daily::~Task_Daily() {}

bool Task_Daily::Run(Helper& h) {
	r_handler = WndHandler::Instance(); // 获取handler实例
	r_helper = &h; // 保存Helper实例

	m_homeDailyBtn = h.CreateTemplate("daily/checkBtn");
	m_homeDailyDot = h.CreateTemplate("daily/checkDot");
	m_checkBtn = h.CreateTemplate("daily/checkClk");

	if (IsDailCheckDone()) {

		return true;
	}
	if (!OpenDailyCheckBoard()) {

		return true;
	}
	if (!DoDailyCheckInBoard()) {

	}
	if (!CloseCheckBoard()) {

	}
	return true;
}

bool Task_Daily::IsDailCheckDone() {
	Task_Navigate::Instance()->NavigateTo(NavigateEnum::Home);

	if (-1 == r_handler->WaitFor(*m_homeDailyBtn)) {
		// 超时
		return false;
	}

	cv::Mat mat;
	r_handler->GetOneFrame(mat);
	bool res = m_homeDailyDot->Match(mat);

	return res;
}

bool Task_Daily::OpenDailyCheckBoard() {
	Task_Navigate::Instance()->NavigateTo(NavigateEnum::Home);

	if (-1 == r_handler->WaitFor(*m_homeDailyBtn)) {
		// 超时
		return false;
	}

	cv::Point pt;
	pt = m_homeDailyBtn->GetLastMatchRect().tl();
	pt += { 26, 28 };

	r_handler->ClickAt(pt);
	sleep(5.0_sec);

	return true;
}

bool Task_Daily::DoDailyCheckInBoard() {
	if (-1 == r_handler->WaitFor(*m_checkBtn)) {
		// 超时
		return false;
	}

	cv::Point pt;
	pt = m_checkBtn->GetLastMatchRect().tl();
	pt += { 22, 7 };

	r_handler->ClickAt(pt);
	sleep(5.0_sec);

	return true;
}

bool Task_Daily::CloseCheckBoard() {
	return Task_Navigate::Instance()->NavigateTo(NavigateEnum::Home);
}

} // namespace ohms
