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

#include "ITask.h"
#include "NavigateEnum.h"

namespace ohms {

class Task_Navigate :
	public ITask {
public:
	Task_Navigate();
	virtual ~Task_Navigate() = default;

	static Task_Navigate* Instance();
	static void Drop();

public:
	virtual bool Run(Helper& h) override;

public:
	int TryToDeterminePage();
	bool NavigateTo(int dest);
	bool NavigateFromTo(int now, int dest);

protected:
	WndHandler* r_handler;
	Helper* r_helper;
	std::unique_ptr<MatchTemplate> temp_chaPage;
	std::unique_ptr<MatchTemplate> temp_matchPage;
	std::unique_ptr<MatchTemplate> temp_homePage;
	std::unique_ptr<MatchTemplate> temp_resultPage;
	std::unique_ptr<MatchTemplate> temp_anyOtherPageHaveReturn;
	std::unique_ptr<MatchTemplate> temp_anyOtherPageHaveHome;
	std::unique_ptr<MatchTemplate> temp_anyOtherPageHaveHomeW;
	std::unique_ptr<MatchTemplate> temp_homeChaBtn;
};

}
