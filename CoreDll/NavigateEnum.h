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

namespace ohms {

namespace NavigateEnum {
enum Pape : int {
	None,

	Home, // 主页
	Challenge, // 挑战赛页面
	MatchConfirm, // 开始挑战的确认页面
	MatchResult, // 挑战结算页面
	AnyOtherHaveHomeBtn, // 任何 不确定 但 左侧有主页按钮 的页面
	AnyOtherHaveReturnBtn, // 任何 不确定 但 左侧有返回按钮 的页面

	COUNT
};
}

}
