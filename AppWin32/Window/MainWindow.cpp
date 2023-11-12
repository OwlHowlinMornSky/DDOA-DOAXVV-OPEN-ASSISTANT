#include "MainWindow.h"

#include <vector>

#include <opencv2/opencv.hpp>

#include "WndEnumeration.h"
#include "macro.h"
#include "Global.h"

namespace {

HFONT hFont;
HWND hComboBoxHwnd;
HWND hButtonRf;
HWND hButtonStop;
HWND hButtonSample;
HWND hButtonBigger;
HWND hButtonSmaller;
HWND hButtonSave;
HWND hButtonSaveC3;
HWND hButtonSwitchClient;
std::vector<ohms::WindowInfo> g_windows;

bool isSample = false;
bool isClient = true;
int scale = 100;
LONG_PTR nowPlay = -1;
size_t saveCount = 0;


void refreshCombox() {
	g_windows.clear();
	ohms::EnumerateWindows(g_windows);

	SendMessageW(hComboBoxHwnd, CB_RESETCONTENT, 0, 0);

	for (std::vector<ohms::WindowInfo>::iterator i = g_windows.begin(), n = g_windows.end(); i != n; ++i) {
		if (i->getHWnd() == ohms::global::hMain) {
			g_windows.erase(i);
			break;
		}
	}

	// Populate combo box
	for (const ohms::WindowInfo& window : g_windows) {
		SendMessageW(hComboBoxHwnd, CB_ADDSTRING, 0, (LPARAM)window.getTitle().c_str());
	}
}


void stopCapture(bool special = false) {
	nowPlay = -1;
	ohms::global::g_app->Stop();

	if (!special)
		SendMessageW(hComboBoxHwnd, CB_SETCURSEL, -1, 0);

	cv::destroyAllWindows();

	if (!special)
		InvalidateRect(ohms::global::hMain, NULL, true);
}

LRESULT CALLBACK WndProc(
	HWND   hwnd,
	UINT   msg,
	WPARAM wParam,
	LPARAM lParam) {
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

		// Create combo box
		hComboBoxHwnd = CreateWindowW(
			WC_COMBOBOXW, L"",
			CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_VSCROLL | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
			150, 10, 600, 300,
			hwnd, NULL, ohms::global::hInst, NULL);
		SendMessageW(hComboBoxHwnd, WM_SETFONT, (WPARAM)hFont, TRUE);

		hButtonRf = CreateWindowW(
			WC_BUTTONW, L"Refresh",
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
			10, 10, 100, 40,
			hwnd, NULL, ohms::global::hInst, NULL);
		SendMessageW(hButtonRf, WM_SETFONT, (WPARAM)hFont, TRUE);

		hButtonStop = CreateWindowW(
			WC_BUTTONW, L"Stop",
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
			10, 70, 100, 40,
			hwnd, NULL, ohms::global::hInst, NULL);
		SendMessageW(hButtonStop, WM_SETFONT, (WPARAM)hFont, TRUE);

		hButtonSample = CreateWindowW(
			WC_BUTTONW, L"Decimation",
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
			10, 130, 100, 40,
			hwnd, NULL, ohms::global::hInst, NULL);
		SendMessageW(hButtonSample, WM_SETFONT, (WPARAM)hFont, TRUE);

		hButtonSwitchClient = CreateWindowW(
			WC_BUTTONW, L"Switch Client",
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
			10, 190, 100, 40,
			hwnd, NULL, ohms::global::hInst, NULL);
		SendMessageW(hButtonSwitchClient, WM_SETFONT, (WPARAM)hFont, TRUE);

		hButtonBigger = CreateWindowW(
			WC_BUTTONW, L"Scale +",
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
			10, 250, 100, 40,
			hwnd, NULL, ohms::global::hInst, NULL);
		SendMessageW(hButtonBigger, WM_SETFONT, (WPARAM)hFont, TRUE);

		hButtonSmaller = CreateWindowW(
			WC_BUTTONW, L"Scale -",
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
			10, 310, 100, 40,
			hwnd, NULL, ohms::global::hInst, NULL);
		SendMessageW(hButtonSmaller, WM_SETFONT, (WPARAM)hFont, TRUE);

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

		SendMessageW(hwnd, WM_OHMS_REFRESH_COMBOX, 0, 0);
		break;
	}

