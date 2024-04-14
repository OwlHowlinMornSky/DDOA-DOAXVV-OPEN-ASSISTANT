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
#include "TaskEnum.h"

namespace ohms::Settings {

struct CORE_API Global {
	static Global DEFAULT; // 本体在 Settings.cpp
	Global() :
		KeepAwake(true), // 默认阻止睡眠
		KeepScreenOn(false), // 默认不保持显示
		Work_TaskList() // 默认为空
	{}

	bool KeepAwake; // 阻止睡眠。
	bool KeepScreenOn; // 阻止睡眠同时保持显示。

	ohms::TaskEnum Work_TaskList[32]; // 选择任务并设置顺序。
};

}
