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
#pragma once

#include "API.h"

#include <atomic>

namespace ohms {

struct CORE_API Settings {
	bool Mouse_ForMouse; // 选择控制鼠标。
	bool PreventFromSleep; // 阻止睡眠。
	bool KeepDisplay; // 阻止睡眠同时保持显示。

	bool ChaGame_ForNew; // 选择新比赛。
	bool ChaGame_EnterAddition; // 进入奖励挑战赛。
	bool ChaGame_CheckAddition; // 是否检查奖励挑战赛。

	Settings();

	static Settings mainSettings;
	static Settings g_set;

	static void MakeOneCopy();

	static std::atomic_bool g_askedForStop; // 请求停止的标记。true为需要停止
};

}
