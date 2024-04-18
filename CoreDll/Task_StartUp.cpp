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

namespace ohms {

Task_StartUp::Task_StartUp() :
	r_handler(nullptr),
	r_helper(nullptr) {}

Task_StartUp::~Task_StartUp() {}

bool Task_StartUp::Run(Helper& h) {
	r_handler = WndHandler::Instance();
	r_helper = &h;

	if (r_handler->SetForGame() != WndHandler::SetReturnValue::OK) {
		if (r_handler->SetForLauncher() != WndHandler::SetReturnValue::OK) {
			system("start steam://rungameid/958260");
			do {
				Sleep(1000);
			} while (r_handler->SetForLauncher() != WndHandler::SetReturnValue::OK);
		}

		//r_handler->ClickAt();// 点击开始。

		do {
			Sleep(1000);
		} while (r_handler->SetForGame() != WndHandler::SetReturnValue::OK);
	}
	return true;
}

}
