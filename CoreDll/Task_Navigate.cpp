﻿/*
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
#include "Task_Navigate.h"
#include "Sleep.h"
#include "CoreLog.h"

namespace {

std::unique_ptr<ohms::Task_Navigate> g_instance;

}

namespace ohms {

Task_Navigate::Task_Navigate() {
	r_handler = WndHandler::Instance();
	r_helper = (Helper*)Helper::instance();
	Helper& h = *r_helper;

	CoreLog() << "Task_Navigate: Begin Load Templates." << std::endl;

	temp_chaPage = h.CreateTemplate("default");
	temp_matchPage = h.CreateTemplate("start");
	temp_homePage = h.CreateTemplate("homeSpec");
	temp_resultPage = h.CreateTemplate("result");
	temp_anyOtherPageHaveReturn = h.CreateTemplate("back");
	temp_anyOtherPageHaveHome = h.CreateTemplate("otherHome");
	temp_anyOtherPageHaveHomeW = h.CreateTemplate("otherHomeAskew");
	temp_homeChaBtn = h.CreateTemplate("homeChaBtn");

	CoreLog() << "Task_Navigate: Finish Load Templates." << std::endl;
}

Task_Navigate* Task_Navigate::Instance() {
	if (g_instance == nullptr) {
		g_instance = std::make_unique<Task_Navigate>();
	}
	return g_instance.get();
}

void Task_Navigate::Drop() {
	g_instance.release();
	return;
}

bool Task_Navigate::Run(Helper& h) {
	return false;
}

int Task_Navigate::TryToDeterminePage() {
	if (r_handler->SetForGame() != WndHandler::SetReturnValue::OK) {
		CoreLog() << "Task_Navigate: Window Handler Set Failed." << std::endl;
		return NavigateEnum::None;
	}

	cv::Mat mat;
	if (!r_handler->GetOneFrame(mat)) {
		CoreLog() << "Task_Navigate: Window Handler GetOneFrame Failed." << std::endl;
		return NavigateEnum::None;
	}

	if (temp_homePage->Match(mat)) {
		CoreLog() << "Task_Navigate: Matched: home." << std::endl;
		return NavigateEnum::Home;
	}
	if (temp_chaPage->Match(mat)) {
		CoreLog() << "Task_Navigate: Matched: cha." << std::endl;
		return NavigateEnum::Challenge;
	}
	if (temp_matchPage->Match(mat)) {
		CoreLog() << "Task_Navigate: Matched: match comfirm." << std::endl;
		return NavigateEnum::MatchConfirm;
	}
	if (temp_resultPage->Match(mat)) {
		CoreLog() << "Task_Navigate: Matched: match result." << std::endl;
		return NavigateEnum::MatchResult;
	}
	if (temp_anyOtherPageHaveHomeW->Match(mat)) {
		CoreLog() << "Task_Navigate: Matched: AnyOtherHaveHomeBtn." << std::endl;
		return NavigateEnum::AnyOtherHaveHomeBtn;
	}
	if (temp_anyOtherPageHaveHome->Match(mat)) {
		CoreLog() << "Task_Navigate: Matched: AnyOtherHaveHomeBtn." << std::endl;
		return NavigateEnum::AnyOtherHaveHomeBtn;
	}
	if (temp_anyOtherPageHaveReturn->Match(mat)) {
		CoreLog() << "Task_Navigate: Matched: AnyOtherHaveReturnBtn." << std::endl;
		return NavigateEnum::AnyOtherHaveReturnBtn;
	}
	CoreLog() << "Task_Navigate: Matche Failed." << std::endl;

	return NavigateEnum::None;
}

bool Task_Navigate::NavigateTo(int dest) {
	return NavigateFromTo(TryToDeterminePage(), dest);
}

bool Task_Navigate::NavigateFromTo(int now, int dest) {
	CoreLog() << "Task_Navigate: From " << now << " to " << dest << "." << std::endl;
	//r_helper->GuiLogF_II(ReturnMsgEnum::Test_II, now, dest);
	if (now != dest) {
		switch (now) {
		case NavigateEnum::Home: // 主页
			break;
		case NavigateEnum::Challenge: // 挑战赛页面
		case NavigateEnum::AnyOtherHaveHomeBtn: // 任何 不确定 但 左侧有主页按钮 的页面
		{
			cv::Point pt = temp_anyOtherPageHaveHome->GetSearchRect().tl();
			pt += { 20, 20 };
			if (!r_handler->KeepClickingUntil(pt, *temp_homePage)) {
				return false;
			}
			break;
		}
		case NavigateEnum::AnyOtherHaveReturnBtn: // 任何 不确定 但 左侧有返回按钮 的页面
		{
			cv::Point pt = temp_anyOtherPageHaveReturn->GetSearchRect().tl();
			if (!r_handler->KeepClickingUntil(pt, *temp_homePage)) {
				return false;
			}
			break;
		}
		default:
			return false;
		}
		switch (dest) {
		case NavigateEnum::Challenge:
		{
			cv::Point pt = temp_homeChaBtn->GetSearchRect().tl();
			pt += { 5, 10 };
			if (!r_handler->KeepClickingUntil(pt, *temp_chaPage)) {
				return false;
			}
			break;
		}
		}
	}
	CoreLog() << "Task_Navigate: Success." << std::endl;
	sleep(milliseconds(30));
	return true;
}

void Task_Navigate::ShakeCursor() {
	CoreLog() << "Task_Navigate: ShakeCursor." << std::endl;
	r_handler->MoveMouseTo({ 0, 0 });
	r_handler->MoveMouseTo({ 960, 540 });
}


}
