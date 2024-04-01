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

#include "Settings.h"
#include "AskedForStop.h"
#include "TaskExceptionCode.h"

namespace ohms {

bool Helper::Task_StartUp() {
	if (r_handler->SetForGame() != WndHandler::SetReturnValue::OK) {
		if (r_handler->SetForLauncher() != WndHandler::SetReturnValue::OK) {
			system("start steam://rungameid/958260");
			do {
				Sleep(1000);
			} while (r_handler->SetForLauncher() != WndHandler::SetReturnValue::OK);
		}
		// 点击开始。
		do {
			Sleep(1000);
		} while (r_handler->SetForGame() != WndHandler::SetReturnValue::OK);
	}
	return true;
}

bool Helper::Task_Challenge() {
	bool taskReturnCode = true; // 若返回false表示终止后续任务。
	try {
		PushMsg(HelperReturnMessage::LOG_Challenge_Start);
		const bool forNew = Settings::g_set.ChaGame_ForNew; // 保存设置

		switch (r_handler->SetForGame()) {
		case WndHandler::SetReturnValue::WndNotFound:
			Step_TaskError(HelperReturnMessage::STR_Task_Error_NoWnd);
			break;
		case WndHandler::SetReturnValue::CaptureFailed:
			Step_TaskError(HelperReturnMessage::STR_Task_Error_FailedCapture);
			break;
		}

		std::unique_ptr<MatchTemplate>
			temp_chaBar = CreateTemplate("default"),
			temp_lastFight = CreateTemplate("lastFight"),
			temp_newFight = CreateTemplate("newFight"),
			temp_startGame = CreateTemplate("start"),
			temp_loading = CreateTemplate("loading"),
			temp_lowFp = CreateTemplate("fp"),
			temp_gameResult = CreateTemplate("result"),
			temp_awardCha = CreateTemplate("add");

		bool forAddThisTime = false;

		cv::Point pt;

		unsigned long playCnt = 0; // 次数

	begin_point:

		++playCnt;
		if (playCnt > 1)
			PushMsg(HelperReturnMessage::CMD_EmptyLine);
		PushMsgCode(HelperReturnMessage::LOG_Challenge_BeginNum, playCnt);

		// 查找目标比赛按钮。
		if (-1 == r_handler->WaitFor(forNew ? *temp_newFight : *temp_lastFight))
			Step_TaskError(
				forNew ?
				HelperReturnMessage::STR_Task_Challenge_NoNew :
				HelperReturnMessage::STR_Task_Challenge_NoLast
			);

		// 点击比赛，直到进入编队画面（找到挑战按钮）。
		PushMsg(forAddThisTime ? HelperReturnMessage::LOG_Challenge_EnterAdd :
				(forNew ? HelperReturnMessage::LOG_Challenge_EnterNew : HelperReturnMessage::LOG_Challenge_EnterLast));
		pt = { 900, (forNew ? temp_newFight : temp_lastFight)->GetLastMatchRect().y };
		if (!Step_KeepClickingUntil(pt, *temp_startGame))
			Step_TaskError(HelperReturnMessage::STR_Task_Challenge_NoEnter);

		forAddThisTime = false;

		// 查找“挑战”按钮。
		r_handler->WaitFor(*temp_startGame);
		pt = temp_startGame->GetLastMatchRect().tl() + cv::Point2i(50, 20);
		PushMsg(HelperReturnMessage::LOG_Challenge_Play);
		for (int i = 0, n = 10; i < n; ++i) {
			r_handler->ClickAt(pt);
			switch (r_handler->WaitForMultiple({ temp_loading.get(), temp_lowFp.get() }, seconds(2.0f))) {
			default:
			case -1:
				if (i == n - 1)
					Step_TaskError(HelperReturnMessage::STR_Task_Challenge_NoStart);
				break;
			case 0:
				i = n;
				break;
			case 1:
				throw TaskExceptionCode::TaskComplete;
				break;
			}
		}

		// 等待结束。
		PushMsg(HelperReturnMessage::LOG_Challenge_WaitForEnd);
		if (-1 == r_handler->WaitFor(*temp_gameResult, seconds(5 * 60.0f)))
			Step_TaskError(HelperReturnMessage::STR_Task_Challenge_TimeOut);

		// 点击，直到进入加载画面。
		PushMsg(HelperReturnMessage::LOG_Challenge_End);
		pt = temp_gameResult->GetLastMatchRect().tl() + cv::Point2i(100, 0);
		if (!Step_KeepClickingUntil(pt, *temp_loading, seconds(60.0f), seconds(0.1f)))
			Step_TaskError(HelperReturnMessage::STR_Task_Challenge_NoEnd);

		// 等待到挑战赛标签页出现。
		PushMsg(HelperReturnMessage::LOG_Challenge_Quiting);
		if (-1 == r_handler->WaitFor(*temp_chaBar, seconds(60.0f)))
			Step_TaskError(HelperReturnMessage::STR_Task_Challenge_NoOver);
		PushMsg(HelperReturnMessage::LOG_Challenge_Over);

		// 检查是否有奖励挑战赛。
		if (Settings::g_set.ChaGame_CheckAddition) {
			if (0 == r_handler->WaitFor(*temp_awardCha, seconds(2.0f))) {
				PushMsg(HelperReturnMessage::LOG_Challenge_FindAdd);
				if (Settings::g_set.ChaGame_EnterAddition) { // 进入奖励挑战赛。
					if (forNew) {
						pt = temp_awardCha->GetLastMatchRect().tl() + cv::Point2i(30, 50);
						if (Step_KeepClickingUntil(pt, *temp_newFight, seconds(10.0f), seconds(2.0f))) {
							PushMsg(HelperReturnMessage::LOG_Challenge_OpenedAdd);
							forAddThisTime = true;
						}
						else {
							Step_TaskError(HelperReturnMessage::STR_Task_Challenge_OpenAddFailed);
						}
						//Step_Click(pt);
					}
					else {
						Step_TaskError(HelperReturnMessage::STR_Task_Challenge_AddNotSup);
					}
				}
				else { // 回到“推荐”栏。
					if (0 == r_handler->WaitFor(*temp_chaBar, seconds(5.0f))) {
						pt = temp_chaBar->GetLastMatchRect().tl() + cv::Point2i(40, 12);
						if (Step_KeepClickingUntilNo(pt, *temp_awardCha, seconds(10.0f), seconds(0.5f))) {
							PushMsg(HelperReturnMessage::LOG_Challenge_IgnoredAdd);
						}
						else {
							Step_TaskError(HelperReturnMessage::STR_Task_Challenge_IgnoreAddFailed);
						}
						//Step_Click(pt);
					}
				}
			}
			else {
				PushMsg(HelperReturnMessage::LOG_Challenge_NotFindAdd);
			}
		}

		goto begin_point;
	}
	catch (int err) {
		switch (err) {
		case TaskExceptionCode::UserStop:
			PushMsg(HelperReturnMessage::LOG_TaskStop);
			taskReturnCode = false;
			break;
		case TaskExceptionCode::TaskComplete:
			PushMsg(HelperReturnMessage::LOG_TaskComplete);
			break;
		case TaskExceptionCode::KnownErrorButNotCritical:
			break;
		case TaskExceptionCode::KnownErrorCritical:
			taskReturnCode = false;
			break;
		default:
			PushMsg(HelperReturnMessage::LOG_TaskError_Exception);
			taskReturnCode = false;
		}
	}
	catch (...) {
		MessageBoxA(0, "!!!", "???", 0);
		PushMsg(HelperReturnMessage::LOG_TaskError_Exception);
		taskReturnCode = false;
	}
	PushMsg(HelperReturnMessage::LOG_Challenge_Exit);
	return taskReturnCode;
}

}
