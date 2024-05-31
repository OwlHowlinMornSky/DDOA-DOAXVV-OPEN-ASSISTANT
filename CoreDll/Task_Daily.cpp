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
#include "Task_Navigate.h"

namespace ohms {

Task_Daily::Task_Daily() :
	r_handler(nullptr),
	r_helper(nullptr) {}

Task_Daily::~Task_Daily() {}

bool Task_Daily::Run(Helper& h) {
	r_handler = WndHandler::Instance(); // 获取handler实例
	r_helper = &h; // 保存Helper实例

	m_set = Settings::Daily::DEFAULT;

	try {
		h.GuiLogF(ReturnMsgEnum::TaskDailyBegin);

		switch (r_handler->SetForGame()) {
		case WndHandler::SetReturnValue::WndNotFound:
			//CoreLog() << "Task.Challenge: Game Window Not Found." << std::endl;
			h.TaskError(ReturnMsgEnum::TaskErrNoWnd);
			break;
		case WndHandler::SetReturnValue::CaptureFailed:
			//CoreLog() << "Task.Challenge: Game Window Cannot Capture." << std::endl;
			h.TaskError(ReturnMsgEnum::TaskErrNoCap);
			break;
		}

		if (m_set.DoCheck)
			DoCheck();

		if (m_set.DoShot)
			DoShot();

		h.GuiLogF(ReturnMsgEnum::TaskDailyComplete);
	}
	catch (int e) {
		if (e != 0)
			h.GuiLogF(ReturnMsgEnum::TaskDailyFailed);
	}
	catch (...) {
		h.GuiLogF(ReturnMsgEnum::TaskDailyFailed);
	}

	return true;
}

void Task_Daily::DoCheck() {
	m_homeDailyBtn = r_helper->CreateTemplate("daily/checkBtn");
	m_homeDailyDot = r_helper->CreateTemplate("daily/checkDot");
	m_checkBtn = r_helper->CreateTemplate("daily/checkClk");
	m_checkBdTitle = r_helper->CreateTemplate("daily/chkBdTitle");
	m_checkOk = r_helper->CreateTemplate("daily/checkOK");

	if (IsDailCheckDone()) {
		return;
	}
	if (!OpenDailyCheckBoard()) {
		r_helper->GuiLogF_I(ReturnMsgEnum::TaskErr_Task, TaskEnum::Daily);
		return;
	}
	if (!DoDailyCheckInBoard()) {
		r_helper->GuiLogF_I(ReturnMsgEnum::TaskErr_Task, TaskEnum::Daily);
	}
	if (!CloseCheckBoard()) {
		r_helper->GuiLogF_I(ReturnMsgEnum::TaskErr_Task, TaskEnum::Daily);
	}
	return;
}

void Task_Daily::DoShot() {
	m_shotEntrance = r_helper->CreateTemplate("daily/shotEntrance");
	m_shotDot = r_helper->CreateTemplate("daily/shotDot");
	m_shotBack = r_helper->CreateTemplate("daily/shotBack");
	m_shot = r_helper->CreateTemplate("daily/shotShot");
	m_homePage = r_helper->CreateTemplate("homeSpec");

	if (IsShotDone()) {
		return;
	}
	if (!OpenShotPage()) {
		r_helper->GuiLogF_I(ReturnMsgEnum::TaskErr_Task, TaskEnum::Daily);
		return;
	}
	if (!DoShotInPage()) {
		r_helper->GuiLogF_I(ReturnMsgEnum::TaskErr_Task, TaskEnum::Daily);
	}
	if (!CloseShotPage()) {
		r_helper->GuiLogF_I(ReturnMsgEnum::TaskErr_Task, TaskEnum::Daily);
	}
	return;
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

	return !res;
}

bool Task_Daily::OpenDailyCheckBoard() {
	Task_Navigate::Instance()->NavigateTo(NavigateEnum::Home);

	if (-1 == r_handler->WaitFor(*m_homeDailyBtn)) {
		// 超时
		return false;
	}

	r_handler->KeepClickingUntil(
		m_homeDailyBtn->GetSpecialPointInResult(0),
		*m_checkBdTitle
	);
	TaskSleep(1.0_sec);

	return true;
}

bool Task_Daily::DoDailyCheckInBoard() {
	if (-1 == r_handler->WaitFor(*m_checkBtn)) {
		// 超时
		return false;
	}

	r_handler->KeepClickingUntil(
		m_checkBtn->GetSpecialPointInResult(0),
		*m_checkOk
	);
	r_handler->KeepClickingUntil(
		m_checkOk->GetSpecialPointInResult(0),
		*m_checkBdTitle
	);
	TaskSleep(1.0_sec);

	return true;
}

bool Task_Daily::CloseCheckBoard() {
	return Task_Navigate::Instance()->NavigateTo(NavigateEnum::Home);
}

bool Task_Daily::IsShotDone() {
	Task_Navigate::Instance()->NavigateTo(NavigateEnum::Home);

	if (-1 == r_handler->WaitFor(*m_shotEntrance)) {
		// 超时
		return false;
	}

	cv::Mat mat;
	r_handler->GetOneFrame(mat);
	bool res = m_shotDot->Match(mat);

	return !res;
}

bool Task_Daily::OpenShotPage() {
	Task_Navigate::Instance()->NavigateTo(NavigateEnum::Home);

	if (-1 == r_handler->WaitFor(*m_shotEntrance)) {
		// 超时
		return false;
	}

	r_handler->KeepClickingUntil(
		m_shotEntrance->GetSpecialPointInResult(0),
		*m_shot,
		20.0_sec,
		3.0_sec
	);
	TaskSleep(2.0_sec);

	return true;
}

bool Task_Daily::DoShotInPage() {
	if (-1 == r_handler->WaitFor(*m_shot)) {
		// 超时
		return false;
	}

	r_handler->ClickAt(m_shot->GetSpecialPointInResult(0));
	TaskSleep(2.0_sec);

	return true;
}

bool Task_Daily::CloseShotPage() {
	if (-1 == r_handler->WaitFor(*m_shotBack)) {
		// 超时
		return false;
	}

	r_handler->KeepClickingUntil(
		m_shotBack->GetSpecialPointInResult(0),
		*m_homePage
	);
	TaskSleep(1.0_sec);

	return true;
}

} // namespace ohms
