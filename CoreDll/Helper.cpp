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
#include <opencv2/highgui.hpp>

#include "Helper.h"

#include <iostream>
#include <fstream>
#include <thread>

#include "Settings.h"
#include "AskedForStop.h"
#include "TaskExceptionCode.h"

#include "CoreLog.h"
#include "ITask.h"

namespace ohms {

Helper::Helper() :
	r_handler(nullptr),
	m_running(false) // 初始未运行
{
	return;
}

Helper::~Helper() {}

int Helper::setup(bool winrtInited) {
	if (!SetupLog())
		return 1;

	m_assets.assign("assets");
	CoreLog() << "Helper set assets folder path as " << m_assets << '.' << std::endl;

	std::ifstream ifs;
	ifs.open(m_assets / "tempLists.ini");
	if (!ifs.is_open()) {
		CoreLog() << "Helper failed to opens template lists." << std::endl;
		return 2;
	}
	CoreLog() << "Helper opened template lists." << std::endl;

	size_t sz;
	ifs >> sz;
	for (size_t i = 0; i < sz; ++i) {
		std::string name;
		bool fix;
		unsigned short thres;
		int r0, r1, r2, r3;
		ifs >> name >> fix >> thres >> r0 >> r1 >> r2 >> r3;
		CoreLog() << "Helper read template [" << name << "]." << std::endl;

		m_templateList.emplace(name, MatchTemplateInfo(fix, thres, { r0, r1, r2, r3 }));
	}
	CoreLog() << "Helper have read " << sz << " templates." << std::endl;

	r_handler = WndHandler::Instance(winrtInited);
	return 0;
}

bool Helper::start() {
	if (m_running) { // 已经有任务运行（或者有bug没清除运行标记）
		PushMsg(ReturnMsgEnum::LOG_StartError_Running);
		CoreLog() << "Helper: Unexpected Start Repeatly. [Failed to Start]" << std::endl;
		return false;
	}

	r_handler = WndHandler::Instance();
	if (r_handler == nullptr) {
		CoreLog() << "Helper: Handler Unavailable. [Failed to Start]" << std::endl;
		return false;
	}
	if (!r_handler->Update()) {
		CoreLog() << "Helper: Handler Failed to Update. [Failed to Start]" << std::endl;
		return false;
	}

	g_askedForStop = false; // 清除运行标志（绝对不能移动到上面去）
	std::thread sub(&Helper::Work, this);
	CoreLog() << "Helper: Detach Thread! [Start]" << std::endl;
	sub.detach(); // 在子线程运行工作
	return !sub.joinable();
}

void Helper::askForStop() {
	if (m_running) { // 运行的时候才有意义
		PushMsg(ReturnMsgEnum::LOG_Stopping);
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
		return ReturnMsgEnum::None;
	}
	// 获取队首并弹出
	unsigned long res = m_hrm.front();
	m_hrm.pop();
	return res;
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
		TaskError(ReturnMsgEnum::STR_Task_FailedToLoadTemplateFile);
		return std::unique_ptr<MatchTemplate>();
	}
	return std::move(res);
}

void Helper::TaskError(unsigned long type) {
	PushMsgCode(ReturnMsgEnum::LOG_TaskError, type);
	throw TaskExceptionCode::KnownErrorButNotCritical; // 要求停止
}

void Helper::Work() {
	m_running = true; // 设置标记（return前要清除）
	PushMsg(ReturnMsgEnum::CMD_BtnToStop); // 让主按钮变为stop

	Settings::Global m_set = Settings::Global::DEFAULT;

	// 按设置防止关闭屏幕和睡眠
	if (m_set.KeepAwake) {
		SetThreadExecutionState(
			ES_CONTINUOUS | ES_SYSTEM_REQUIRED |
			(m_set.KeepScreenOn ? ES_DISPLAY_REQUIRED : 0)
		);
	}

	try {
		size_t flag = 0;
		std::unique_ptr<ITask> task;
		while (
			flag < Settings::Global::ListLength &&
			m_set.Work_TaskList[flag] != TaskEnum::None
			) {
			if (ITask::CreateTask(m_set.Work_TaskList[flag], task)) {
				bool res = task->Run(*this);
				if (!res) // 返回false表示无法继续
					break;
			}
			flag++;
		}
	}
	catch (...) {
		PushMsg(ReturnMsgEnum::LOG_WorkError_ExceptionInternalError);
	}
	r_handler->Reset(); // 停止截图

	// 允许关闭屏幕和睡眠
	SetThreadExecutionState(ES_CONTINUOUS);

	if (g_askedForStop) {
		PushMsg(ReturnMsgEnum::LOG_Stopped);
	}
	else {
		PushMsg(ReturnMsgEnum::LOG_Complete);
	}
	m_running = false; // 清除标记
	PushMsg(ReturnMsgEnum::CMD_BtnToStart); // 让主按钮变成start
	PushMsg(ReturnMsgEnum::CMD_Stopped); // 通知已完全停止

	cv::destroyAllWindows();
	return;
}

} // namespace ohms
