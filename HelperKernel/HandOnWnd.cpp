#include "HandOnWnd.h"

namespace HelperKernel {

HandOnWnd::HandOnWnd() :
	m_hwnd(NULL),
	m_screenSize(),
	m_lastMousePoint(),
	m_workArea(),
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

bool HandOnWnd::SetUserCursorInterceptionEnabled(bool enabled) {
	if (enabled) {
		if (!GetUserCursorInterceptionEnabled() && !TryHook())
			return false;// IHelper::instance()->GuiLogF(ReturnMsgEnum::HookFailed);
	}
	else {
		if (GetUserCursorInterceptionEnabled())
			DropHook();
	}
	return true;
}

bool HandOnWnd::GetUserCursorInterceptionEnabled() {
	return NULL != m_hhook;
}

void HandOnWnd::Reset() {
	DropHook();
	m_hwnd = NULL;
}

bool HandOnWnd::SetOnWnd(HWND hwnd) {
	Reset();
	if (m_hwnd == NULL)
		return false;
	m_hwnd = hwnd;
	return true;
}

bool HandOnWnd::InitHookMod() {
	m_hmod = LoadLibraryW(L"HookDll.dll");
	if (m_hmod == NULL) {
		//CoreLog() << "Failed to Load Lobrary: " << ParseWin32Error() << std::endl;
		return false;
	}

	m_hookproc = GetProcAddress(m_hmod, "DdoaHookProc");
	if (m_hookproc == NULL) {
		//CoreLog() << "Failed to Get Procedure Address: " << ParseWin32Error() << std::endl;
		DropHookMod();
		return false;
	}
	return true;
}

bool HandOnWnd::TryHook() {
	if (!IsOperating()) return false;

	if (!InitHookMod()) {
		return false;
	}

	DWORD pid = NULL;
	DWORD tid = GetWindowThreadProcessId(m_hwnd, &pid);
	if (tid == 0) {
		//CoreLog() << "Failed to Get Thread Id: " << ParseWin32Error() << std::endl;
		return false;
	}

	m_hhook = SetWindowsHookExA(
		WH_GETMESSAGE,
		(HOOKPROC)m_hookproc,
		m_hmod,
		tid
	);
	if (m_hhook == NULL) {
		//CoreLog() << "Failed to Set Hook: " << ParseWin32Error() << std::endl;
		return false;
	}
	return true;
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
