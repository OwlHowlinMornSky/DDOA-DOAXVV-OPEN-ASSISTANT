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
#include "Task_StartUp.h"

#include "Clock.h"
#include "AskedForStop.h"

#include "NavigateEnum.h"

namespace ohms {

Task_StartUp::Task_StartUp() :
	r_handler(nullptr),
	r_helper(nullptr) {}

Task_StartUp::~Task_StartUp() {}

bool Task_StartUp::Run(Helper& h) {
	r_handler = WndHandler::Instance();
	r_helper = &h;

	Clock clk;
	cv::Point pt;

	h.GuiLogF(ReturnMsgEnum::TaskStartUpBegin);

	if (!r_handler->GameWndAvailable()) {
		if (!r_handler->LaucherAvailable()) {
			system("start steam://rungameid/958260");

			clk.restart();
			while (true) {
				if (clk.getElapsedTime() > seconds(60.0f)) {
					h.GuiLogF_SI(ReturnMsgEnum::TaskErr_F_SI, ReturnMsgEnum::TaskErrCommonTLE, 1);
					goto FINALLY_FAILED;
				}
				if (r_handler->LaucherAvailable()) {
					break;
				}
				if (g_askedForStop) {
					goto FINALLY_FAILED;
				}
				Sleep(1000);
			}
		}

		std::unique_ptr<MatchTemplate>
			temp_startBtn = h.CreateTemplate("StartGameBtn"),
			temp_titleBtn = h.CreateTemplate("startTitleTLbtn"),
			temp_loading = h.CreateTemplate("loading"),
			temp_homeSpec = h.CreateTemplate("homeSpec");

		r_handler->SetForLauncher();
		if (-1 == r_handler->WaitFor(*temp_startBtn, seconds(30.0f))) {
			h.GuiLogF_SI(ReturnMsgEnum::TaskErr_F_SI, ReturnMsgEnum::TaskErrCommonTLE, 2);
			goto FINALLY_FAILED;
		}

		pt = temp_startBtn->GetLastMatchRect().tl();
		pt += { 120, 40 };

		clk.restart();
		while (true) {
			if (clk.getElapsedTime() > seconds(60.0f)) {
				h.GuiLogF_SI(ReturnMsgEnum::TaskErr_F_SI, ReturnMsgEnum::TaskErrCommonTLE, 3);
				goto FINALLY_FAILED;
			}
			if (!r_handler->LaucherAvailable()) {
				break;
			}
			r_handler->ClickAt(pt);// 点击开始。
			if (g_askedForStop) {
				goto FINALLY_FAILED;
			}
			Sleep(500);
		}
		r_handler->Reset();

		clk.restart();
		while (true) {
			if (clk.getElapsedTime() > seconds(60.0f)) {
				h.GuiLogF_SI(ReturnMsgEnum::TaskErr_F_SI, ReturnMsgEnum::TaskErrCommonTLE, 4);
				goto FINALLY_FAILED;
			}
			if (r_handler->GameWndAvailable()) {
				break;
			}
			if (g_askedForStop) {
				goto FINALLY_FAILED;
			}
			Sleep(1000);
		}

		r_handler->SetForGame();
		if (-1 == r_handler->WaitFor(*temp_titleBtn, seconds(60.0f))) {
			h.GuiLogF_SI(ReturnMsgEnum::TaskErr_F_SI, ReturnMsgEnum::TaskErrCommonTLE, 5);
			goto FINALLY_FAILED;
		}

		pt = { 920, 40 };
		if (!r_handler->KeepClickingUntil(pt, *temp_homeSpec, seconds(90.0f), seconds(1.0f))) {
			h.GuiLogF_SI(ReturnMsgEnum::TaskErr_F_SI, ReturnMsgEnum::TaskErrCommonTLE, 6);
			goto FINALLY_FAILED;
		}
	}
	else { // 开始时就存在游戏窗口
		r_handler->SetForGame();

		int page = h.TryToDeterminePage();

		if (!(page > 0 && page < NavigateEnum::COUNT)) { // 不确定在哪个页面

			std::unique_ptr<MatchTemplate>
				temp_titlePage = h.CreateTemplate("startTitleTLbtn"),
				temp_homeSpec = h.CreateTemplate("homeSpec");

			cv::Mat mat;

			if (!r_handler->GetOneFrame(mat)) {
				goto FINALLY_FAILED;
			}

			if (temp_titlePage->Match(mat)) {
				pt = { 920, 40 };
				if (!r_handler->KeepClickingUntil(pt, *temp_homeSpec, seconds(90.0f), seconds(1.0f))) {
					h.GuiLogF_SI(ReturnMsgEnum::TaskErr_F_SI, ReturnMsgEnum::TaskErrCommonTLE, 7);
					goto FINALLY_FAILED;
				}
			}
			else {
				h.GuiLogF_SI(ReturnMsgEnum::TaskErr_F_SI, ReturnMsgEnum::TaskErrCommonTLE, 8);
				goto FINALLY_FAILED;
			}
		}
	}

FINALLY_SUCCESS:
	h.GuiLogF(ReturnMsgEnum::TaskStartUpComplete);
	return true;

FINALLY_FAILED:
	h.GuiLogF(ReturnMsgEnum::TaskStartUpFailed);
	return false;
}

}
