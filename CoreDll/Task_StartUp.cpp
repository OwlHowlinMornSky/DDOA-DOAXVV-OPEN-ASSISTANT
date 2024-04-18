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

namespace ohms {

Task_StartUp::Task_StartUp() :
	r_handler(nullptr),
	r_helper(nullptr) {}

Task_StartUp::~Task_StartUp() {}

bool Task_StartUp::Run(Helper& h) {
	r_handler = WndHandler::Instance();
	r_helper = &h;

	Clock clk;
	std::unique_ptr<MatchTemplate>
		temp_startBtn = h.CreateTemplate("StartGameBtn"),
		temp_titleBtn = h.CreateTemplate("startTitleTLbtn"),
		temp_loading = h.CreateTemplate("loading"),
		temp_homeSpec = h.CreateTemplate("homeSpec");
	cv::Point pt;

	if (!r_handler->GameWndAvailable()) {
		if (!r_handler->LaucherAvailable()) {
			system("start steam://rungameid/958260");

			clk.restart();
			while (true) {
				if (clk.getElapsedTime() > seconds(60.0f)) {
					h.GuiLogF_SI(ReturnMsgEnum::TaskErr_F_SI, ReturnMsgEnum::TaskErrCommonTLE, 1);
					return false;
				}
				if (r_handler->LaucherAvailable()) {
					break;
				}
				if (g_askedForStop) {
					return true;
				}
				Sleep(1000);
			}
		}

		r_handler->SetForLauncher();
		if (-1 == r_handler->WaitFor(*temp_startBtn, seconds(20.0f))) {
			h.GuiLogF_SI(ReturnMsgEnum::TaskErr_F_SI, ReturnMsgEnum::TaskErrCommonTLE, 2);
			return false;
		}

		pt = temp_startBtn->GetLastMatchRect().tl();
		pt += { 120, 40 };

		while (true) {
			if (!r_handler->LaucherAvailable()) {
				break;
			}
			r_handler->ClickAt(pt);// 点击开始。
			if (g_askedForStop) {
				return true;
			}
			Sleep(500);
		}
		r_handler->Reset();

		while (true) {
			if (clk.getElapsedTime() > seconds(60.0f)) {
				h.GuiLogF_SI(ReturnMsgEnum::TaskErr_F_SI, ReturnMsgEnum::TaskErrCommonTLE, 3);
				return false;
			}
			if (r_handler->GameWndAvailable()) {
				break;
			}
			if (g_askedForStop) {
				return true;
			}
			Sleep(1000);
		}
	}

	r_handler->SetForGame();
	if (-1 == r_handler->WaitFor(*temp_titleBtn, seconds(60.0f))) {
		h.GuiLogF_SI(ReturnMsgEnum::TaskErr_F_SI, ReturnMsgEnum::TaskErrCommonTLE, 4);
		return false;
	}

	pt = { 920, 40 };
	if (!r_handler->KeepClickingUntil(pt, *temp_loading, seconds(30.0f), seconds(0.3f))) {
		h.GuiLogF_SI(ReturnMsgEnum::TaskErr_F_SI, ReturnMsgEnum::TaskErrCommonTLE, 5);
		return false;
	}

	return true;
}

}
