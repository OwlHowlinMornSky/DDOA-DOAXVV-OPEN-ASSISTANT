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
#include "Task_Navigate.h"

namespace ohms {

Task_StartUp::Task_StartUp() :
	r_handler(nullptr),
	r_helper(nullptr) {}

Task_StartUp::~Task_StartUp() {}

bool Task_StartUp::Run(Helper& h) {
	r_handler = WndHandler::Instance(); // 获取handler实例
	r_helper = &h; // 保存Helper实例

	Clock clk;
	cv::Point pt;

	// LOG：任务开始【启动游戏】
	h.GuiLogF(ReturnMsgEnum::TaskStartUpBegin); 

	// 检查游戏窗口是否已存在
	if (!r_handler->GameWndAvailable()) {
		// 检查启动器窗口是否已存在
		if (!r_handler->LaucherAvailable()) {
			// 游戏未运行（游戏窗口和启动器窗口都不存在）

			// 令steam打开doaxvv
			system("start steam://rungameid/958260");

			// 等待启动器打开
			clk.restart();
			while (true) {
				//if (clk.getElapsedTime() > seconds(60.0f)) {
				//	h.GuiLogF_SI(ReturnMsgEnum::TaskErr_F_SI, ReturnMsgEnum::TaskErrCommonTLE, 1);
				//	goto FINALLY_FAILED;
				//}
				if (r_handler->LaucherAvailable()) {
					break;
				}
				if (g_askedForStop) {
					goto USER_STOP;
				}
				TaskSleep(1000_msec);
			}
		}
		// 启动器已打开，但游戏还未打开

		std::unique_ptr<MatchTemplate>
			temp_startBtn = h.CreateTemplate("StartGameBtn"),
			temp_titleBtn = h.CreateTemplate("startTitleTLbtn"),
			temp_loading = h.CreateTemplate("loading"),
			temp_homeSpec = h.CreateTemplate("homeSpec");

		r_handler->SetForLauncher();

		// 寻找启动器的启动按钮
		if (-1 == r_handler->WaitFor(*temp_startBtn, seconds(30.0f))) {
			h.GuiLogF_SI(ReturnMsgEnum::TaskErr_F_SI, ReturnMsgEnum::TaskErrCommonTLE, 2);
			goto FINALLY_FAILED;
		}

		// pt 置为 点击启动器的启动按钮位置
		pt = temp_startBtn->GetSpecialPointInResult(0);

		// 持续点击启动，直到启动器关闭
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
				goto USER_STOP;
			}
			TaskSleep(500_msec);
		}
		r_handler->Reset();

		// 等待游戏窗口出现
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
				goto USER_STOP;
			}
			TaskSleep(1000_msec);
		}

		r_handler->SetForGame();

		// 等待游戏标题画面（左上角 选项按钮）
		if (-1 == r_handler->WaitFor(*temp_titleBtn, seconds(300.0f))) {
			h.GuiLogF_SI(ReturnMsgEnum::TaskErr_F_SI, ReturnMsgEnum::TaskErrCommonTLE, 5);
			goto FINALLY_FAILED;
		}

		// 持续点击直到进入主页
		pt = { 920, 40 };
		if (!r_handler->KeepClickingUntil(pt, *temp_homeSpec, seconds(90.0f), seconds(1.0f))) {
			h.GuiLogF_SI(ReturnMsgEnum::TaskErr_F_SI, ReturnMsgEnum::TaskErrCommonTLE, 6);
			goto FINALLY_FAILED;
		}
	}
	else {
		// 开始时就存在游戏窗口
		r_handler->SetForGame();

		int page = Task_Navigate::Instance()->TryToDeterminePage();

		if (!(page > 0 && page < NavigateEnum::COUNT)) { // 不确定在哪个页面

			std::unique_ptr<MatchTemplate>
				temp_titlePage = h.CreateTemplate("startTitleTLbtn"),
				temp_homeSpec = h.CreateTemplate("homeSpec");

			cv::Mat mat;

			if (!r_handler->GetOneFrame(mat)) {
				goto FINALLY_FAILED;
			}

			if (temp_titlePage->Match(mat)) {
				// 在标题界面则尝试进入主页
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

	h.GuiLogF(ReturnMsgEnum::TaskStartUpComplete);
USER_STOP:
	return true;

FINALLY_FAILED:
	h.GuiLogF(ReturnMsgEnum::TaskStartUpFailed);
	return false;
}

}
