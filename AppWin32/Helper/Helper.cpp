#include "Helper.h"

#include <iostream>
#include <thread>

namespace {

const WCHAR g_findCls[] = L"DOAX VenusVacation";
const WCHAR g_findWnd[] = L"DOAX VenusVacation";

}

namespace ohms {

Helper::Helper() :

	m_running(false),
	m_askedForStop(false),

	r_logger(nullptr),

	m_doaxvv(0),
	r_capture(nullptr)

{
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

void Helper::regLogger(ILogger* logger) {
	r_logger = logger;
}

void Helper::regForNew(bool forNew) {
	task_ChaGame_ForNew = forNew;
}

bool Helper::start() {
	if (!r_logger) {
		r_logger->addString(L"初始化错误");
		return false;
	}
	if (m_running) {
		r_logger->addString(L"不能重复运行任务");
		return false;
	}
	r_capture = wgc::ICapture::getInstance();
	if (!r_capture) {
		return false;
	}

	m_askedForStop = false;
	std::thread sub(&Helper::mainwork, this);
	sub.detach();
	return !sub.joinable();
}

void Helper::askForStop() {
	if (m_running) {
		r_logger->addString(L"正在停止...");
		m_askedForStop = true;
	}
	return;
}

bool Helper::isRunning() {
	return m_running;
}

bool Helper::msgPop(HelperReturnMessage& hrm) {
	std::lock_guard lg(m_hrm_mutex);
	if (m_hrm.empty()) {
		return false;
	}
	hrm = m_hrm.front();
	m_hrm.pop();
	return true;
}

void Helper::mainwork() {
	m_running = true;
	msgPush(HelperReturnMessage::BtnToStop);

	// 禁止关闭屏幕和睡眠
	SetThreadExecutionState(ES_CONTINUOUS | ES_SYSTEM_REQUIRED | ES_DISPLAY_REQUIRED);

	try {
		m_doaxvv = FindWindowW(g_findCls, g_findWnd);
		if (m_doaxvv == NULL) {
			r_logger->addString(L"Cannot find DOAXVV window.");
			throw 0;
		}
		if (!IsWindow(m_doaxvv) || IsIconic(m_doaxvv) || !r_capture->startCapture(m_doaxvv)) {
			r_logger->addString(L"Target cannot be captured.");
			throw 0;
		}

		// Run subworks.
		subwork_challenge();
	}
	catch (int err) {
		if (err != 0) {
			r_logger->addString(L" ");
			r_logger->addString(L"工作异常");
			MessageBoxW(NULL, L"工作异常", L"DOAXVV-helper: Task Error", MB_ICONERROR);
		}
	}
	catch (...) {
		r_logger->addString(L" ");
		r_logger->addString(L"工作异常");
		MessageBoxW(NULL, L"工作异常", L"DOAXVV-helper: Task Error", MB_ICONERROR);
	}
	r_capture->stopCapture();

	// 允许关闭屏幕和睡眠
	SetThreadExecutionState(ES_CONTINUOUS);

#ifdef OHMS_DDOA_SHOW
	cv::destroyAllWindows();
#endif // OHMS_DDOA_SHOW
	m_running = false;
	msgPush(HelperReturnMessage::BtnToStart);
	msgPush(HelperReturnMessage::Stopped);
	return;
}

void Helper::msgPush(ohms::HelperReturnMessage hrm) {
	std::lock_guard lg(m_hrm_mutex);
	m_hrm.push(hrm);
	return;
}

} // namespace ohms
