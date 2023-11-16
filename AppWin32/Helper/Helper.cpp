#include "Helper.h"

#include "../Global.h"

#include <thread>
#include <iostream>

namespace ohms {

Helper::Helper() :
	m_askedForStop(false),
	m_running(false) {

	m_lastFight = cv::imread("assets/lastFight.png");
	m_start = cv::imread("assets/start.png");
	m_result = cv::imread("assets/result.png");
	m_loading = cv::imread("assets/loading.png");

	return;
}

Helper::~Helper() {}

bool Helper::start() {
	if (m_running) {
		std::cout << "It is now running!" << std::endl;
		return false;
	}
	m_askedForStop = false;
	std::thread sub(&Helper::work, this);
	sub.detach();
	return !sub.joinable();
}

void Helper::askForStop() {
	m_askedForStop = true;
	return;
}

bool Helper::isRunning() {
	return m_running;
}

void Helper::work() {
	m_running = true;
	ohms::global::pushHRM(HelperReturnMessage::BtnToStop);

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

	m_running = false;
	ohms::global::pushHRM(HelperReturnMessage::Stopped);
	ohms::global::pushHRM(HelperReturnMessage::BtnToStart);
	return;
}

void Helper::subwork_fight() {
	cv::Rect rect;
	cv::Point pt;

begin_point:
	//goto debug_point;

	std::cout << "开始查找 上一次比赛" << std::endl;
	// 查找“上一次比赛”
	rect = { 600, 240, 100, 300 }; // 600 -> 700, 240 -> 540
	step_waitFor(true, m_lastFight, rect);
	if (m_askedForStop)
		goto end_point;
	std::cout << "找到 上一次比赛" << std::endl;

	std::cout << "点击 上一次比赛" << std::endl;
	// 点击上一次比赛，直到进入编队画面（找到挑战按钮）。
	pt = cv::Point(rect.x + 150, rect.y);
	rect = { 700, 470, 200, 70 }; // 700 -> 900, 470 -> 540
	keepClickingUntil(
		pt,
		rect,
		m_start
	);
	if (m_askedForStop)
		goto end_point;
	std::cout << "已进入 编队页面" << std::endl;

	std::cout << "开始查找 挑战 按钮" << std::endl;
	// 查找“挑战”按钮。
	rect = { 700, 470, 200, 70 }; // 700 -> 900, 470 -> 540
	step_waitFor(true, m_start, rect);
	if (m_askedForStop)
		goto end_point;
	std::cout << "找到 挑战 按钮" << std::endl;

	std::cout << "点击 挑战 按钮" << std::endl;
	// 点击挑战，直到进入加载画面。
	pt = cv::Point(rect.x + 50, rect.y + 20);
	rect = { 0, 0, 300, 180 }; // 300, 180
	keepClickingUntil(
		pt,
		rect,
		m_loading,
		0, 
		seconds(1.0f),
		20
	);
	if (m_askedForStop)
		goto end_point;
	std::cout << "已进入 加载页面" << std::endl;

	std::cout << "等待挑战结束" << std::endl;
	// 等待结束。
	rect = { 640, 0, 320, 140 }; // 640 -> 960, 140
	step_waitFor(true, m_result, rect, Time::Zero, 30);
	if (m_askedForStop)
		goto end_point;
	std::cout << "已进入 挑战结束页面" << std::endl;

	std::cout << "正在退出 挑战" << std::endl;
	//step_click(cv::Point(rect.x + 150, rect.y + 40));
	// 点击，直到进入加载画面。
	pt = cv::Point(rect.x + 50, rect.y + 20);
	rect = { 0, 0, 300, 180 }; // 300, 180
	keepClickingUntil(
		pt,
		rect,
		m_loading,
		0,
		seconds(0.1f),
		20
	);
	if (m_askedForStop)
		goto end_point;
	std::cout << "已退出 挑战" << std::endl;

	goto begin_point;

end_point:
	std::cout << "任务结束" << std::endl;
	cv::destroyAllWindows();
	return;
}

}
