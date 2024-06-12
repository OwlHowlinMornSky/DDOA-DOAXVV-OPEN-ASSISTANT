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
#include "Task_Record.h"

#include "WndHandler.h"
#include "Settings_WndHandler.h"

#include "../HookDll/DdoaHookProc.h"

namespace {

std::unique_ptr<ohms::Task_Record> g_instance;

}

namespace ohms {

Task_Record* Task_Record::Instance() {
	if (g_instance == nullptr) {
		g_instance = std::make_unique<Task_Record>();
	}
	return g_instance.get();
}

void Task_Record::Drop() {
	g_instance.release();
	return;
}

bool Task_Record::Run(Helper& h) {
	return true;
}

int Task_Record::start() {
	m_started = false;

	auto handler = WndHandler::Instance();
	handler->Update();

	m_oldSet = Settings::WndHandler::DEFAULT.UseHook;
	Settings::WndHandler::DEFAULT.UseHook = false;

	auto code = handler->SetForGame();
	if (code != WndHandler::SetReturnValue::OK) {
		return 3;
	}

	int res = Hook::StartRecord();
	if (res != 0) {
		stop();
		return res;
	}

	if (!handler->StartRecord()) {
		stop();
		return 4;
	}

	m_started = true;
	return 0;
}

int Task_Record::stop() {
	auto handler = WndHandler::Instance();

	if (m_started) {
		handler->StopRecord();
	}

	if (Hook::StopRecord() != 0) {
		return 1;
	}

	handler->Reset();

	Settings::WndHandler::DEFAULT.UseHook = m_oldSet;

	m_started = false;

	return 0;
}

}
