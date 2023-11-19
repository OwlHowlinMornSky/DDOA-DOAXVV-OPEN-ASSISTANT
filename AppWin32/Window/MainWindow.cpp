#include "MainWindow.h"

#include <windowsx.h>

namespace {

const WCHAR g_clsName[] = L"OHMS.DOAXVVHELPER.WNDCLS.MAIN";
const WCHAR g_wndName[] = L"DOAXVV-helper";

constexpr int g_timer{ 1 };

} // namespace

namespace ohms {

MainWindow::MainWindow() :

	hFont(NULL),

	hBtnMain(NULL),
	m_btnMainIsStart(true),

	hBtnSettingsLast(NULL),
	hBtnSettingsNew(NULL),

	hListLog(NULL),

	r_helper(nullptr)

{}

MainWindow::~MainWindow() {
	destroy();
}

bool MainWindow::create(int nShowCmd) noexcept {
	if (m_hwnd != NULL)
		return false;

	r_helper = IHelper::instance();

	if (!Window::create(nShowCmd))
		return false;

	SetWindowTextW(m_hwnd, g_wndName);
	SetTimer(m_hwnd, g_timer, 60, NULL);
	return true;
}

void MainWindow::destroy() noexcept {
	if (m_hwnd == NULL)
		return;

	KillTimer(m_hwnd, g_timer);

	m_btnMainIsStart = false;
	OnBtnMain_Clicked();

	while (r_helper->isRunning()) {
		MSG msg{ 0 };
		if (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}
		else {
			Sleep(30);
		}
	}
	return Window::destroy();
}

LRESULT MainWindow::procedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) noexcept {
	switch (msg) {
	case WM_CREATE:
	{
		HINSTANCE hInst = GetModuleHandleW(NULL);

		hFont = CreateFontW(
			0, 0, 0, 0, FW_DONTCARE,
			FALSE, FALSE, FALSE,
			GB2312_CHARSET,
			OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,
			CLEARTYPE_QUALITY,
			DEFAULT_PITCH | FF_DONTCARE,
			L"Segoe UI"
		);

		hBtnMain = CreateWindowW(
			WC_BUTTONW, L"Start",
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
			10, 10, 100, 40,
			hwnd, NULL, hInst, NULL
		);
		SendMessageW(hBtnMain, WM_SETFONT, (WPARAM)hFont, TRUE);

		hBtnSettingsLast = CreateWindowW(
			WC_BUTTONW, L"Last Game",
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
			10, 370, 100, 40,
			hwnd, NULL, hInst, NULL
		);
		SendMessageW(hBtnSettingsLast, WM_SETFONT, (WPARAM)hFont, TRUE);

		hBtnSettingsNew = CreateWindowW(
			WC_BUTTONW, L"New Game",
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
			10, 430, 100, 40,
			hwnd, NULL, hInst, NULL
		);
		SendMessageW(hBtnSettingsNew, WM_SETFONT, (WPARAM)hFont, TRUE);

		Button_SetCheck(hBtnSettingsLast, BST_CHECKED);

		hListLog = CreateWindowW(
			WC_LISTBOXW, L"Log",
			WS_VISIBLE | WS_CHILD | WS_BORDER | LBS_HASSTRINGS | WS_VSCROLL | WS_HSCROLL,
			160, 10, 600, 500,
			hwnd, NULL, hInst, NULL
		);
		SendMessageW(hListLog, WM_SETFONT, (WPARAM)hFont, TRUE);
		m_logger.reg(hListLog);
		r_helper->regLogger(&m_logger);

		break;
	}

	case WM_DESTROY:
	{
		DestroyWindow(hListLog);
		DestroyWindow(hBtnSettingsNew);
		DestroyWindow(hBtnSettingsLast);
		DestroyWindow(hBtnMain);
		DeleteObject(hFont);
		break;
	}

	case WM_CLOSE:
		PostQuitMessage(0);
		break;

	case WM_COMMAND:
		switch (HIWORD(wp)) {
		case BN_CLICKED:
			if ((HWND)lp == hBtnMain)
				OnBtnMain_Clicked();
			break;
		default:
			return DefWindowProcW(hwnd, msg, wp, lp);
		}
		break;

	case WM_TIMER:
		if (wp == g_timer)
			OnTimerUpdate();
		break;

	default:
		return DefWindowProc(hwnd, msg, wp, lp);
	}
	return 0;
}

void MainWindow::OnBtnMain_Clicked() {
	BtnSettings_SetEnabled(false);
	BtnMain_SetEnabled(false);
	if (m_btnMainIsStart) {
		m_logger.clear();

		if (Button_GetState(hBtnSettingsLast) == BST_CHECKED)
			r_helper->regForNew(false);
		else if (Button_GetState(hBtnSettingsNew) == BST_CHECKED)
			r_helper->regForNew(true);
		else {
			m_logger.addString(L"请先设置比赛类型");
			return;
		}

		if (!r_helper->start()) {
			m_logger.addString(L"无法启动任务");
			return;
		}
	}
	else {
		r_helper->askForStop();
	}
	return;
}

void MainWindow::OnTimerUpdate() {
	ohms::HelperReturnMessage msg;
	while (r_helper->popMessage(msg)) {
		switch (msg) {
		case HelperReturnMessage::Stopped:
			m_logger.addString(L"已停止");
			BtnSettings_SetEnabled(true);
			break;
		case HelperReturnMessage::BtnToStop:
			BtnMain_SetText(L"Stop");
			BtnMain_SetEnabled(true);
			m_btnMainIsStart = false;
			break;
		case HelperReturnMessage::BtnToStart:
			BtnMain_SetText(L"Start");
			BtnMain_SetEnabled(true);
			m_btnMainIsStart = true;
			break;
		}
	}
	return;
}

void MainWindow::BtnMain_SetText(const WCHAR* text) {
	SetWindowTextW(hBtnMain, text);
	return;
}

void MainWindow::BtnMain_SetEnabled(bool enabled) {
	EnableWindow(hBtnMain, enabled ? TRUE : FALSE);
	return;
}

void MainWindow::BtnSettings_SetEnabled(bool enabled) {
	EnableWindow(hBtnSettingsLast, enabled ? TRUE : FALSE);
	EnableWindow(hBtnSettingsNew, enabled ? TRUE : FALSE);
	return;
}

} // namespace ohms