	case WM_DESTROY:
	{
		DestroyWindow(hButtonSwitchClient);
		DestroyWindow(hButtonSaveC3);
		DestroyWindow(hButtonSave);
		DestroyWindow(hButtonSmaller);
		DestroyWindow(hButtonBigger);
		DestroyWindow(hButtonSample);
		DestroyWindow(hButtonStop);
		DestroyWindow(hButtonRf);
		DestroyWindow(hComboBoxHwnd);
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

		swprintf_s(str, 1024, (nowPlay != -1) ? L"Running" : L"Stopped");
		rect = { 120, 80, 220, 120 };
		DrawTextW(hdc, str, -1, &rect, DT_LEFT | DT_TOP | DT_WORDBREAK | DT_NOCLIP | DT_CALCRECT);
		//Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
		DrawTextW(hdc, str, -1, &rect, DT_LEFT | DT_TOP | DT_WORDBREAK);

		swprintf_s(str, 1024, isSample ? L"Now:\nDecimation" : L"Now:\nNormal");
		rect = { 120, 130, 220, 180 };
		DrawTextW(hdc, str, -1, &rect, DT_LEFT | DT_TOP | DT_WORDBREAK | DT_NOCLIP | DT_CALCRECT);
		//Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
		DrawTextW(hdc, str, -1, &rect, DT_LEFT | DT_TOP | DT_WORDBREAK);

		swprintf_s(str, 1024, isClient ? L"Now:\nClient" : L"Now:\nWindow");
		rect = { 120, 190, 220, 280 };
		DrawTextW(hdc, str, -1, &rect, DT_LEFT | DT_TOP | DT_WORDBREAK | DT_NOCLIP | DT_CALCRECT);
		//Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
		DrawTextW(hdc, str, -1, &rect, DT_LEFT | DT_TOP | DT_WORDBREAK);

		swprintf_s(str, 1024, L"Scale: %d %%", scale * (isSample ? 10 : 1));
		rect = { 120, 290, 220, 500 };
		DrawTextW(hdc, str, -1, &rect, DT_LEFT | DT_TOP | DT_WORDBREAK | DT_NOCLIP | DT_CALCRECT);
		//Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
		DrawTextW(hdc, str, -1, &rect, DT_LEFT | DT_TOP | DT_WORDBREAK);

		rect = { 230, 80, 750, 500 };
		Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
		if (nowPlay != -1) {
			swprintf_s(str, 1024, L"Class:\n%s\n\nTitle:\n%s",
					   g_windows[nowPlay].getClassName().c_str(),
					   g_windows[nowPlay].getTitle().c_str());
		}
		else {
			swprintf_s(str, 1024, L"Class:\n\n\nTitle:\n");
		}
		DrawTextW(hdc, str, -1, &rect, DT_LEFT | DT_TOP | DT_WORDBREAK | DT_NOPREFIX | DT_NOCLIP | DT_WORD_ELLIPSIS);

		SelectObject(hdc, hOldFont);
		EndPaint(hwnd, &ps);

		break;
	}

	case WM_CLOSE:
		SendMessageW(hwnd, WM_OHMS_STOP_CAPTURE, 0, 0);
		PostQuitMessage(0);
		break;

