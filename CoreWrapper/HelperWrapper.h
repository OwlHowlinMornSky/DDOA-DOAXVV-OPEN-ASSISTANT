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
#pragma once

#include <IHelper.h>
#include "ReturnMessages.h"

namespace Wrapper {

public ref class HelperWrapper {
public:
	HelperWrapper();
	~HelperWrapper();

public:
	System::Boolean Start();
	System::Void AskForStop();
	System::Boolean IsRunning();

	ReturnMessage GetMessage();
	System::UInt32 GetCode();

	System::Void Drop();

public:
	/**
	 * @brief 设置是否显示调试性截图。
	 * @param show 为 true 则显示截图。
	 * @return 0 if success.
	*/
	System::Int32 SetShowCaptureOrNot(bool show);
	/**
	 * @brief 设置挑战赛打新比赛或上一次比赛。
	 * @param forNew 为 true 则打新比赛，否则打上一次比赛
	 * @return 0 if success.
	*/
	System::Int32 SetChallengeForNewOrLast(bool forNew);
	/**
	 * @brief 设置鼠标操作 发送输入 还是 窗口消息。
	 * @param sendInput 为 true 则使用鼠标输入，否则发送窗口消息。
	 * @return 0 if success.
	*/
	System::Int32 SetMouseSendInputOrSendMessage(bool sendInput);
	/**
	 * @brief 设置是否阻止睡眠。
	 * @param keep 为 true 则阻止睡眠。
	 * @return 0 if success.
	*/
	System::Int32 SetKeepAwakeOrNot(bool keep);
	/**
	 * @brief 设置阻止关闭屏幕。
	 * @param keep 为 true 则阻止。
	 * @return 0 if success.
	*/
	System::Int32 SetKeepScreenOnOrNot(bool keep);
	/**
	 * @brief 设置挑战赛运行时是否检测奖励挑战赛。
	 * @param check 为 true 则检测。
	 * @return 0 if success.
	*/
	System::Int32 SetChallengeCheckAwardOrNot(bool check);
	/**
	 * @brief 设置是否进入奖励挑战赛。
	 * @param play 为 true 则进入。
	 * @return 0 if success.
	*/
	System::Int32 SetChallengePlayAwardOrNot(bool play);

private:
	ohms::IHelper* r_helper;
};

} // namespace Wrapper
