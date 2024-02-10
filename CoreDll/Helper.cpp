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
#include <thread>

namespace {

const WCHAR g_findCls[] = L"DOAX VenusVacation"; // 查找doaxvv窗口的类的名字
const WCHAR g_findWnd[] = L"DOAX VenusVacation"; // 查找doaxvv窗口的名字

}

namespace ohms {

Helper::Helper() :

	m_running(false), // 未运行
	m_askedForStop(false), // 没有要求停止

	m_doaxvv(0), // 初始未查找
	r_capture(nullptr), // 初始无索引

	task_ChaGame_ForNew(false), // 默认上一次比赛
	task_Mouse_ForMouse(false), // 默认发窗口消息

	task_PreventFromSleep(true), // 默认阻止睡眠
	task_KeepDisplay(false) // 默认不保持显示

{
	if (!wgc::ICapture::setup(true)) {
		MessageBoxW(NULL, L"Failed to setup WGC", L"DDOA", MB_ICONERROR);
		throw 1;
	}

	// 初始化各种mat目标和相应搜索范围
	mat_ChaGameLast = cv::imread("assets/lastFight.png");
	mat_ChaGameNew = cv::imread("assets/newFight.png");
	rect_ChaGame = { 600, 240, 100, 300 }; // 600 -> 700, 240 -> 540

	mat_StartGame = cv::imread("assets/start.png");
	rect_StartGame = { 700, 470, 200, 70 }; // 700 -> 900, 470 -> 540

	mat_Result = cv::imread("assets/result.png");
	rect_Result = { 640, 35, 320, 70 }; // 640 -> 960, 140 ( 35 -> 105 )

	mat_Loading = cv::imread("assets/loading.png");
	rect_Loading = { 0, 0, 300, 180 }; // 300, 180

	mat_LowFP = cv::imread("assets/fp.png");
	rect_LowFP = { 256, 60, 400, 210 }; // 256 -> 656, 60 -> 270

	mat_ChaTabBar = cv::imread("assets/default.png");
	rect_ChaTabBar = { 640, 80, 320, 190 }; // 640 -> 960, 80 -> 270
	return;
}

Helper::~Helper() {}

long Helper::regForNew(bool forNew) {
	if (m_running)
		return 1l;
	task_ChaGame_ForNew = forNew;
	return 0l;
}

long Helper::regForMouse(bool forMouse) {
	if (m_running)
		return 1l;
	task_Mouse_ForMouse = forMouse;
	return 0l;
}

long Helper::regPrevent(bool prevent) {
	if (m_running)
		return 1l;
	task_PreventFromSleep = prevent;
	return 0l;
}

long Helper::regPreventKeepDisplay(bool keep) {
	if (m_running)
		return 1l;
	task_KeepDisplay = keep;
	return 0l;
}

bool Helper::start() {
	if (m_running) { // 已经有任务运行（或者有bug没清除运行标记）
		PushMsg(HelperReturnMessage::LOG_StartError_Running);
		return false;
	}
	r_capture = wgc::ICapture::getInstance(); // 获取capture索引
	if (!r_capture) { // capture获取失败（但是App初始化获取成功才运行过来，所以这个理论上永远不会触发）
		return false;
	}
	r_capture->setClipToClientArea(true);

	m_askedForStop = false; // 清除运行标志（绝对不能移动到上面去）
	std::thread sub(&Helper::Work, this);
	sub.detach(); // 在子线程运行工作
	return !sub.joinable();
}

void Helper::askForStop() {
	if (m_running) { // 运行的时候才有意义
		PushMsg(HelperReturnMessage::LOG_Stopping);
		m_askedForStop = true;
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
	if (task_PreventFromSleep) {
		SetThreadExecutionState(
			ES_CONTINUOUS | ES_SYSTEM_REQUIRED |
			(task_KeepDisplay ? ES_DISPLAY_REQUIRED : 0)
		);
	}

	try {
		m_doaxvv = FindWindowW(g_findCls, g_findWnd); // 查找doaxvv窗口
		if (m_doaxvv == NULL) {
			PushMsg(HelperReturnMessage::LOG_WorkError_NoWnd);
			throw 0;
		}
		if (!IsWindow(m_doaxvv) || IsIconic(m_doaxvv) || !r_capture->startCapture(m_doaxvv)) { // 这些是能截图的必要条件
			PushMsg(HelperReturnMessage::LOG_WorkError_FailedCapture);
			throw 0;
		}

		// Run subworks.
		Task_Challenge();
	}
	catch (int err) {
		// catch 到 0 是 主动停止，不是 0 则是错误
		if (err != 0) {
			PushMsg(HelperReturnMessage::LOG_WorkError_Exception);
		}
	}
	catch (...) {
		PushMsg(HelperReturnMessage::LOG_WorkError_Exception);
	}
	r_capture->stopCapture(); // 停止截图

	// 允许关闭屏幕和睡眠
	SetThreadExecutionState(ES_CONTINUOUS);

	cv::destroyAllWindows(); // 销毁show窗口

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

} // namespace ohms
