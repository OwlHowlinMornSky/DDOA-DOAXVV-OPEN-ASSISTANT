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
	task_Mouse_ForMouse(false) // 默认发窗口消息

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

void Helper::regForNew(bool forNew) {
	task_ChaGame_ForNew = forNew;
}

void Helper::regForMouse(bool forMouse) {
	task_Mouse_ForMouse = forMouse;
}

bool Helper::start() {
	if (m_running) { // 已经有任务运行（或者有bug没清除运行标记）
		msgPush(HelperReturnMessage::Log_ErrorIsRunning);
		return false;
	}
	r_capture = wgc::ICapture::getInstance(); // 获取capture索引
	if (!r_capture) { // capture获取失败（但是App初始化获取成功才运行过来，所以这个理论上永远不会触发）
		return false;
	}
	r_capture->setClipToClientArea(true);

	m_askedForStop = false; // 清除运行标志（绝对不能移动到上面去）
	std::thread sub(&Helper::mainwork, this);
	sub.detach(); // 在子线程运行工作
	return !sub.joinable();
}

void Helper::askForStop() {
	if (m_running) { // 运行的时候才有意义
		msgPush(HelperReturnMessage::Log_Stopping);
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

void Helper::mainwork() {
	m_running = true; // 设置标记（return前要清除）
	msgPush(HelperReturnMessage::BtnToStop); // 让主按钮变为stop

	// 防止关闭屏幕和睡眠
	SetThreadExecutionState(ES_CONTINUOUS | ES_SYSTEM_REQUIRED | ES_DISPLAY_REQUIRED);

	try {
		m_doaxvv = FindWindowW(g_findCls, g_findWnd); // 查找doaxvv窗口
		if (m_doaxvv == NULL) {
			msgPush(HelperReturnMessage::Log_ErrorNotFindWnd);
			throw 0;
		}
		if (!IsWindow(m_doaxvv) || IsIconic(m_doaxvv) || !r_capture->startCapture(m_doaxvv)) { // 这些是能截图的必要条件
			msgPush(HelperReturnMessage::Log_ErrorCannotCapture);
			throw 0;
		}

		// Run subworks.
		subwork_challenge();
	}
	catch (int err) {
		// catch 到 0 是 主动停止，不是 0 则是错误
		if (err != 0) {
			msgPush(HelperReturnMessage::Log_ErrorInWork);
		}
	}
	catch (...) {
		msgPush(HelperReturnMessage::Log_ErrorInWork);
	}
	r_capture->stopCapture(); // 停止截图

	// 允许关闭屏幕和睡眠
	SetThreadExecutionState(ES_CONTINUOUS);

	cv::destroyAllWindows(); // 销毁show窗口

	m_running = false; // 清除标记
	msgPush(HelperReturnMessage::BtnToStart); // 让主按钮变成start
	msgPush(HelperReturnMessage::Stopped); // 通知已完全停止
	return;
}

void Helper::msgPush(unsigned long hrm) {
	std::lock_guard lg(m_hrm_mutex); // 上锁
	m_hrm.push(hrm); // 压入
	return;
}

void Helper::msgPush(unsigned long hrm, unsigned long code) {
	std::lock_guard lg(m_hrm_mutex); // 上锁
	m_hrm.push(hrm); // 压入
	m_hrm.push(code); // 压入
	return;
}

} // namespace ohms
