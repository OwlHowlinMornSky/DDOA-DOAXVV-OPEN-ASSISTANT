#include "Helper.h"

#include <iostream>
#include <thread>

namespace {

const WCHAR g_findCls[] = L"DOAX VenusVacation";
const WCHAR g_findWnd[] = L"DOAX VenusVacation";

}

namespace ohms {

Helper::Helper() :

	m_doaxvv(0),
	r_logger(nullptr),

	m_askedForStop(false),
	m_running(false),
	r_capture(nullptr)

{
	m_lastFight = cv::imread("assets/lastFight.png");
	m_newFight = cv::imread("assets/newFight.png");
	m_rect_fight = { 600, 240, 100, 300 }; // 600 -> 700, 240 -> 540

	m_start = cv::imread("assets/start.png");
	m_rect_start = { 700, 470, 200, 70 }; // 700 -> 900, 470 -> 540

	m_result = cv::imread("assets/result.png");
	m_rect_result = { 640, 35, 320, 70 }; // 640 -> 960, 140 ( 35 -> 105 )

	m_loading = cv::imread("assets/loading.png");
	m_rect_loading = { 0, 0, 300, 180 }; // 300, 180

	m_fp = cv::imread("assets/fp.png");
	m_rect_fp = { 256, 60, 400, 210 }; // 256 -> 656, 60 -> 270

	m_default = cv::imread("assets/default.png");
	m_rect_default = { 640, 80, 320, 190 }; // 640 -> 960, 80 -> 270

	return;
}

Helper::~Helper() {}

void Helper::regLogger(Logger* logger) {
	r_logger = logger;
}

void Helper::regForNew(bool forNew) {
	m_task_forNew = forNew;
}

bool Helper::start() {
	if (!r_logger) {
		std::cout << "Logger not registered!" << std::endl;
		return false;
	}
	if (m_running) {
		r_logger->addString(L"不能重复运行任务");
		return false;
	}
	r_capture = wgc::getInstance();
	if (!r_capture) {
		return false;
	}

	m_askedForStop = false;
	std::thread sub(&Helper::work, this);
	sub.detach();
	return !sub.joinable();
}

void Helper::askForStop() {
	if (m_running) {
		r_logger->addString(L" ");
		r_logger->addString(L"正在停止...");
		m_askedForStop = true;
	}
	return;
}

bool Helper::isRunning() {
	return m_running;
}

bool Helper::popMessage(HelperReturnMessage& hrm) {
	std::lock_guard lg(mutexHRM);
	if (helperReturnMessage.empty()) {
		return false;
	}
	hrm = helperReturnMessage.front();
	helperReturnMessage.pop();
	return true;
}

void Helper::pushHRM(ohms::HelperReturnMessage hrm) {
	std::lock_guard lg(mutexHRM);
	helperReturnMessage.push(hrm);
	return;
}

void Helper::work() {
	m_running = true;
	pushHRM(HelperReturnMessage::BtnToStop);

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

		/*RECT wndOldPos{0};
		GetWindowRect(ohms::global::doaxvv, &wndOldPos);
		SetWindowPos(
			ohms::global::doaxvv, NULL, 2000, 100, 0, 0,
			SWP_NOZORDER | SWP_NOREDRAW | SWP_NOSIZE | SWP_NOSENDCHANGING
		);*/

		// Run subworks.
		subwork_fight();

		/*SetWindowPos(
			ohms::global::doaxvv, NULL, wndOldPos.left, wndOldPos.top, 0, 0,
			SWP_NOZORDER | SWP_NOREDRAW | SWP_NOSIZE | SWP_NOSENDCHANGING
		);*/
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
	pushHRM(HelperReturnMessage::BtnToStart);
	pushHRM(HelperReturnMessage::Stopped);
	return;
}

} // namespace ohms
