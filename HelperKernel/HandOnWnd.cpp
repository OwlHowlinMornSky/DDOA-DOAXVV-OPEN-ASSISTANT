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
	wchar_t* cstr0 = nullptr;
	if (cls != nullptr) {
		cli::array<wchar_t>^ wArray0 = cls->ToCharArray();
		int len0 = wArray0->Length;
		cstr0 = new wchar_t[len0 + 2];
		System::IntPtr pcstr0(cstr0);
		System::Runtime::InteropServices::Marshal::Copy(wArray0, 0, pcstr0, len0);
		cstr0[len0] = 0;
		cstr0[len0 + 1] = 0;
	}

	wchar_t* cstr1 = nullptr;
	if (title != nullptr) {
		cli::array<wchar_t>^ wArray1 = title->ToCharArray();
		int len1 = wArray1->Length;
		cstr1 = new wchar_t[len1 + 2];
		System::IntPtr pcstr1(cstr1);
		System::Runtime::InteropServices::Marshal::Copy(wArray1, 0, pcstr1, len1);
		cstr1[len1] = 0;
		cstr1[len1 + 1] = 0;
	}

	HWND hwnd = FindWindowW(cstr0, cstr1);
	if (hwnd == NULL) {
		return 1;
	}
	return SetOnWnd(hwnd);
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
