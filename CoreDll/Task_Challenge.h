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
	bool SetHandler() const;
	bool LoadTemplates();
	void FirstNavigate();
	bool InitNavigate();
	void EnterConfirmPage();
	void StartMatch();
	bool HandleLowFp();
	void WaitingForEnd();
	void CheckForAwrad();

protected:
	Settings::Challenge m_set; // 设置数据的副本
	Helper* r_helper;
	WndHandler* r_handler;
	std::unique_ptr<MatchTemplate> temp_chaBar;
	std::unique_ptr<MatchTemplate> temp_lastFight;
	std::unique_ptr<MatchTemplate> temp_newFight;
	std::unique_ptr<MatchTemplate> temp_startGame;
	std::unique_ptr<MatchTemplate> temp_loading;
	std::unique_ptr<MatchTemplate> temp_lowFp;
	std::unique_ptr<MatchTemplate> temp_gameResult;
	std::unique_ptr<MatchTemplate> temp_awardCha;
	std::unique_ptr<MatchTemplate> m_camFp;
	std::unique_ptr<MatchTemplate> m_camFpDrink;
	std::unique_ptr<MatchTemplate> m_camFpDrinkComf;
	std::unique_ptr<MatchTemplate> m_camFpNo;
	std::unique_ptr<MatchTemplate> m_camFpComf[2];

	std::unique_ptr<MatchTemplate> m_act100pre[5];
	std::unique_ptr<MatchTemplate> m_actSlevel[5];

	enum class PlayMatch {
		Previous = 0,
		New,
		Activity,
		Award
	} target;
	int playCnt;
	int playAwardCnt;

	enum class LoopStatus {
		Begin = 0,
		Navigate,
		Enter,
		Start,
		Wait,
		Check,
		End
	} m_loopSt;
};

}

