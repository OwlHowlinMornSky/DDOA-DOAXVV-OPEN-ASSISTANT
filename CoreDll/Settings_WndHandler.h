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

namespace ohms::Settings {

struct CORE_API WndHandler {
	static WndHandler DEFAULT; // 本体在 Settings.cpp
	WndHandler() :
		UseSendInput(false), // 默认发窗口消息
		Debug_ShowCapture(false),
		Debug_DebugHandler(false) {}

	bool UseSendInput; // 选择控制鼠标。

	bool Debug_ShowCapture; // [调试] 是否显示截取到的帧。
	bool Debug_DebugHandler; // [调试] 是否以DDOA调试器为目标。
};

}