	case WM_COMMAND:
		switch (HIWORD(wParam)) {
		case CBN_SELCHANGE:
		{
			const LRESULT index = SendMessageW((HWND)lParam, CB_GETCURSEL, 0, 0);

			if (nowPlay == index)
				break;

			stopCapture(true);

			HWND dst = g_windows.at(index).getHWnd();

			if (IsWindow(dst)) {
				if (!IsIconic(dst)) {
					if (ohms::global::g_app->StartCapture(dst)) {
						ohms::global::g_app->setDecimationMode(isSample);
						ohms::global::g_app->setShowScale(scale);

						nowPlay = index;
					}
					else {
						stopCapture();
						MessageBoxW(hwnd, L"This window cannot be captured.", L"ERROR", MB_ICONERROR);
					}
				}
				else {
					stopCapture();
					MessageBoxW(hwnd, L"Please restore minimized window before capture.", L"WARNING", MB_ICONWARNING);
				}
			}
			else {
				stopCapture();
				SendMessageW(hwnd, WM_OHMS_REFRESH_COMBOX, 0, 0);
			}

			InvalidateRect(hwnd, NULL, true);

			break;
		}
		case BN_CLICKED:
		{

			if ((HWND)lParam == hButtonRf) {
				SendMessageW(hwnd, WM_OHMS_STOP_CAPTURE, 0, 0);
				SendMessageW(hwnd, WM_OHMS_REFRESH_COMBOX, 0, 0);
			}
			else if ((HWND)lParam == hButtonStop) {
				SendMessageW(hwnd, WM_OHMS_STOP_CAPTURE, 0, 0);
			}
			else if ((HWND)lParam == hButtonSample) {
				isSample = !isSample;
				ohms::global::g_app->setDecimationMode(isSample);
				SetWindowTextW(hButtonSample, isSample ? L"Normal" : L"Decimation");
				InvalidateRect(hwnd, NULL, true);
			}
			else if ((HWND)lParam == hButtonBigger) {
				if (scale < 200)
					scale += 10;
				ohms::global::g_app->setShowScale(scale);
				InvalidateRect(hwnd, NULL, true);
			}
			else if ((HWND)lParam == hButtonSmaller) {
				if (scale > 10)
					scale -= 10;
				ohms::global::g_app->setShowScale(scale);
				InvalidateRect(hwnd, NULL, true);
			}
			else if ((HWND)lParam == hButtonSave) {
				if (nowPlay == -1) {
					MessageBoxW(hwnd, L"Please choose a window before save image.", L"ERROR", MB_ICONERROR);
				}
				else {
					if (!ohms::global::g_app->saveNow(false, saveCount++)) {
						MessageBoxW(hwnd, L"Failed saving.", L"ERROR", MB_ICONERROR);
					}
				}
			}
			else if ((HWND)lParam == hButtonSaveC3) {
				if (nowPlay == -1) {
					MessageBoxW(hwnd, L"Please choose a window before save image.", L"ERROR", MB_ICONERROR);
				}
				else {
					if (!ohms::global::g_app->saveNow(true, saveCount++)) {
						MessageBoxW(hwnd, L"Failed saving.", L"ERROR", MB_ICONERROR);
					}
				}
			}
			else if ((HWND)lParam == hButtonSwitchClient) {
				isClient = !isClient;
				ohms::global::g_app->setClipClientArea(isClient);
				InvalidateRect(hwnd, NULL, true);
			}
			break;
		}
		default:
			break;
		}
		break;

	case WM_TIMER:
		ohms::global::g_app->setNeedRefresh();
		break;

	case WM_OHMS_REFRESH_COMBOX:
		refreshCombox();
		break;

	case WM_OHMS_STOP_CAPTURE:
		stopCapture();
		break;

	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
		break;
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
	wcex.lpszClassName = L"CaptureWithOpenCV";
	wcex.hIconSm = LoadIconW(wcex.hInstance, IDI_APPLICATION);
	auto res = RegisterClassExW(&wcex);

	if (res != 0)
		g_classRegistered = true;
	return g_classRegistered;
}

} // namespace

namespace ohms {

MainWindow::MainWindow() :
	m_hwnd(NULL)
{}

bool ohms::MainWindow::create(int nShowCmd) {
	if (!::registerClass())
		return false;

	m_hwnd = CreateWindowW(
		L"CaptureWithOpenCV",
		L"CaptureWithOpenCV",
		WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
		NULL, NULL, ohms::global::hInst, NULL);

	if (m_hwnd == NULL)
		return false;

	ohms::global::hMain = m_hwnd;

	ShowWindow(m_hwnd, nShowCmd);
	UpdateWindow(m_hwnd);



	//SetTimer(hMain, 1, 300, NULL);
	SetTimer(m_hwnd, 1, 60, NULL);

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
