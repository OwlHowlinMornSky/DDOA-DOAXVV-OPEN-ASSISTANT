#include "MainWindow.h"

#include <vector>

#include <opencv2/opencv.hpp>

#include "../Global.h"

namespace {

const WCHAR g_clsName[] = L"OHMS.DOAXVVHELPER.WNDCLS.MAIN";
const WCHAR g_wndName[] = L"DOAXVV-helper";

constexpr int g_timer{ 1 };

} // namespace

namespace ohms {

MainWindow::MainWindow() :
	hButtonSave(NULL),
	hButtonSaveC3(NULL),
	hButtonStart(NULL),
	hButtonStop(NULL),
	hFont(NULL) {}

MainWindow::~MainWindow() {}

bool MainWindow::create(int nShowCmd) noexcept {
	Window::create(nShowCmd);
	SetWindowTextW(m_hwnd, g_wndName);
	SetTimer(m_hwnd, g_timer, 33, NULL);
	return false;
}

void MainWindow::destroy() noexcept {
	KillTimer(m_hwnd, g_timer);
	return Window::destroy();
}

LRESULT MainWindow::procedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) noexcept {
	switch (msg) {
	case WM_CREATE:
	{
		hFont = CreateFontW(0, 0, 0, 0, FW_DONTCARE,
							FALSE, FALSE, FALSE,
							GB2312_CHARSET,
							OUT_DEFAULT_PRECIS,
							CLIP_DEFAULT_PRECIS,
							CLEARTYPE_QUALITY,
							DEFAULT_PITCH | FF_DONTCARE,
							L"Segoe UI");

		hButtonStart = CreateWindowW(
			WC_BUTTONW, L"Start",
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
			10, 10, 100, 40,
			hwnd, NULL, ohms::global::hInst, NULL);
		SendMessageW(hButtonStart, WM_SETFONT, (WPARAM)hFont, TRUE);

		hButtonStop = CreateWindowW(
			WC_BUTTONW, L"Stop",
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
			10, 70, 100, 40,
			hwnd, NULL, ohms::global::hInst, NULL);
		SendMessageW(hButtonStop, WM_SETFONT, (WPARAM)hFont, TRUE);

		hButtonSaveC3 = CreateWindowW(
			WC_BUTTONW, L"Save BGR",
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
			10, 370, 100, 40,
			hwnd, NULL, ohms::global::hInst, NULL);
		SendMessageW(hButtonSaveC3, WM_SETFONT, (WPARAM)hFont, TRUE);

		hButtonSave = CreateWindowW(
			WC_BUTTONW, L"Save BGRA",
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
			10, 430, 100, 40,
			hwnd, NULL, ohms::global::hInst, NULL);
		SendMessageW(hButtonSave, WM_SETFONT, (WPARAM)hFont, TRUE);

		setBtnEnabled_stop(false);
		break;
	}

	case WM_DESTROY:
	{
		DestroyWindow(hButtonSaveC3);
		DestroyWindow(hButtonSave);
		DestroyWindow(hButtonStop);
		DestroyWindow(hButtonStart);
		DeleteObject(hFont);
		break;
	}

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		SetBkMode(hdc, TRANSPARENT);

		HGDIOBJ hOldFont = SelectObject(hdc, hFont);

		RECT rect = { 10, 130, 220, 120 };
		if (running) {
			constexpr WCHAR str[] = L"Running";
			DrawTextW(hdc, str, -1, &rect, DT_LEFT | DT_TOP | DT_WORDBREAK | DT_NOCLIP | DT_CALCRECT);
			DrawTextW(hdc, str, -1, &rect, DT_LEFT | DT_TOP | DT_WORDBREAK);
		}
		else {
			constexpr WCHAR str[] = L"Stopped";
			DrawTextW(hdc, str, -1, &rect, DT_LEFT | DT_TOP | DT_WORDBREAK | DT_NOCLIP | DT_CALCRECT);
			DrawTextW(hdc, str, -1, &rect, DT_LEFT | DT_TOP | DT_WORDBREAK);
		}

		SelectObject(hdc, hOldFont);
		EndPaint(hwnd, &ps);
		break;
	}

	case WM_CLOSE:
		stop();
		PostQuitMessage(0);
		break;

	case WM_COMMAND:
		switch (HIWORD(wp)) {
		case BN_CLICKED:
		{
			if ((HWND)lp == hButtonStart) {
				start();
			}
			else if ((HWND)lp == hButtonStop) {
				stop();
			}
			else if ((HWND)lp == hButtonSave) {
				if (!ohms::global::capture->saveMat(false, saveCount++)) {
					MessageBoxW(hwnd, L"Failed to save.", L"ERROR", MB_ICONERROR);
				}
			}
			else if ((HWND)lp == hButtonSaveC3) {
				if (!ohms::global::capture->saveMat(true, saveCount++)) {
					MessageBoxW(hwnd, L"Failed to save.", L"ERROR", MB_ICONERROR);
				}
			}
			break;
		}
		default:
			return DefWindowProcW(hwnd, msg, wp, lp);
		}
		break;

	case WM_TIMER:
		if (wp == g_timer) {
			update();
		}
		break;

	default:
		return DefWindowProc(hwnd, msg, wp, lp);
	}
	return 0;
}

bool MainWindow::start() {
	ohms::global::helper->start();
	setBtnEnabled_start(false);

	

	stop();

	HWND dst = FindWindowW(L"DOAX VenusVacation", L"DOAX VenusVacation");

	if (dst == NULL) {
		MessageBoxW(NULL, L"Cannot find DOAXVV window.", L"ERROR", MB_ICONERROR);
		return false;
	}
	if (!IsWindow(dst)) {
		MessageBoxW(NULL, L"Target is not a widnow.", L"ERROR", MB_ICONERROR);
		return false;
	}
	if (IsIconic(dst)) {
		MessageBoxW(NULL, L"Target is minimized.", L"ERROR", MB_ICONERROR);
		return false;
	}
	if (!ohms::global::capture->startCapture(dst)) {
		MessageBoxW(NULL, L"Target cannot be captured.", L"ERROR", MB_ICONERROR);
		return false;
	}
	running = true;
	InvalidateRect(m_hwnd, NULL, true);
	return true;
}

void MainWindow::stop() {
	ohms::global::helper->stop();



	running = false;
	ohms::global::capture->stopCapture();
	cv::destroyAllWindows();
	InvalidateRect(m_hwnd, NULL, true);
	return;
}

void MainWindow::update() {
	auto res = ohms::global::helper->update();
	switch (res) {

	}

	if (ohms::global::capture->isRefreshed()) {
		auto mat = ohms::global::capture->getMat();
		if (mat != nullptr) {
			cv::imshow("show", *mat);
		}
	}
	ohms::global::capture->askForRefresh();
	return;
}

void MainWindow::setBtnEnabled_start(bool enabled) {}

void MainWindow::setBtnEnabled_stop(bool enabled) {}

} // namespace ohms
