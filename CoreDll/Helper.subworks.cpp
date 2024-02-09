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

namespace ohms {

bool Helper::subwork_challenge() {
	msgPush(HelperReturnMessage::Log_Challenge_Start);
	const bool forNew = task_ChaGame_ForNew; // 保存设置

	cv::Rect rect;
	cv::Point pt;

	unsigned long i = 0; // 次数

begin_point:
	try {
		++i;
		msgPush(HelperReturnMessage::Log_Challenge_BeginNum, i);

		// 查找目标。
		if (!step_waitFor(forNew ? mat_ChaGameNew : mat_ChaGameLast, rect_ChaGame, rect, seconds(15.0f)))
			step_subtaskError(
				forNew ?
				HelperReturnMessage::Log_Task_Challenge_NoNew :
				HelperReturnMessage::Log_Task_Challenge_NoLast
			);

		// 点击比赛，直到进入编队画面（找到挑战按钮）。
		msgPush(forNew ? HelperReturnMessage::Log_Challenge_EnterNew : HelperReturnMessage::Log_Challenge_EnterLast);
		if (!step_keepClickingUntil({ 900, rect.y }, mat_StartGame, rect_StartGame))
			step_subtaskError(HelperReturnMessage::Log_Task_Challenge_NoEnter);

		// 查找“挑战”按钮。
		step_waitFor(mat_StartGame, rect_StartGame, rect);
		msgPush(HelperReturnMessage::Log_Challenge_Play);
		{
			size_t tc = 0;
			while (!m_askedForStop) {
				// 点击挑战，直到进入加载画面。
				pt = { rect.x + 50, rect.y + 20 };
				if (step_keepClickingUntil(pt, mat_Loading, rect_Loading, seconds(1.5f), seconds(0.3f), 20.0f))
					break;
				if (step_waitFor(mat_LowFP, rect_LowFP, rect, seconds(0.2f)))
					step_subtaskError(HelperReturnMessage::Log_Task_Challenge_LowFP);
				if (++tc > 10)
					step_subtaskError(HelperReturnMessage::Log_Task_Challenge_NoStart);
			}
		}

		// 等待结束。
		msgPush(HelperReturnMessage::Log_Challenge_WaitForEnd);
		if (!step_waitFor(mat_Result, rect_Result, rect, seconds(5 * 60.0f), 25.0f))
			step_subtaskError(HelperReturnMessage::Log_Task_Challenge_TimeOut);

		// 点击，直到进入加载画面。
		msgPush(HelperReturnMessage::Log_Challenge_End);
		pt = { rect.x + 100, rect.y };
		if (!step_keepClickingUntil(pt, mat_Loading, rect_Loading, seconds(60.0f), seconds(0.1f), 20.0f))
			step_subtaskError(HelperReturnMessage::Log_Task_Challenge_NoEnd);

		// 等待到挑战赛标签页出现。
		msgPush(HelperReturnMessage::Log_Challenge_Quiting);
		if (!step_waitFor(mat_ChaTabBar, rect_ChaTabBar, rect, seconds(60.0f)))
			step_subtaskError(HelperReturnMessage::Log_Task_Challenge_NoOver);
		msgPush(HelperReturnMessage::Log_Challenge_Over);

		goto begin_point;
	}
	catch (int err) {
		if (err == 0) { // 返回false表示主动停止
			msgPush(HelperReturnMessage::Log_Task_Stop);
			return false;
		}
		else { // 不是0就是真错误
			msgPush(HelperReturnMessage::Log_Task_Exception);
		}
	}
	catch (...) {
		msgPush(HelperReturnMessage::Log_Task_Exception);
	}
	msgPush(HelperReturnMessage::Log_Challenge_Exit);
	return true;
}

}
