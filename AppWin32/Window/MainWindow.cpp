#include "MainWindow.h"

#include <vector>

#include <opencv2/opencv.hpp>

#include "Global.h"

namespace {

HFONT hFont;
HWND hMain;
HWND hButtonStart;
HWND hButtonStop;
HWND hButtonSave;
HWND hButtonSaveC3;

bool running = false;
size_t saveCount = 0;

void stopCapture(bool special = false) {
	running = false;
	ohms::global::g_app->Stop();
	cv::destroyAllWindows();
	if (!special)
		InvalidateRect(hMain, NULL, true);
	return;
}

void startCapture() {
	stopCapture(true);

	HWND dst = FindWindowW(L"DOAX VenusVacation", L"DOAX VenusVacation");

	if (dst == NULL) {
		MessageBoxW(NULL, L"Didn't find DOAXVV window.", L"ERROR", MB_ICONERROR);
		return;
	}

	if (IsWindow(dst)) {
		if (!IsIconic(dst)) {
			if (ohms::global::g_app->StartCapture(dst)) {
				running = true;
			}
			else {
				MessageBoxW(NULL, L"This window cannot be captured.", L"ERROR", MB_ICONERROR);
			}
		}
		else {
			MessageBoxW(NULL, L"Please restore minimized window before capture.", L"WARNING", MB_ICONWARNING);
		}
	}

	InvalidateRect(hMain, NULL, true);
}

LRESULT CALLBACK WndProc(
	HWND   hwnd,
	UINT   msg,
	WPARAM wParam,
	LPARAM lParam
) {
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

		WCHAR str[1024];
		RECT rect;

		swprintf_s(str, 1024, running ? L"Running" : L"Stopped");
		rect = { 120, 80, 220, 120 };
		DrawTextW(hdc, str, -1, &rect, DT_LEFT | DT_TOP | DT_WORDBREAK | DT_NOCLIP | DT_CALCRECT);
		DrawTextW(hdc, str, -1, &rect, DT_LEFT | DT_TOP | DT_WORDBREAK);

		SelectObject(hdc, hOldFont);
		EndPaint(hwnd, &ps);
		break;
	}

	case WM_CLOSE:
		stopCapture();
		PostQuitMessage(0);
		break;

	case WM_COMMAND:
		switch (HIWORD(wParam)) {
		case BN_CLICKED:
		{

			if ((HWND)lParam == hButtonStart) {
				startCapture();
			}
			else if ((HWND)lParam == hButtonStop) {
				stopCapture();
			}
			else if ((HWND)lParam == hButtonSave) {
				if (!running) {
					MessageBoxW(hwnd, L"Please choose a window before save image.", L"ERROR", MB_ICONERROR);
				}
				else {
					if (!ohms::global::g_app->saveNow(false, saveCount++)) {
						MessageBoxW(hwnd, L"Failed saving.", L"ERROR", MB_ICONERROR);
					}
				}
			}
			else if ((HWND)lParam == hButtonSaveC3) {
				if (!running) {
					MessageBoxW(hwnd, L"Please choose a window before save image.", L"ERROR", MB_ICONERROR);
				}
				else {
					if (!ohms::global::g_app->saveNow(true, saveCount++)) {
						MessageBoxW(hwnd, L"Failed saving.", L"ERROR", MB_ICONERROR);
					}
				}
			}
			break;
		}
		default:
			return DefWindowProc(hwnd, msg, wParam, lParam);
		}
		break;

	case WM_TIMER:
		if (ohms::global::g_app->getUpdated()) {
			auto mat = ohms::global::g_app->getCapMat();
			if (mat != nullptr) {
				cv::imshow("show", *mat);
			}
		}
		ohms::global::g_app->setNeedRefresh();
		break;

	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

bool g_classRegistered = false;

bool registerClass() {
	if (g_classRegistered)
		return true;
	WNDCLASSEX wcex = {};
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = ohms::global::hInst;
	wcex.hIcon = LoadIconW(ohms::global::hInst, IDI_APPLICATION);
	wcex.hCursor = LoadCursorW(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"OHMS.DOAXVVHELPER.WNDCLS";
	wcex.hIconSm = LoadIconW(wcex.hInstance, IDI_APPLICATION);
	auto res = RegisterClassExW(&wcex);

	if (res != 0)
		g_classRegistered = true;
	return g_classRegistered;
}

} // namespace

namespace ohms {

MainWindow::MainWindow() :
	m_hwnd(NULL) {}

bool ohms::MainWindow::create(int nShowCmd) {
	if (m_hwnd != NULL || hMain != NULL || !::registerClass())
		return false;

	m_hwnd = CreateWindowW(
		L"OHMS.DOAXVVHELPER.WNDCLS",
		L"DOAXVV-helper",
		WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
		NULL, NULL, ohms::global::hInst, NULL);

	if (m_hwnd == NULL)
		return false;

	hMain = m_hwnd;

	ShowWindow(m_hwnd, nShowCmd);
	UpdateWindow(m_hwnd);

	SetTimer(m_hwnd, 1, 33, NULL);
	return true;
}

void MainWindow::destroy() {
	DestroyWindow(m_hwnd);
	return;
}

bool MainWindow::available() const {
	return m_hwnd != NULL;
}

} // namespace ohms
