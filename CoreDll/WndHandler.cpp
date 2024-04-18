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
#include <opencv2/opencv.hpp> // 不能移下去，因为windows头文件不能在opencv头文件之前。

#include "WndHandler.h"

#include "Clock.h"
#include "Settings.h"
#include "AskedForStop.h"
#include "TaskExceptionCode.h"

#include <ohms/WGC.h>

namespace {

const WCHAR g_findCls[] = L"DOAX VenusVacation"; // 查找doaxvv窗口的类的名字
const WCHAR g_findWnd[] = L"DOAX VenusVacation"; // 查找doaxvv窗口的名字
const WCHAR g_finGWnd[] = L"DOAX VenusVacation Launcher"; // 查找doaxvv launcher窗口的名字
const WCHAR g_finDWnd[] = L"DDOA-DEBUG"; // 查找调试窗口的名字

ohms::wgc::ICapture* r_capture = nullptr; // capture索引
ohms::WndHandler* g_wndh;

}

namespace ohms {

WndHandler::WndHandler() :
	m_hwnd(NULL),
	m_lastMousePoint(),
	m_screenSize(),
	m_state(StateValue::Idle),
	m_workArea() {}

WndHandler::~WndHandler() {
	Reset();
}

WndHandler* WndHandler::Instance(bool winrtInited) {
	if (::g_wndh == nullptr) {
		if (!wgc::ICapture::setup(winrtInited)) { // 初始化WGC
			MessageBoxW(NULL, L"Failed to setup WGC", L"DDOA", MB_ICONERROR);
			return nullptr;
		}
		::g_wndh = new WndHandler;
	}
	return ::g_wndh;
}

void WndHandler::Drop() {
	delete ::g_wndh;
	g_wndh = nullptr;
}

bool WndHandler::Update() {
	// 获取可用桌面大小
	SystemParametersInfoW(SPI_GETWORKAREA, 0, &m_workArea, 0);
	// 获取屏幕大小
	m_screenSize.x = GetSystemMetrics(SM_CXSCREEN);
	m_screenSize.y = GetSystemMetrics(SM_CYSCREEN);
	// 获取截图实例
	r_capture = ohms::wgc::ICapture::getInstance();
	return r_capture != nullptr;
}

bool WndHandler::LaucherAvailable() {
    return FindWindowW(g_findCls, g_finGWnd) != NULL; // 查找doaxvv launcher窗口
}

bool WndHandler::GameWndAvailable() {
	return FindWindowW(g_findCls, g_findWnd) != NULL; // 查找doaxvv窗口
}

WndHandler::SetReturnValue WndHandler::SetForLauncher() {
	if(Settings::WndHandler::DEFAULT.Debug_DebugHandler)
		return SetForDebugger(false);
	if (m_state == StateValue::Launcher)
		return SetReturnValue::OK;
	Reset();
	m_hwnd = FindWindowW(g_findCls, g_finGWnd); // 查找doaxvv launcher窗口
	if (m_hwnd == NULL) {
		return SetReturnValue::WndNotFound;
	}
	if (!IsWindow(m_hwnd) || IsIconic(m_hwnd) || !r_capture->startCaptureWindow(m_hwnd)) { // 这些是能截图的必要条件
		return SetReturnValue::CaptureFailed;
	}
	r_capture->setClipToClientArea(true);
	m_state = StateValue::Launcher;
	return SetReturnValue::OK;
}

WndHandler::SetReturnValue WndHandler::SetForGame() {
	if (Settings::WndHandler::DEFAULT.Debug_DebugHandler)
		return SetForDebugger(true);
	if (m_state == StateValue::Game)
		return SetReturnValue::OK;
	Reset();
	m_hwnd = FindWindowW(g_findCls, g_findWnd); // 查找doaxvv窗口
	if (m_hwnd == NULL) {
		return SetReturnValue::WndNotFound;
	}
	if (!IsWindow(m_hwnd) || IsIconic(m_hwnd) || !r_capture->startCaptureWindow(m_hwnd)) { // 这些是能截图的必要条件
		return SetReturnValue::CaptureFailed;
	}
	r_capture->setClipToClientArea(true);
	m_state = StateValue::Game;
	return SetReturnValue::OK;
}

void WndHandler::Reset() {
	m_state = StateValue::Idle;
	m_hwnd = NULL;
	if (r_capture) // 停止截图
		r_capture->stopCapture();
	return;
}

WndHandler::StateValue WndHandler::GetState() const {
	switch (m_state) {
	case StateValue::DebuggerGame:
		return StateValue::Game;
	case StateValue::DebuggerLauncher:
		return StateValue::Launcher;
	default:
		break;
	}
	return m_state;
}

int WndHandler::WaitFor(const MatchTemplate& _temp, Time _tlimit) {
	assert(m_state != StateValue::Idle);
	r_capture->askForRefresh();
	Clock clk;
	cv::Rect trect;
	while (!g_askedForStop) {
#ifdef _DEBUG
		if (CopyMat()) {
			bool matchRes = _temp.Match(m_mat);
			if (Settings::WndHandler::DEFAULT.Debug_ShowCapture) {
				if (_temp.GetIsFixed()) {
					cv::rectangle(m_mat, _temp.GetSearchRect(), matchRes ? cv::Scalar(0, 255, 0) : cv::Scalar(0, 0, 255), 2, 8, 0); // 画寻找范围框（满足阈值为绿，否则为红）
				}
				else {
					cv::rectangle(m_mat, _temp.GetSearchRect(), cv::Scalar(255, 0, 0), 2, 8, 0); // 蓝线画寻找范围框
					cv::rectangle(m_mat, _temp.GetLastMatchRect(), matchRes ? cv::Scalar(0, 255, 0) : cv::Scalar(0, 0, 255), 2, 8, 0); // 画最佳匹配框（满足阈值为绿，否则为红）
				}
				cv::resize(m_mat, m_mat, m_mat.size() / 2, 0.0, 0.0, cv::InterpolationFlags::INTER_LINEAR); // 缩小到一半
				cv::imshow("show", m_mat); // show
				cv::waitKey(1);
			}
			if (matchRes)
				break;
		}
#else
		if (CopyMat() && _temp.Match(m_mat))
			break;
#endif
		if (_tlimit > Time::Zero && clk.getElapsedTime() > _tlimit) // 应用超时
			return -1;
		Sleep(20);
	}
	if (g_askedForStop)
		throw TaskExceptionCode::UserStop; // throw 0 表示停止
	return 0;
}

int WndHandler::WaitForMultiple(std::vector<const MatchTemplate*> _temps, Time _tlimit) {
	assert(m_state != StateValue::Idle);
	r_capture->askForRefresh();
	Clock clk;
	cv::Rect trect;
	int res = -1;
	while (!g_askedForStop) {
		if (CopyMat()) {
			int c = 0;
			for (const MatchTemplate* i : _temps) {
				if (i->Match(m_mat)) {
					res = c;
					break;
				}
				c++;
			}
#ifdef _DEBUG
			if (Settings::WndHandler::DEFAULT.Debug_ShowCapture) {
				for (const MatchTemplate* i : _temps) {
					if (i->GetIsFixed()) {
						cv::rectangle(m_mat, i->GetSearchRect(), cv::Scalar(0, 0, 255), 2, 8, 0); // 画寻找范围框（红）
					}
					else {
						cv::rectangle(m_mat, i->GetSearchRect(), cv::Scalar(255, 0, 0), 2, 8, 0); // 蓝线画寻找范围框
						cv::rectangle(m_mat, i->GetLastMatchRect(), cv::Scalar(0, 0, 255), 2, 8, 0); // 画最佳匹配框（红）
					}
				}
				if (res != -1) {
					if (_temps[res]->GetIsFixed()) {
						cv::rectangle(m_mat, _temps[res]->GetSearchRect(), cv::Scalar(0, 255, 0), 2, 8, 0); // 画寻找范围框（绿）
					}
					else {
						cv::rectangle(m_mat, _temps[res]->GetSearchRect(), cv::Scalar(255, 0, 0), 2, 8, 0); // 蓝线画寻找范围框
						cv::rectangle(m_mat, _temps[res]->GetLastMatchRect(), cv::Scalar(0, 255, 0), 2, 8, 0); // 画最佳匹配框（绿）
					}
				}
				cv::resize(m_mat, m_mat, m_mat.size() / 2, 0.0, 0.0, cv::InterpolationFlags::INTER_LINEAR); // 缩小到一半
				cv::imshow("show", m_mat); // show
				cv::waitKey(1);
			}
#endif // _DEBUG
			if (res != -1)
				break;
		}
		if (_tlimit > Time::Zero && clk.getElapsedTime() > _tlimit) // 应用超时
			return -1;
		Sleep(20);
	}
	if (g_askedForStop)
		throw TaskExceptionCode::UserStop; // throw 0 表示停止
	return res;
}

bool WndHandler::ClickAt(cv::Point pt) {
	assert(m_state != StateValue::Idle);
	// 缩放到当前客户区大小
	RECT rect{ 0 };
	GetClientRect(m_hwnd, &rect);
	pt.x = pt.x * (rect.right - rect.left) / 960;
	pt.y = pt.y * (rect.bottom - rect.top) / 540;

	//MessageBoxA(0, (std::to_string(pt.x) + ", " + std::to_string(pt.y)).c_str(), "t", 0);

	if (Settings::WndHandler::DEFAULT.UseSendInput) {
		GetWindowRect(m_hwnd, &rect);

		// 把目标窗口移动到屏幕范围内
		if (rect.right > m_workArea.right)
			rect.left -= rect.right - m_workArea.right;
		if (rect.left < m_workArea.left)
			rect.left = m_workArea.left;
		if (rect.bottom > m_workArea.bottom)
			rect.top -= rect.bottom - m_workArea.bottom;
		if (rect.top < m_workArea.top)
			rect.top = m_workArea.top;
		SetWindowPos(m_hwnd, NULL, rect.left, rect.top, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOACTIVATE);

		INPUT input = {};

		// 有距离时连续移动光标
		if (!(pt.x == m_lastMousePoint.x && pt.y == m_lastMousePoint.y)) {
			int vecx = pt.x - m_lastMousePoint.x;
			int vecy = pt.y - m_lastMousePoint.y;
			float deltaLength = std::sqrtf(1.0f * vecx * vecx + vecy * vecy);
			int stepCnt = static_cast<int>(std::roundf(std::sqrtf(deltaLength) / 2.0f));
			stepCnt++;
			vecx /= stepCnt;
			vecy /= stepCnt;
			POINT tmp;
			for (int i = 1; i < stepCnt; ++i) {
				tmp = m_lastMousePoint;
				tmp.x += vecx * i;
				tmp.y += vecy * i;

				ClientToScreen(m_hwnd, &tmp);
				tmp.x = tmp.x * 65535ll / m_screenSize.x;
				tmp.y = tmp.y * 65535ll / m_screenSize.y;

				input.type = INPUT_MOUSE;
				input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
				input.mi.dx = tmp.x;
				input.mi.dy = tmp.y;
				SendInput(1, &input, sizeof(INPUT));
				Sleep(9);
			}
		}
		POINT p{ pt.x, pt.y };
		ClientToScreen(m_hwnd, &p);
		p.x = p.x * 65535ll / m_screenSize.x;
		p.y = p.y * 65535ll / m_screenSize.y;

		// 最终移动光标到目的地
		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
		input.mi.dx = p.x;
		input.mi.dy = p.y;
		SendInput(1, &input, sizeof(INPUT));
		Sleep(9);
		m_lastMousePoint = { pt.x, pt.y };

		// 点击
		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_ABSOLUTE;
		input.mi.dx = p.x;
		input.mi.dy = p.y;
		SendInput(1, &input, sizeof(INPUT));

		Sleep(60);

		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_LEFTUP | MOUSEEVENTF_ABSOLUTE;
		input.mi.dx = p.x;
		input.mi.dy = p.y;
		SendInput(1, &input, sizeof(INPUT));
	}
	else {
		PostMessageW(m_hwnd, WM_SETFOCUS, 0, 0);
		// 有距离时连续移动光标
		if (!(pt.x == m_lastMousePoint.x && pt.y == m_lastMousePoint.y)) {
			int vecx = pt.x - m_lastMousePoint.x;
			int vecy = pt.y - m_lastMousePoint.y;
			float deltaLength = std::sqrtf(1.0f * vecx * vecx + vecy * vecy);
			int stepCnt = static_cast<int>(std::roundf(std::sqrtf(deltaLength) / 2.0f));
			stepCnt++;
			vecx /= stepCnt;
			vecy /= stepCnt;
			POINT tmp;
			for (int i = 1; i < stepCnt; ++i) {
				tmp = m_lastMousePoint;
				tmp.x += vecx * i;
				tmp.y += vecy * i;
				PostMessageW(m_hwnd, WM_MOUSEMOVE, 0, MAKELPARAM(tmp.x, tmp.y));
				Sleep(9);
			}
		}
		// 最终移动光标到目的地
		PostMessageW(m_hwnd, WM_MOUSEMOVE, 0, MAKELPARAM(pt.x, pt.y));
		Sleep(9);
		m_lastMousePoint = { pt.x, pt.y };
		// 点击
		PostMessageW(m_hwnd, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(pt.x, pt.y));
		Sleep(40);
		PostMessageW(m_hwnd, WM_LBUTTONUP, 0, MAKELPARAM(pt.x, pt.y));
	}
	return true;
}

bool WndHandler::MoveMouseTo(cv::Point pt) {// 缩放到当前客户区大小
	assert(m_state != StateValue::Idle);
	RECT rect{ 0 };
	GetClientRect(m_hwnd, &rect);
	pt.x = pt.x * (rect.right - rect.left) / 960;
	pt.y = pt.y * (rect.bottom - rect.top) / 540;

	if (Settings::WndHandler::DEFAULT.UseSendInput) {
		GetWindowRect(m_hwnd, &rect);

		// 把目标窗口移动到屏幕范围内
		if (rect.right > m_workArea.right)
			rect.left -= rect.right - m_workArea.right;
		if (rect.left < m_workArea.left)
			rect.left = m_workArea.left;
		if (rect.bottom > m_workArea.bottom)
			rect.top -= rect.bottom - m_workArea.bottom;
		if (rect.top < m_workArea.top)
			rect.top = m_workArea.top;
		SetWindowPos(m_hwnd, NULL, rect.left, rect.top, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOACTIVATE);

		INPUT input = {};

		// 有距离时连续移动光标
		if (!(pt.x == m_lastMousePoint.x && pt.y == m_lastMousePoint.y)) {
			int vecx = pt.x - m_lastMousePoint.x;
			int vecy = pt.y - m_lastMousePoint.y;
			float deltaLength = std::sqrtf(1.0f * vecx * vecx + vecy * vecy);
			int stepCnt = static_cast<int>(std::roundf(std::sqrtf(deltaLength) / 2.0f));
			stepCnt++;
			vecx /= stepCnt;
			vecy /= stepCnt;
			POINT tmp;
			for (int i = 1; i < stepCnt; ++i) {
				tmp = m_lastMousePoint;
				tmp.x += vecx * i;
				tmp.y += vecy * i;

				ClientToScreen(m_hwnd, &tmp);
				tmp.x = tmp.x * 65535ll / m_screenSize.x;
				tmp.y = tmp.y * 65535ll / m_screenSize.y;

				input.type = INPUT_MOUSE;
				input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
				input.mi.dx = tmp.x;
				input.mi.dy = tmp.y;
				SendInput(1, &input, sizeof(INPUT));
				Sleep(9);
			}
		}
		POINT p{ pt.x, pt.y };
		ClientToScreen(m_hwnd, &p);
		p.x = p.x * 65535ll / m_screenSize.x;
		p.y = p.y * 65535ll / m_screenSize.y;

		// 最终移动光标到目的地
		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
		input.mi.dx = p.x;
		input.mi.dy = p.y;
		SendInput(1, &input, sizeof(INPUT));
		Sleep(9);
		m_lastMousePoint = { pt.x, pt.y };
	}
	else {
		PostMessageW(m_hwnd, WM_SETFOCUS, 0, 0);
		// 有距离时连续移动光标
		if (!(pt.x == m_lastMousePoint.x && pt.y == m_lastMousePoint.y)) {
			int vecx = pt.x - m_lastMousePoint.x;
			int vecy = pt.y - m_lastMousePoint.y;
			float deltaLength = std::sqrtf(1.0f * vecx * vecx + vecy * vecy);
			int stepCnt = static_cast<int>(std::roundf(std::sqrtf(deltaLength) / 2.0f));
			stepCnt++;
			vecx /= stepCnt;
			vecy /= stepCnt;
			POINT tmp;
			for (int i = 1; i < stepCnt; ++i) {
				tmp = m_lastMousePoint;
				tmp.x += vecx * i;
				tmp.y += vecy * i;
				PostMessageW(m_hwnd, WM_MOUSEMOVE, 0, MAKELPARAM(tmp.x, tmp.y));
				Sleep(9);
			}
		}
		// 最终移动光标到目的地
		PostMessageW(m_hwnd, WM_MOUSEMOVE, 0, MAKELPARAM(pt.x, pt.y));
		Sleep(9);
		m_lastMousePoint = { pt.x, pt.y };
	}
	return true;
}

bool WndHandler::KeepClickingUntil(const cv::Point clkPt, const MatchTemplate& _temp, Time maxTime, Time clkTime) {
	if (clkTime < milliseconds(10)) // 点击时间不能小于10毫秒（规定的）
		clkTime = milliseconds(10);
	Clock clock;
	do {
		if (maxTime > Time::Zero && clock.getElapsedTime() >= maxTime) // 应用超时
			return false;
		ClickAt(clkPt); // 点击
	} while (!g_askedForStop && (-1 == WaitFor(_temp, clkTime)));
	if (g_askedForStop)
		throw 0;
	return true;
}

bool WndHandler::KeepClickingUntilNo(const cv::Point clkPt, const MatchTemplate& _temp, Time maxTime, Time clkTime) {
	if (clkTime < milliseconds(10)) // 点击时间不能小于10毫秒（规定的）
		clkTime = milliseconds(10);
	Clock clock;
	do {
		if (maxTime > Time::Zero && clock.getElapsedTime() >= maxTime) // 应用超时
			return false;
		ClickAt(clkPt); // 点击
	} while (!g_askedForStop && (0 == WaitFor(_temp, clkTime)));
	if (g_askedForStop)
		throw 0;
	return true;
}

WndHandler::SetReturnValue WndHandler::SetForDebugger(bool isGame) {
	if (m_state == StateValue::DebuggerGame || m_state == StateValue::DebuggerLauncher) {
		m_state = isGame ? StateValue::DebuggerGame : StateValue::DebuggerLauncher;
		return SetReturnValue::OK;
	}
	Reset();
	m_hwnd = FindWindowW(NULL, g_finDWnd); // 查找调试窗口
	if (m_hwnd == NULL) {
		return SetReturnValue::WndNotFound;
	}
	if (!IsWindow(m_hwnd) || IsIconic(m_hwnd) || !r_capture->startCaptureWindow(m_hwnd)) { // 这些是能截图的必要条件
		return SetReturnValue::CaptureFailed;
	}
	r_capture->setClipToClientArea(true);
	m_state = isGame ? StateValue::DebuggerGame : StateValue::DebuggerLauncher;
	return SetReturnValue::OK;
}

bool WndHandler::CopyMat() {
	if (r_capture->isRefreshed()) { // refresh过再处理画面才有意义
		r_capture->askForRefresh();
		if (r_capture->copyMatTo(m_mat, true)) { // 要求转换为BGR
			if (m_mat.size().width != 960 || m_mat.size().height != 540) { // 确保大小满足要求
				cv::resize(
					m_mat, m_mat,
					cv::Size(960, 540),
					0.0, 0.0, cv::InterpolationFlags::INTER_LINEAR
				); // 双线性缩放
			}
			return true;
		}
	}
	return false;
}

}
