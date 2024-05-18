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
#include "Task_Challenge.h"
#include "CoreLog.h"
#include "TaskExceptionCode.h"
#include "Task_Navigate.h"

namespace ohms {

Task_Challenge::Task_Challenge() :
	r_helper(nullptr),
	r_handler(nullptr),
	m_set(Settings::Challenge::DEFAULT) {}

Task_Challenge::~Task_Challenge() {}

bool Task_Challenge::Run(Helper& h) {
	r_handler = WndHandler::Instance();
	r_helper = &h;

	bool taskReturnCode = true; // 若返回false表示终止后续任务。
	try {
		CoreLog() << "Task.Challenge: Start." << std::endl;
		h.GuiLogF(ReturnMsgEnum::ChaStart);

		const bool forNew = m_set.PlayNewMatchOrPrevious; // 保存设置

		switch (r_handler->SetForGame()) {
		case WndHandler::SetReturnValue::WndNotFound:
			CoreLog() << "Task.Challenge: Game Window Not Found." << std::endl;
			h.TaskError(ReturnMsgEnum::TaskErrNoWnd);
			break;
		case WndHandler::SetReturnValue::CaptureFailed:
			CoreLog() << "Task.Challenge: Game Window Cannot Capture." << std::endl;
			h.TaskError(ReturnMsgEnum::TaskErrNoCap);
			break;
		}
		CoreLog() << "Task.Challenge: Window Handler Setted." << std::endl;

		CoreLog() << "Task.Challenge: Begin Load Templates." << std::endl;
		std::unique_ptr<MatchTemplate>
			temp_chaBar = h.CreateTemplate("default"),
			temp_lastFight = h.CreateTemplate("lastFight"),
			temp_newFight = h.CreateTemplate("newFight"),
			temp_startGame = h.CreateTemplate("start"),
			temp_loading = h.CreateTemplate("loading"),
			temp_lowFp = h.CreateTemplate("fp"),
			temp_gameResult = h.CreateTemplate("result"),
			temp_awardCha = h.CreateTemplate("add");
		m_camFp = h.CreateTemplate("UseFp");
		m_camFpNo = h.CreateTemplate("cha/shotFpNo");
		m_camFpComf[0] = h.CreateTemplate("UseFpComf0");
		m_camFpComf[1] = h.CreateTemplate("UseFpComf1");
		CoreLog() << "Task.Challenge: Finish Load Templates." << std::endl;

		cv::Point pt;
		unsigned long playCnt = 0; // 次数
		bool forAddThisTime = false; // 是否已经进入奖励挑战赛
		unsigned long playAwardCnt = 0; // 奖励挑战赛次数

		//Task_Navigate::Instance()->ShakeCursor();

		while (true) {
			CoreLog() << "Task.Challenge: Loop Begin." << std::endl;
			// 检查导航位置
			switch (Task_Navigate::Instance()->TryToDeterminePage()) {
			case NavigateEnum::Challenge:
				CoreLog() << "Task.Challenge: Navigate Detected: Challenge." << std::endl;
				TaskSleep(2.0_sec);
				if (-1 == r_handler->WaitFor(*temp_chaBar)) {
					CoreLog() << "Task.Challenge: Navigate Failed: No ChaBar." << std::endl;
					throw TaskExceptionCode::KnownErrorButNotCritical; // 不影响后续任务的错误。
				}
				r_handler->ClickAt(temp_chaBar->GetSpecialPointInResult(0));
				TaskSleep(500_msec);
				break;
			case NavigateEnum::MatchConfirm:
				CoreLog() << "Task.Challenge: Navigate Detected: Match Confirm." << std::endl;
				goto MatchComfirm;
				break;
			case NavigateEnum::MatchResult:
				CoreLog() << "Task.Challenge: Navigate Detected: Match Result." << std::endl;
				goto MatchEnd;
				break;
			default:
				CoreLog() << "Task.Challenge: Navigate Detected: Others." << std::endl;
				if (!Task_Navigate::Instance()->NavigateTo(NavigateEnum::Challenge)) {
					CoreLog() << "Task.Challenge: Navigate Failed." << std::endl;
					throw TaskExceptionCode::KnownErrorButNotCritical; // 不影响后续任务的错误。
				}
				TaskSleep(2.0_sec);
				if (-1 == r_handler->WaitFor(*temp_chaBar)) {
					CoreLog() << "Task.Challenge: Navigate Failed: No ChaBar." << std::endl;
					throw TaskExceptionCode::KnownErrorButNotCritical; // 不影响后续任务的错误。
				}
				r_handler->ClickAt(temp_chaBar->GetSpecialPointInResult(0));
				TaskSleep(500_msec);
				break;
			}
			CoreLog() << "Task.Challenge: Navigate Over." << std::endl;

			CoreLog() << "Task.Challenge: Search for Target Match Enter Button." << std::endl;
			// 查找目标比赛按钮。
			if (-1 == r_handler->WaitFor(forNew ? *temp_newFight : *temp_lastFight))
				h.TaskError(
					forNew ?
					ReturnMsgEnum::TaskErrChaNoNew :
					ReturnMsgEnum::TaskErrChaNoPri
				);

			// 点击比赛，直到进入编队画面（找到挑战按钮）。
			CoreLog() << "Task.Challenge: Enter Game <" << (forAddThisTime ? "Award" : (forNew ? "New" : "Last")) << ">." << std::endl;
			pt = { 900, (forNew ? temp_newFight : temp_lastFight)->GetLastMatchRect().y };
			if (!r_handler->KeepClickingUntil(pt, *temp_startGame))
				h.TaskError(ReturnMsgEnum::TaskErrChaNoEnter);

			forAddThisTime = false;

		MatchComfirm:
			CoreLog() << "Task.Challenge: Search for Match Start Button." << std::endl;
			// 查找“挑战”按钮。
			r_handler->WaitFor(*temp_startGame);
			CoreLog() << "Task.Challenge: Play Game." << std::endl;
			for (int i = 0, n = 10; i < n; ++i) {
				CoreLog() << "Task.Challenge: Start Match Loop: " << i << "." << std::endl;
				pt = temp_startGame->GetSpecialPointInResult(0);
				r_handler->ClickAt(pt);
				switch (r_handler->WaitForMultiple({ temp_loading.get(), temp_lowFp.get() }, 2.0_sec)) {
				default:
				case -1:
					CoreLog() << "Task.Challenge: Start Match Loop: Not Found." << std::endl;
					if (i == n - 1) {
						CoreLog() << "Task.Challenge: Failed to Start Match." << std::endl;
						h.TaskError(ReturnMsgEnum::TaskErrChaNoStart);
					}
					break;
				case 0:
					i = n;
					CoreLog() << "Task.Challenge: Start Match Loop: OK." << std::endl;
					break;
				case 1:
					CoreLog() << "Task.Challenge: Start Match Loop: Low FP." << std::endl;
					if (!m_set.AutoUseCamFP) { // 使用cam补充fp
						CoreLog() << "Task.Challenge: Task Over: Setted No Use FP." << std::endl;
						throw TaskExceptionCode::TaskComplete;
					}
					switch (r_handler->WaitForMultiple({ m_camFp.get(), m_camFpNo.get() }, 2.0_sec)) {
					case 0:
					{
						CoreLog() << "Task.Challenge: Try to Use FP: Available." << std::endl;
						pt = m_camFp->GetSpecialPointInResult(0);

						r_handler->ClickAt(pt);
						TaskSleep(1.0_sec);

						if (-1 == r_handler->WaitFor(*(m_camFpComf[0]))) {
							CoreLog() << "Task.Challenge: Task Over: Try to Use FP: No 1st." << std::endl;
							throw TaskExceptionCode::TaskComplete;
						}
						pt = m_camFpComf[0]->GetSpecialPointInResult(0);
						if (!r_handler->KeepClickingUntil(pt, *(m_camFpComf[1]), 10.0_sec, 2.0_sec)) {
							CoreLog() << "Task.Challenge: Task Over: Try to Use FP: No 2st." << std::endl;
							throw TaskExceptionCode::TaskComplete;
						}
						pt = m_camFpComf[1]->GetSpecialPointInResult(0);

						r_handler->ClickAt(pt);
						TaskSleep(1.0_sec);
						if (-1 == r_handler->WaitFor(*temp_startGame)) {
							CoreLog() << "Task.Challenge: Task Over: Try to Use FP: No Close." << std::endl;
							throw TaskExceptionCode::TaskComplete;
						}
						CoreLog() << "Task.Challenge: Try to Use FP: OK." << std::endl;
						break;
					}
					default:
						CoreLog() << "Task.Challenge: Task Over: No FP." << std::endl;
						throw TaskExceptionCode::TaskComplete;
					}
					break;
				}
			}
			CoreLog() << "Task.Challenge: Match Started." << std::endl;

			if (forAddThisTime) {
				++playAwardCnt;
				h.GuiLogF_I(ReturnMsgEnum::ChaBeginAdd_I, playAwardCnt);
				CoreLog() << "Task.Challenge: Match Award " << playAwardCnt << "." << std::endl;
			}
			else {
				++playCnt;
				h.GuiLogF_I(ReturnMsgEnum::ChaBegin_I, playCnt);
				CoreLog() << "Task.Challenge: Match " << playCnt << "." << std::endl;
			}

		MatchEnd:

			// 等待结束。
			CoreLog() << "Task.Challenge: In Game, Waitting for End." << std::endl;
			if (-1 == r_handler->WaitFor(*temp_gameResult, 300.0_sec))
				h.TaskError(ReturnMsgEnum::TaskErrChaTimeOut);

			// 点击，直到进入加载画面。
			CoreLog() << "Task.Challenge: Game End, Trying to Exit." << std::endl;
			pt = temp_gameResult->GetSpecialPointInResult(0);
			if (!r_handler->KeepClickingUntil(pt, *temp_loading, 60.0_sec, 0.1_sec))
				h.TaskError(ReturnMsgEnum::TaskErrChaNoEnd);

			// 等待到挑战赛标签页出现。
			CoreLog() << "Task.Challenge: Game Exit, Waitting for Challenge Page." << std::endl;
			if (-1 == r_handler->WaitFor(*temp_chaBar, 60.0_sec))
				h.TaskError(ReturnMsgEnum::TaskErrChaNoOver);
			h.GuiLogF(ReturnMsgEnum::ChaOver);

			// 检查是否有奖励挑战赛。
			if (m_set.CheckAddition) {
				if (0 == r_handler->WaitFor(*temp_awardCha, 2.0_sec)) {
					CoreLog() << "Task.Challenge: Find Award." << std::endl;
					h.GuiLogF(ReturnMsgEnum::ChaFindAdd);
					if (m_set.EnterAddition) { // 进入奖励挑战赛。
						if (forNew) {
							pt = temp_awardCha->GetSpecialPointInResult(0);
							if (r_handler->KeepClickingUntil(pt, *temp_newFight, 10.0_sec, 2.0_sec)) {
								h.GuiLogF(ReturnMsgEnum::ChaOpenedAdd);
								forAddThisTime = true;
								playAwardCnt = 0;
							}
							else {
								h.TaskError(ReturnMsgEnum::TaskErrChaOpenAddFailed);
							}
						}
						else {
							h.TaskError(ReturnMsgEnum::TaskErrChaAddNotSup);
						}
					}
					else { // 回到“推荐”栏。
						if (0 == r_handler->WaitFor(*temp_chaBar, 5.0_sec)) {
							pt = temp_chaBar->GetSpecialPointInResult(0);
							if (r_handler->KeepClickingUntilNo(pt, *temp_awardCha, 10.0_sec, 0.5_sec)) {
								h.GuiLogF(ReturnMsgEnum::ChaIgnoredAdd);
							}
							else {
								h.TaskError(ReturnMsgEnum::TaskErrChaIgnoreAddFailed);
							}
						}
					}
				}
				else {
					CoreLog() << "Task.Challenge: Not Find Award." << std::endl;
					h.GuiLogF(ReturnMsgEnum::ChaNotFindAdd);
				}
			}

			CoreLog() << "Task.Challenge: Loop End." << std::endl;

			TaskSleep(1.0_sec);
		}
	}
	catch (int err) {
		switch (err) {
		case TaskExceptionCode::UserStop:
			h.GuiLogF(ReturnMsgEnum::TaskStop);
			taskReturnCode = false;
			break;
		case TaskExceptionCode::TaskComplete:
			h.GuiLogF(ReturnMsgEnum::TaskComplete);
			break;
		case TaskExceptionCode::KnownErrorButNotCritical:
			break;
		case TaskExceptionCode::KnownErrorCritical:
			taskReturnCode = false;
			break;
		default:
			h.GuiLogF(ReturnMsgEnum::TaskException);
			taskReturnCode = false;
		}
	}
	catch (...) {
		h.GuiLogF(ReturnMsgEnum::TaskException);
		taskReturnCode = false;
	}
	CoreLog() << "Task.Challenge: Exit." << std::endl;
	h.GuiLogF(ReturnMsgEnum::ChaExit);
	return taskReturnCode;
}

}
