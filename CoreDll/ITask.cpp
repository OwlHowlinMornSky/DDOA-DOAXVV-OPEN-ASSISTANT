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

#include "Sleep.h"
#include "Clock.h"
#include "AskedForStop.h"
#include "Task_StartUp.h"
#include "Task_Challenge.h"
#include "Task_TEST.h"
#include "Task_Navigate.h"
#include "Task_Daily.h"
#include "CoreLog.h"

namespace ohms {

void ITask::TaskSleep(Time time) {
	CoreLog() << "Task slept for " << time.asMicroseconds() << "us." << std::endl;
	Clock clk;
	while (true) {
		if (g_askedForStop) {
			throw 0;
		}
		if (time > 60_msec) {
			sleep(60_msec);
			time = time - clk.restart();
		}
		else if(time > Time::Zero) {
			sleep(time);
			break;
		}
		else {
			break;
		}
	}
}

bool ITask::CreateTask(unsigned long type, std::unique_ptr<ITask>& outPtr) {
	switch (type) {
	case TaskEnum::StartUp:
		CoreLog() << "Create task: Task_StartUp" << std::endl;
		outPtr = std::make_unique<Task_StartUp>();
		return true;
	case TaskEnum::Daily:
		CoreLog() << "Create task: Task_Daily" << std::endl;
		outPtr = std::make_unique<Task_Daily>();
		return true;
	case TaskEnum::Room:
		CoreLog() << "Create task: Task_Room" << std::endl;
		break;
	case TaskEnum::Challenge:
		CoreLog() << "Create task: Task_Challenge" << std::endl;
		outPtr = std::make_unique<Task_Challenge>();
		return true;
	case TaskEnum::Spring:
		CoreLog() << "Create task: Task_Spring" << std::endl;
		break;
	case TaskEnum::Award:
		CoreLog() << "Create task: Task_Award" << std::endl;
		break;
	case TaskEnum::Exit:
		CoreLog() << "Create task: Task_Exit" << std::endl;
		break;
	case TaskEnum::TEST_TASK:
		CoreLog() << "Create task: Task_TEST" << std::endl;
		outPtr = std::make_unique<Task_TEST>();
		return true;
	default:
		break;
	}
	CoreLog() << "Create task [Not implement]" << std::endl;
	return false;
}

}
