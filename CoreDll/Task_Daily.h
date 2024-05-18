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
#include "WndHandler.h"
#include "Settings_Daily.h"

namespace ohms {

class Task_Daily :
	public ITask {
public:
	Task_Daily();
	virtual ~Task_Daily() override;

public:
	virtual bool Run(Helper& h) override;

protected:
	void DoCheck();
	void DoShot();

	bool IsDailCheckDone();
	bool OpenDailyCheckBoard();
	bool DoDailyCheckInBoard();
	bool CloseCheckBoard();

	bool IsShotDone();
	bool OpenShotPage();
	bool DoShotInPage();
	bool CloseShotPage();

protected:
	Helper* r_helper;
	WndHandler* r_handler;

	Settings::Daily m_set;

	std::unique_ptr<MatchTemplate> m_homeDailyBtn;
	std::unique_ptr<MatchTemplate> m_homeDailyDot;
	std::unique_ptr<MatchTemplate> m_checkBtn;
	std::unique_ptr<MatchTemplate> m_checkBdTitle;
	std::unique_ptr<MatchTemplate> m_checkOk;

	std::unique_ptr<MatchTemplate> m_homePage;
	std::unique_ptr<MatchTemplate> m_shotEntrance;
	std::unique_ptr<MatchTemplate> m_shotDot;
	std::unique_ptr<MatchTemplate> m_shotBack;
	std::unique_ptr<MatchTemplate> m_shot;
};

}
