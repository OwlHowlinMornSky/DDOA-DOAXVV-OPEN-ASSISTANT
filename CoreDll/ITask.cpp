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
#include "ITask.h"

#include "Task_StartUp.h"
#include "Task_Challenge.h"
#include "Task_LegacyCha.h"
#include "Task_TEST.h"
#include "Task_Navigate.h"

namespace ohms {

bool ITask::CreateTask(unsigned long type, std::unique_ptr<ITask>& outPtr) {
	switch (type) {
	case TaskEnum::StartUp:
		outPtr = std::make_unique<Task_StartUp>();
		return true;
	case TaskEnum::Daily:
		break;
	case TaskEnum::Room:
		break;
	case TaskEnum::Challenge:
		break;
	case TaskEnum::Spring:
		break;
	case TaskEnum::Award:
		break;
	case TaskEnum::Exit:
		break;
	case TaskEnum::LegacyCha:
		outPtr = std::make_unique<Task_LegacyCha>();
		return true;
	case TaskEnum::TEST_TASK:
		outPtr = std::make_unique<Task_TEST>();
		return true;
	default:
		break;
	}
	return false;
}

}
