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
#include "Settings.h"

namespace ohms {

Settings Settings::mainSettings;

Settings::Settings() :
	Mouse_ForMouse(false), // 默认发窗口消息
	PreventFromSleep(true), // 默认阻止睡眠
	KeepDisplay(false), // 默认不保持显示

	ChaGame_ForNew(false), // 默认上一次比赛
	ChaGame_EnterAddition(true), // 默认进入奖励挑战赛
	ChaGame_CheckAddition(false) // 默认不检查奖励挑战赛
{}

}
