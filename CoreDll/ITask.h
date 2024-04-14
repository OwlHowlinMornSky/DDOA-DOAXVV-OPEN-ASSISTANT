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

#include "TaskEnum.h"
#include <memory>
#include "Helper.h"

namespace ohms {

class ITask {
public:
	ITask() = default;
	virtual ~ITask() = default;

	virtual bool Run(Helper& h) = 0;

protected:
	TaskEnum m_taskType;

public:
	static bool CreateTask(TaskEnum type, std::unique_ptr<ITask>& outPtr);
};

}
