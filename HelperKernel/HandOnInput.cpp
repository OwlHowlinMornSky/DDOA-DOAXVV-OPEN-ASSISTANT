/*
*    DDOA-DOAXVV-OPEN-ASSISTANT
*
*     Copyright 2023-2025  Tyler Parret True
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
#include "HandOnInput.h"
#include <string>

namespace HelperKernel {

HandOnInput::HandOnInput() :
	m_hwnd(NULL),
	m_lastMousePoint(),
	m_virtual_hookEnabled(false) {}

HandOnInput::~HandOnInput() {
	Reset();
}

bool HandOnInput::IsOperating() {
	return NULL != m_hwnd;
}

void HandOnInput::Reset() {
	m_hwnd = NULL;
}

int HandOnInput::SetOnWnd(HWND hwnd) {
	Reset();
	if (hwnd == NULL)
		return 1;
	m_hwnd = hwnd;
	return 0;
}

int HandOnInput::SetOnWnd(System::String^ cls, System::String^ title) {
	std::wstring cstr0;
	if (cls != nullptr) {
		cli::array<wchar_t>^ wArray0 = cls->ToCharArray();
		int len0 = wArray0->Length;
		cstr0.resize(len0);
		System::IntPtr pcstr0(cstr0.data());
		System::Runtime::InteropServices::Marshal::Copy(wArray0, 0, pcstr0, len0);
	}

	std::wstring cstr1;
	if (title != nullptr) {
		cli::array<wchar_t>^ wArray1 = title->ToCharArray();
		int len1 = wArray1->Length;
		cstr1.resize(len1);
		System::IntPtr pcstr1(cstr1.data());
		System::Runtime::InteropServices::Marshal::Copy(wArray1, 0, pcstr1, len1);
	}

	HWND hwnd = FindWindowW(cstr0.c_str(), cstr1.c_str());
	if (hwnd == NULL) {
		return 1;
	}
	return SetOnWnd(hwnd);
}

void HandOnInput::MoveCursorTo(Drawing::Point target) {
	if (!IsOperating()) return;

	// 缩放到客户区大小
	RECT rect{ 0 };
	GetClientRect(m_hwnd, &rect);
	Drawing::Point pt(target.X * (rect.right - rect.left) / 960, target.Y * (rect.bottom - rect.top) / 540);

	RECT workArea = {};
	POINT screenSize = {};
	// 获取可用桌面大小
	SystemParametersInfoW(SPI_GETWORKAREA, 0, &workArea, 0);
	// 获取屏幕大小
	screenSize.x = GetSystemMetrics(SM_CXSCREEN);
	screenSize.y = GetSystemMetrics(SM_CYSCREEN);

	GetWindowRect(m_hwnd, &rect);

	// 把目标窗口移动到屏幕范围内
	if (rect.right > workArea.right)
		rect.left -= rect.right - workArea.right;
	if (rect.left < workArea.left)
		rect.left = workArea.left;
	if (rect.bottom > workArea.bottom)
		rect.top -= rect.bottom - workArea.bottom;
	if (rect.top < workArea.top)
		rect.top = workArea.top;
	SetWindowPos(m_hwnd, NULL, rect.left, rect.top, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOACTIVATE);

	INPUT input = {};

	// 有距离时连续移动光标
	if (pt != m_lastMousePoint) {
		int vecx = pt.X - m_lastMousePoint.X;
		int vecy = pt.Y - m_lastMousePoint.Y;
		float deltaLength = System::MathF::Sqrt(1.0f * vecx * vecx + vecy * vecy);
		int stepCnt = (int)System::MathF::Round(System::MathF::Sqrt(deltaLength) / 2.0f) + 1;
		vecx /= stepCnt;
		vecy /= stepCnt;
		for (int i = 1; i < stepCnt; ++i) {
			int tmpx = m_lastMousePoint.X + vecx * i;
			int tmpy = m_lastMousePoint.Y + vecy * i;

			POINT tmp{};
			ClientToScreen(m_hwnd, &tmp);
			tmp.x = tmp.x * 65535ll / screenSize.x;
			tmp.y = tmp.y * 65535ll / screenSize.y;

			input.type = INPUT_MOUSE;
			input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
			input.mi.dx = tmp.x;
			input.mi.dy = tmp.y;
			SendInput(1, &input, sizeof(INPUT));
			Threading::Thread::Sleep(10);
		}
	}
	POINT p{ pt.X, pt.Y };
	ClientToScreen(m_hwnd, &p);
	p.x = p.x * 65535ll / screenSize.x;
	p.y = p.y * 65535ll / screenSize.y;

	// 最终移动光标到目的地
	input.type = INPUT_MOUSE;
	input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
	input.mi.dx = p.x;
	input.mi.dy = p.y;
	SendInput(1, &input, sizeof(INPUT));
	Threading::Thread::Sleep(10);
	m_lastMousePoint = pt;

	Threading::Thread::Sleep(10);
}

void HandOnInput::MoveMouseWheel(bool isDown, unsigned int cnt) {
	if (!IsOperating()) return;

	RECT workArea = {};
	POINT screenSize = {};
	// 获取可用桌面大小
	SystemParametersInfoW(SPI_GETWORKAREA, 0, &workArea, 0);
	// 获取屏幕大小
	screenSize.x = GetSystemMetrics(SM_CXSCREEN);
	screenSize.y = GetSystemMetrics(SM_CYSCREEN);

	RECT rect{ 0 };
	GetWindowRect(m_hwnd, &rect);

	// 把目标窗口移动到屏幕范围内
	if (rect.right > workArea.right)
		rect.left -= rect.right - workArea.right;
	if (rect.left < workArea.left)
		rect.left = workArea.left;
	if (rect.bottom > workArea.bottom)
		rect.top -= rect.bottom - workArea.bottom;
	if (rect.top < workArea.top)
		rect.top = workArea.top;
	SetWindowPos(m_hwnd, NULL, rect.left, rect.top, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOACTIVATE);

	INPUT input = {};
	input.type = INPUT_MOUSE;
	input.mi.dwFlags = MOUSEEVENTF_WHEEL | MOUSEEVENTF_ABSOLUTE;
	input.mi.mouseData = isDown ? -WHEEL_DELTA : WHEEL_DELTA;
	input.mi.dx = m_lastMousePoint.X * 65535ll / screenSize.x;
	input.mi.dy = m_lastMousePoint.Y * 65535ll / screenSize.y;

	while (cnt-- > 0) {
		SendInput(1, &input, sizeof(INPUT));
		Threading::Thread::Sleep(320);
	}

	return;
}

Drawing::Point HandOnInput::GetCursorPosition() {
	return m_lastMousePoint;
}

void HandOnInput::ClickAt(Drawing::Point target) {
	if (!IsOperating()) return;

	// 缩放到当前客户区大小
	RECT rect{ 0 };
	GetClientRect(m_hwnd, &rect);
	Drawing::Point pt(target.X * (rect.right - rect.left) / 960, target.Y * (rect.bottom - rect.top) / 540);

	RECT workArea = {};
	POINT screenSize = {};
	// 获取可用桌面大小
	SystemParametersInfoW(SPI_GETWORKAREA, 0, &workArea, 0);
	// 获取屏幕大小
	screenSize.x = GetSystemMetrics(SM_CXSCREEN);
	screenSize.y = GetSystemMetrics(SM_CYSCREEN);

	GetWindowRect(m_hwnd, &rect);

	// 把目标窗口移动到屏幕范围内
	if (rect.right > workArea.right)
		rect.left -= rect.right - workArea.right;
	if (rect.left < workArea.left)
		rect.left = workArea.left;
	if (rect.bottom > workArea.bottom)
		rect.top -= rect.bottom - workArea.bottom;
	if (rect.top < workArea.top)
		rect.top = workArea.top;
	SetWindowPos(m_hwnd, NULL, rect.left, rect.top, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOACTIVATE);

	INPUT input = {};

	// 有距离时连续移动光标
	if (pt != m_lastMousePoint) {
		int vecx = pt.X - m_lastMousePoint.X;
		int vecy = pt.Y - m_lastMousePoint.Y;
		float deltaLength = System::MathF::Sqrt(1.0f * vecx * vecx + vecy * vecy);
		int stepCnt = (int)System::MathF::Round(System::MathF::Sqrt(deltaLength) / 2.0f) + 1;
		vecx /= stepCnt;
		vecy /= stepCnt;
		for (int i = 1; i < stepCnt; ++i) {
			int tmpx = m_lastMousePoint.X + vecx * i;
			int tmpy = m_lastMousePoint.Y + vecy * i;

			POINT tmp{};
			ClientToScreen(m_hwnd, &tmp);
			tmp.x = tmp.x * 65535ll / screenSize.x;
			tmp.y = tmp.y * 65535ll / screenSize.y;

			input.type = INPUT_MOUSE;
			input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
			input.mi.dx = tmp.x;
			input.mi.dy = tmp.y;
			SendInput(1, &input, sizeof(INPUT));
			Threading::Thread::Sleep(10);
		}
	}
	POINT p{ pt.X, pt.Y };
	ClientToScreen(m_hwnd, &p);
	p.x = p.x * 65535ll / screenSize.x;
	p.y = p.y * 65535ll / screenSize.y;

	// 最终移动光标到目的地
	input.type = INPUT_MOUSE;
	input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
	input.mi.dx = p.x;
	input.mi.dy = p.y;
	SendInput(1, &input, sizeof(INPUT));
	m_lastMousePoint = pt;
	Threading::Thread::Sleep(10);

	// 点击
	input.type = INPUT_MOUSE;
	input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_ABSOLUTE;
	input.mi.dx = p.x;
	input.mi.dy = p.y;
	SendInput(1, &input, sizeof(INPUT));

	Threading::Thread::Sleep(60);

	input.type = INPUT_MOUSE;
	input.mi.dwFlags = MOUSEEVENTF_LEFTUP | MOUSEEVENTF_ABSOLUTE;
	input.mi.dx = p.x;
	input.mi.dy = p.y;
	SendInput(1, &input, sizeof(INPUT));

	Threading::Thread::Sleep(10);
}

int HandOnInput::SetUserCursorInterceptionEnabled(bool enabled) {
	// SendInput do not need hook.
	m_virtual_hookEnabled = enabled;
	return 0;
}

bool HandOnInput::GetUserCursorInterceptionEnabled() {
	return m_virtual_hookEnabled;
}

}
