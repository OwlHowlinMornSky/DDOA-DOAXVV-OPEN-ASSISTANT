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
#include "WndHandler.h"

#include "Clock.h"
#include "Settings.h"

namespace {

const WCHAR g_findCls[] = L"DOAX VenusVacation"; // 查找doaxvv窗口的类的名字
const WCHAR g_findWnd[] = L"DOAX VenusVacation"; // 查找doaxvv窗口的名字
const WCHAR g_finGWnd[] = L"DOAX VenusVacation Launcher"; // 查找doaxvv launcher窗口的名字

}

namespace ohms {

WndHandler::WndHandler() :
	m_hwnd(NULL),
	m_lastMousePoint(),
	m_screenSize(),
	m_state(StateValue::Idle),
	m_workArea(),
	r_capture(ohms::wgc::ICapture::getInstance())
{}

WndHandler::~WndHandler() {}

void WndHandler::Update() {
	// 获取可用桌面大小
	SystemParametersInfoW(SPI_GETWORKAREA, 0, &m_workArea, 0);
	// 获取屏幕大小
	m_screenSize.x = GetSystemMetrics(SM_CXSCREEN);
	m_screenSize.y = GetSystemMetrics(SM_CYSCREEN);
	return;
}

WndHandler::SetReturnValue WndHandler::SetForLaucher() {
	if (m_state == StateValue::Launcher)
		return SetReturnValue::OK;
	Reset();
	m_hwnd = FindWindowW(g_findCls, g_finGWnd); // 查找doaxvv launcher窗口
	if (m_hwnd == NULL) {
		return SetReturnValue::WndNotFound;
	}
	if (!IsWindow(m_hwnd) || IsIconic(m_hwnd) || !r_capture->startCapture(m_hwnd)) { // 这些是能截图的必要条件
		return SetReturnValue::CaptureFailed;
	}
	m_state = StateValue::Launcher;
	return SetReturnValue::OK;
}

WndHandler::SetReturnValue WndHandler::SetForGame() {
	if (m_state == StateValue::Game)
		return SetReturnValue::OK;
	Reset();
	m_hwnd = FindWindowW(g_findCls, g_findWnd); // 查找doaxvv窗口
	if (m_hwnd == NULL) {
		return SetReturnValue::WndNotFound;
	}
	if (!IsWindow(m_hwnd) || IsIconic(m_hwnd) || !r_capture->startCapture(m_hwnd)) { // 这些是能截图的必要条件
		return SetReturnValue::CaptureFailed;
	}
	m_state = StateValue::Game;
	return SetReturnValue::OK;
}

void WndHandler::Reset() {
	m_state = StateValue::Idle;
	m_hwnd = NULL;
	r_capture->stopCapture();
	return;
}

WndHandler::StateValue WndHandler::GetState() const {
	return m_state;
}

int WndHandler::WaitFor(const MatchTemplate& _temp, Time _tlimit) {
	r_capture->askForRefresh();
	Clock clk;
	cv::Mat mat;
	cv::Rect trect;
	MSG msg{ 0 };
	while (!Settings::g_askedForStop) {
		// show mat时必须处理该线程的窗口消息，cv的窗口才正常
		// 没有show mat时也必须处理消息，否则收不到capture到的帧（似乎是分离线程初始化wgc导致的
		if (PeekMessageW(&msg, NULL, NULL, NULL, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}
		else {
			if (CopyMat(mat) && _temp.Match(mat))
				break;
			if (_tlimit > Time::Zero && clk.getElapsedTime() > _tlimit) // 应用超时
				return -1;
			r_capture->askForRefresh();
			Sleep(30);
		}
	}
	if (Settings::g_askedForStop)
		throw 0; // throw 0 表示停止
	return 0;
}

int WndHandler::WaitForMultiple(std::vector<const MatchTemplate*> _temps, Time _tlimit) {
	r_capture->askForRefresh();
	Clock clk;
	cv::Mat mat;
	cv::Rect trect;
	MSG msg{ 0 };
	int res = -1;
	while (!Settings::g_askedForStop) {
		// show mat时必须处理该线程的窗口消息，cv的窗口才正常
		// 没有show mat时也必须处理消息，否则收不到capture到的帧（似乎是分离线程初始化wgc导致的
		if (PeekMessageW(&msg, NULL, NULL, NULL, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}
		else {
			if (CopyMat(mat)) {
				int c = 0;
				for (const MatchTemplate* i : _temps) {
					if (i->Match(mat)) {
						res = c;
						break;
					}
					c++;
				}
				if (res != -1)
					break;
			}
			if (_tlimit > Time::Zero && clk.getElapsedTime() > _tlimit) // 应用超时
				return -1;
			r_capture->askForRefresh();
			Sleep(30);
		}
	}
	if (Settings::g_askedForStop)
		throw 0; // throw 0 表示停止
	return res;
}

bool WndHandler::CopyMat(cv::Mat& target) {
	if (r_capture->isRefreshed()) { // refresh过再处理画面才有意义
		if (r_capture->copyMatTo(target, true)) { // 要求转换为BGR
			if (target.size().width != 960 || target.size().height != 540) { // 确保大小满足要求
				auto sz = target.size();
				cv::resize(
					target, target,
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
