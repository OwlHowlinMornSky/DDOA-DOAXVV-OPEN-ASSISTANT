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
#include "Helper.h"

#include <iostream>
#include <fstream>
#include <thread>

#include "Settings.h"
#include "AskedForStop.h"
#include "TaskExceptionCode.h"

namespace ohms {

Helper::Helper() :
	m_running(false) // 未运行
{
	return;
}

Helper::~Helper() {}

int Helper::setup() {
	m_assets.assign("assets");

	std::ifstream ifs;
	ifs.open(m_assets / "tempLists.ini");

	if (!ifs.is_open())
		return 1;

	size_t sz;
	ifs >> sz;
	for (size_t i = 0; i < sz; ++i) {
		std::string name;
		bool fix;
		unsigned short thres;
		int r0, r1, r2, r3;
		ifs >> name >> fix >> thres >> r0 >> r1 >> r2 >> r3;

		m_templateList.emplace(name, MatchTemplateInfo(fix, thres, { r0, r1, r2, r3 }));
	}

	return 0;
}

bool Helper::start() {
	if (m_running) { // 已经有任务运行（或者有bug没清除运行标记）
		PushMsg(HelperReturnMessage::LOG_StartError_Running);
		return false;
	}

	r_handler = WndHandler::Instance();
	if (r_handler == nullptr) {
		return false;
	}
	if (!r_handler->Update()) {
		return false;
	}

	g_askedForStop = false; // 清除运行标志（绝对不能移动到上面去）
	ohms::Settings::MakeOneCopy();
	std::thread sub(&Helper::Work, this);
	sub.detach(); // 在子线程运行工作
	return !sub.joinable();
}

void Helper::askForStop() {
	if (m_running) { // 运行的时候才有意义
		PushMsg(HelperReturnMessage::LOG_Stopping);
		g_askedForStop = true;
	}
	return;
}

bool Helper::isRunning() {
	return m_running;
}

unsigned long Helper::msgPop() {
	std::lock_guard lg(m_hrm_mutex); // 上锁
	if (m_hrm.empty()) { // 没有消息
		return HelperReturnMessage::None;
	}
	// 获取队首并弹出
	unsigned long res = m_hrm.front();
	m_hrm.pop();
	return res;
}

void Helper::Work() {
	m_running = true; // 设置标记（return前要清除）
	PushMsg(HelperReturnMessage::CMD_BtnToStop); // 让主按钮变为stop

	// 按设置防止关闭屏幕和睡眠
	if (Settings::g_set.KeepAwake) {
		SetThreadExecutionState(
			ES_CONTINUOUS | ES_SYSTEM_REQUIRED |
			(Settings::g_set.KeepScreenOn ? ES_DISPLAY_REQUIRED : 0)
		);
	}

	try {
		// Run task.
		Task_Challenge();
	}
	catch (...) {
		PushMsg(HelperReturnMessage::LOG_WorkError_ExceptionInternalError);
	}
	r_handler->Reset(); // 停止截图

	// 允许关闭屏幕和睡眠
	SetThreadExecutionState(ES_CONTINUOUS);

	if (g_askedForStop) {
		PushMsg(HelperReturnMessage::LOG_Stopped);
	}
	else {
		PushMsg(HelperReturnMessage::LOG_Complete);
	}
	m_running = false; // 清除标记
	PushMsg(HelperReturnMessage::CMD_BtnToStart); // 让主按钮变成start
	PushMsg(HelperReturnMessage::CMD_Stopped); // 通知已完全停止
	return;
}

void Helper::PushMsg(unsigned long hrm) {
	std::lock_guard lg(m_hrm_mutex); // 上锁
	m_hrm.push(hrm); // 压入
	return;
}

void Helper::PushMsgCode(unsigned long hrm, unsigned long code) {
	std::lock_guard lg(m_hrm_mutex); // 上锁
	m_hrm.push(hrm); // 压入
	m_hrm.push(code); // 压入
	return;
}

std::unique_ptr<MatchTemplate> Helper::CreateTemplate(const std::string& name) {
	std::unique_ptr<MatchTemplate> res = std::make_unique<MatchTemplate>(m_templateList.at(name));
	if (!res->LoadMat((m_assets / (name + ".png")).string())) {
		Step_TaskError(HelperReturnMessage::STR_Task_FailedToLoadTemplateFile);
		return std::unique_ptr<MatchTemplate>();
	}
	return std::move(res);
}

} // namespace ohms
