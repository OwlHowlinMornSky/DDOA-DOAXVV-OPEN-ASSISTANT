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

#include "ITask.h"
#include "Settings_Challenge.h"
#include "WndHandler.h"

namespace ohms {

class Task_Challenge :
	public ITask {
public:
	Task_Challenge();
	virtual ~Task_Challenge() override;

public:
	virtual bool Run(Helper& h) override;

protected:
	Settings::Challenge m_set; // 设置数据的副本
	Helper* r_helper;
	WndHandler* r_handler;
	std::unique_ptr<MatchTemplate> m_camFp;
	std::unique_ptr<MatchTemplate> m_camFpDrink;
	std::unique_ptr<MatchTemplate> m_camFpDrinkComf;
	std::unique_ptr<MatchTemplate> m_camFpNo;
	std::unique_ptr<MatchTemplate> m_camFpComf[2];
};

}

