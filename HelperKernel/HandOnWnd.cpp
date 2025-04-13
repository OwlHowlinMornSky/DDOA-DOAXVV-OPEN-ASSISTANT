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
#include "HandOnWnd.h"
#include <string>

namespace HelperKernel {

HandOnWnd::HandOnWnd() :
	m_hwnd(NULL),
	m_lastMousePoint(),
	m_hmod(NULL),
	m_hookproc(NULL),
	m_hhook(NULL) {}

HandOnWnd::~HandOnWnd() {
	Reset();
	DropHookMod();
}

bool HandOnWnd::IsOperating() {
	return NULL != m_hwnd;
}

void HandOnWnd::Reset() {
	DropHook();
	m_hwnd = NULL;
}

int HandOnWnd::SetOnWnd(HWND hwnd) {
	Reset();
	if (hwnd == NULL)
		return 1;
	m_hwnd = hwnd;
	return 0;
}

int HandOnWnd::SetOnWnd(System::String^ cls, System::String^ title) {
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

void HandOnWnd::MoveCursorTo(Drawing::Point target) {
	if (!IsOperating()) return;

	// 缩放到客户区大小
	RECT rect{ 0 };
	GetClientRect(m_hwnd, &rect);
	Drawing::Point pt(target.X * (rect.right - rect.left) / 960, target.Y * (rect.bottom - rect.top) / 540);

	PostMessageW(m_hwnd, WM_SETFOCUS, 0, 0);
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
			PostMessageW(m_hwnd, WM_MOUSEMOVE, MK_CONTROL, MAKELPARAM(tmpx, tmpy));
			Threading::Thread::Sleep(10);
		}
	}
	// 最终移动光标到目的地
	PostMessageW(m_hwnd, WM_MOUSEMOVE, MK_CONTROL, MAKELPARAM(pt.X, pt.Y));
	m_lastMousePoint = pt;

	Threading::Thread::Sleep(20);
}

void HandOnWnd::MoveMouseWheel(bool isDown, unsigned int cnt) {
	if (!IsOperating()) return;

	if (isDown) {
		while (cnt-- > 0) {
			PostMessageW(m_hwnd, WM_MOUSEWHEEL, MAKEWPARAM(MK_CONTROL, -WHEEL_DELTA), MAKELPARAM(m_lastMousePoint.X, m_lastMousePoint.Y));
			Threading::Thread::Sleep(320);
		}
	}
	else {
		while (cnt-- > 0) {
			PostMessageW(m_hwnd, WM_MOUSEWHEEL, MAKEWPARAM(MK_CONTROL, WHEEL_DELTA), MAKELPARAM(m_lastMousePoint.X, m_lastMousePoint.Y));
			Threading::Thread::Sleep(320);
		}
	}

	return;
}

Drawing::Point HandOnWnd::GetCursorPosition() {
	return m_lastMousePoint;
}

void HandOnWnd::ClickAt(Drawing::Point target) {
	if (!IsOperating()) return;

	// 缩放到当前客户区大小
	RECT rect{ 0 };
	GetClientRect(m_hwnd, &rect);
	Drawing::Point pt(target.X * (rect.right - rect.left) / 960, target.Y * (rect.bottom - rect.top) / 540);

	PostMessageW(m_hwnd, WM_SETFOCUS, 0, 0);
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
			PostMessageW(m_hwnd, WM_MOUSEMOVE, MK_CONTROL, MAKELPARAM(tmpx, tmpy));
			Threading::Thread::Sleep(10);
		}
	}
	// 最终移动光标到目的地
	PostMessageW(m_hwnd, WM_MOUSEMOVE, MK_CONTROL, MAKELPARAM(pt.X, pt.Y));
	m_lastMousePoint = pt;
	Threading::Thread::Sleep(10);

	// 点击
	PostMessageW(m_hwnd, WM_LBUTTONDOWN, MK_LBUTTON | MK_CONTROL, MAKELPARAM(pt.X, pt.Y));
	Threading::Thread::Sleep(60);
	PostMessageW(m_hwnd, WM_LBUTTONUP, 0, MAKELPARAM(pt.X, pt.Y));

	Threading::Thread::Sleep(10);
}

int HandOnWnd::SetUserCursorInterceptionEnabled(bool enabled) {
	if (enabled) {
		if (GetUserCursorInterceptionEnabled())
			return 0;
		return TryHook();// IHelper::instance()->GuiLogF(ReturnMsgEnum::HookFailed);
	}
	else {
		if (GetUserCursorInterceptionEnabled())
			DropHook();
	}
	return 0;
}

bool HandOnWnd::GetUserCursorInterceptionEnabled() {
	return NULL != m_hhook;
}

int HandOnWnd::InitHookMod() {
	m_hmod = LoadLibraryW(L"HookDll.dll");
	if (m_hmod == NULL) {
		//CoreLog() << "Failed to Load Lobrary: " << ParseWin32Error() << std::endl;
		return 1;
	}

	m_hookproc = GetProcAddress(m_hmod, "DdoaHookProc");
	if (m_hookproc == NULL) {
		//CoreLog() << "Failed to Get Procedure Address: " << ParseWin32Error() << std::endl;
		DropHookMod();
		return 2;
	}
	return 0;
}

int HandOnWnd::TryHook() {
	if (!IsOperating()) return 1;

	if (int res = InitHookMod(); res != 0) {
		return res + 1;
	}

	DWORD pid = NULL;
	DWORD tid = GetWindowThreadProcessId(m_hwnd, &pid);
	if (tid == 0) {
		//CoreLog() << "Failed to Get Thread Id: " << ParseWin32Error() << std::endl;
		return 4;
	}

	m_hhook = SetWindowsHookExA(
		WH_GETMESSAGE,
		(HOOKPROC)m_hookproc,
		m_hmod,
		tid
	);
	if (m_hhook == NULL) {
		//CoreLog() << "Failed to Set Hook: " << ParseWin32Error() << std::endl;
		return 5;
	}
	return 0;
}

void HandOnWnd::DropHook() {
	if (m_hhook != NULL)
		UnhookWindowsHookEx(m_hhook);
	m_hhook = NULL;
}

void HandOnWnd::DropHookMod() {
	m_hookproc = NULL;
	if (m_hmod != NULL)
		FreeLibrary(m_hmod);
	m_hmod = NULL;
}

}
