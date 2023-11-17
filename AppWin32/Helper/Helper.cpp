#include "Helper.h"

#include "../Global.h"

#include <thread>

namespace ohms {

Helper::Helper() :

	m_doaxvv(0),
	r_logger(nullptr),

	m_askedForStop(false),
	m_running(false),
	r_capture(nullptr)

{

	m_lastFight = cv::imread("assets/lastFight.png");
	m_start = cv::imread("assets/start.png");
	m_result = cv::imread("assets/result.png");
	m_loading = cv::imread("assets/loading.png");
	m_fp = cv::imread("assets/fp.png");
	m_default = cv::imread("assets/default.png");

	return;
}

Helper::~Helper() {}

bool Helper::start(HWND doaxvv, Logger* logger) {
	if (m_running) {
		std::cout << "It is now running!" << std::endl;
		return false;
	}
	r_capture = wgc::getInstance();
	if (!r_capture) {
		return false;
	}

	m_doaxvv = doaxvv;
	r_logger = logger;

	m_askedForStop = false;
	std::thread sub(&Helper::work, this);
	sub.detach();
	return !sub.joinable();
}

void Helper::askForStop() {
	m_askedForStop = true;
	r_logger->addString(L" ");
	r_logger->addString(L"正在停止...");
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

#ifndef _DEBUG
	if (ohms::global::show)
#endif // _DEBUG
		cv::destroyAllWindows();


	m_running = false;
	pushHRM(HelperReturnMessage::BtnToStart);
	pushHRM(HelperReturnMessage::Stopped);

	return;
}

void Helper::subwork_fight() {
	r_logger->addString(L"开始任务: 挑战赛");

	cv::Rect rect;
	cv::Point pt;

	size_t i = 0;

begin_point:
	++i;
	r_logger->addString(L" ");
	r_logger->addString(
		std::wstring(L"开始第 ") + std::to_wstring(i) + L" 次比赛"
	);

	r_logger->addString(L"开始查找 上一次比赛");
	// 查找“上一次比赛”
	rect = { 600, 240, 100, 300 }; // 600 -> 700, 240 -> 540
	if (!step_waitFor(true, m_lastFight, rect, seconds(15.0f))) {
		r_logger->addString(L" ");
		r_logger->addString(L"任务出错: 找不到上一次比赛");
		m_askedForStop = true;
		MessageBoxW(NULL, L"找不到上一次比赛", L"DOAXVV-helper: Task Error", MB_ICONERROR);
	}
	if (m_askedForStop)
		goto end_point;
	r_logger->addString(L"找到 上一次比赛");

	r_logger->addString(L"点击 上一次比赛");
	// 点击上一次比赛，直到进入编队画面（找到挑战按钮）。
	pt = cv::Point(rect.x + 250, rect.y);
	rect = { 700, 470, 200, 70 }; // 700 -> 900, 470 -> 540
	if (!keepClickingUntil(
		pt,
		rect,
		m_start,
		10
	)) {
		r_logger->addString(L" ");
		r_logger->addString(L"任务出错: 无法进入上一次比赛");
		m_askedForStop = true;
		MessageBoxW(NULL, L"无法进入上一次比赛", L"DOAXVV-helper: Task Error", MB_ICONERROR);
	}
	if (m_askedForStop)
		goto end_point;
	r_logger->addString(L"已进入 编队页面");

	r_logger->addString(L"开始查找 挑战 按钮");
	// 查找“挑战”按钮。
	rect = { 700, 470, 200, 70 }; // 700 -> 900, 470 -> 540
	step_waitFor(true, m_start, rect);
	if (m_askedForStop)
		goto end_point;
	r_logger->addString(L"找到 挑战 按钮");

	r_logger->addString(L"点击 挑战 按钮");
	{
		size_t tc = 0;
		while (!m_askedForStop) {
			// 点击挑战，直到进入加载画面。
			pt = cv::Point(rect.x + 50, rect.y + 20);
			cv::Rect ld_rect{ 0, 0, 300, 180 }; // 300, 180
			if (keepClickingUntil(
				pt,
				ld_rect,
				m_loading,
				4,
				seconds(0.5f),
				20
			)) {
				break;
			}
			cv::Rect fp_rect;
			fp_rect = { 256, 60, 400, 210 }; // 256 -> 656, 60 -> 270
			if (step_waitFor(true, m_fp, fp_rect, milliseconds(1000))) {
				r_logger->addString(L" ");
				r_logger->addString(L"任务出错: FP耗尽");
				m_askedForStop = true;
				MessageBoxW(NULL, L"FP耗尽", L"DOAXVV-helper: Task Error", MB_ICONERROR);
				break;
			}
			if (++tc > 10) {
				r_logger->addString(L" ");
				r_logger->addString(L"任务出错: 进入挑战超时");
				m_askedForStop = true;
				MessageBoxW(NULL, L"进入挑战超时", L"DOAXVV-helper: Task Error", MB_ICONERROR);
				break;
			}
		}
	}
	if (m_askedForStop)
		goto end_point;
	r_logger->addString(L"已进入 加载页面");

	r_logger->addString(L"等待结算");
	// 等待结束。
	rect = { 640, 35, 320, 70 }; // 640 -> 960, 140 ( 35 -> 105 )
	if (!step_waitFor(true, m_result, rect, seconds(5 * 60.0f), 25)) {
		r_logger->addString(L" ");
		r_logger->addString(L"任务出错: 挑战超时");
		m_askedForStop = true;
		MessageBoxW(NULL, L"挑战超时", L"DOAXVV-helper: Task Error", MB_ICONERROR);
	}
	if (m_askedForStop)
		goto end_point;
	r_logger->addString(L"已进入 结算页面");

	r_logger->addString(L"正在退出 结算");
	// 点击，直到进入加载画面。
	pt = cv::Point(rect.x + 100, rect.y);
	rect = { 0, 0, 300, 180 }; // 300, 180
	if (!keepClickingUntil(
		pt,
		rect,
		m_loading,
		60,
		seconds(0.1f),
		20
	)) {
		r_logger->addString(L" ");
		r_logger->addString(L"任务出错: 退出结算超时");
		m_askedForStop = true;
		MessageBoxW(NULL, L"退出结算超时", L"DOAXVV-helper: Task Error", MB_ICONERROR);
	}
	if (m_askedForStop)
		goto end_point;
	r_logger->addString(L"已退出 结算");

	r_logger->addString(L"正在退出 挑战");
	rect = { 640, 80, 320, 190 }; // 640 -> 960, 80 -> 270
	if (!step_waitFor(true, m_default, rect, seconds(60.0f))) {
		r_logger->addString(L" ");
		r_logger->addString(L"任务出错: 退出挑战超时");
		m_askedForStop = true;
		MessageBoxW(NULL, L"退出挑战超时", L"DOAXVV-helper: Task Error", MB_ICONERROR);
	}
	if (m_askedForStop)
		goto end_point;
	r_logger->addString(L"已退出 挑战");

	goto begin_point;

	r_logger->addString(L"结束任务: 挑战赛");

end_point:
	return;
}

}
