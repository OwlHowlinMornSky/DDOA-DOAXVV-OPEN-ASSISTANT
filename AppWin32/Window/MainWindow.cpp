﻿#include "MainWindow.h"

#include <vector>

#include <opencv2/opencv.hpp>

#include "../Global.h"

#include <iostream>

namespace {

const WCHAR g_clsName[] = L"OHMS.DOAXVVHELPER.WNDCLS.MAIN";
const WCHAR g_wndName[] = L"DOAXVV-helper";

constexpr int g_timer{ 1 };

} // namespace

namespace ohms {

MainWindow::MainWindow() :
	m_saveCount(0),
	m_isStart(true),
	m_hButtonSave(NULL),
	m_hButtonSaveC3(NULL),
	m_hBtn(NULL),
	m_hFont(NULL) {}

MainWindow::~MainWindow() {}

bool MainWindow::create(int nShowCmd) noexcept {
	Window::create(nShowCmd);
	SetWindowTextW(m_hwnd, g_wndName);
	SetTimer(m_hwnd, g_timer, 33, NULL);
	return false;
}

void MainWindow::destroy() noexcept {
	KillTimer(m_hwnd, g_timer);
	ohms::global::helper->askForStop();
	while (ohms::global::helper->isRunning()) {
		Sleep(10);
	}
	return Window::destroy();
}

LRESULT MainWindow::procedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) noexcept {
	switch (msg) {
	case WM_CREATE:
	{
		m_hFont = CreateFontW(0, 0, 0, 0, FW_DONTCARE,
							FALSE, FALSE, FALSE,
							GB2312_CHARSET,
							OUT_DEFAULT_PRECIS,
							CLIP_DEFAULT_PRECIS,
							CLEARTYPE_QUALITY,
							DEFAULT_PITCH | FF_DONTCARE,
							L"Segoe UI");

		m_hBtn = CreateWindowW(
			WC_BUTTONW, L"Start",
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
			10, 10, 100, 40,
			hwnd, NULL, ohms::global::hInst, NULL);
		SendMessageW(m_hBtn, WM_SETFONT, (WPARAM)m_hFont, TRUE);

		m_hButtonSaveC3 = CreateWindowW(
			WC_BUTTONW, L"Save BGR",
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
			10, 370, 100, 40,
			hwnd, NULL, ohms::global::hInst, NULL);
		SendMessageW(m_hButtonSaveC3, WM_SETFONT, (WPARAM)m_hFont, TRUE);

		m_hButtonSave = CreateWindowW(
			WC_BUTTONW, L"Save BGRA",
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
			10, 430, 100, 40,
			hwnd, NULL, ohms::global::hInst, NULL);
		SendMessageW(m_hButtonSave, WM_SETFONT, (WPARAM)m_hFont, TRUE);
		break;
	}

	case WM_DESTROY:
	{
		DestroyWindow(m_hButtonSaveC3);
		DestroyWindow(m_hButtonSave);
		DestroyWindow(m_hBtn);
		DeleteObject(m_hFont);
		break;
	}

	/*case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		//SetBkMode(hdc, TRANSPARENT);

		//HGDIOBJ hOldFont = SelectObject(hdc, m_hFont);

		//SelectObject(hdc, hOldFont);
		EndPaint(hwnd, &ps);
		break;
	}*/

	case WM_CLOSE:
		stop();
		PostQuitMessage(0);
		break;

	case WM_COMMAND:
		switch (HIWORD(wp)) {
		case BN_CLICKED:
		{
			if ((HWND)lp == m_hBtn) {
				if (m_isStart)
					start();
				else
					stop();
			}
			else if ((HWND)lp == m_hButtonSave) {
				if (!ohms::global::capture->saveMat(false, m_saveCount++)) {
					MessageBoxW(hwnd, L"Failed to save.", L"ERROR", MB_ICONERROR);
				}
			}
			else if ((HWND)lp == m_hButtonSaveC3) {
				if (!ohms::global::capture->saveMat(true, m_saveCount++)) {
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
		if (wp == g_timer)
			update();
		break;

	default:
		return DefWindowProc(hwnd, msg, wp, lp);
	}
	return 0;
}

void MainWindow::start() {
	HWND dst = FindWindowW(L"DOAX VenusVacation", L"DOAX VenusVacation Launcher");
	if (dst == NULL) {
		printf_s("Cannot find DOAXVV window.\n");
		return;
	}
	if (!IsWindow(dst)) {
		printf_s("Target is not a widnow.\n");
		return;
	}
	if (IsIconic(dst)) {
		printf_s("Target is minimized.\n");
		return;
	}
	if (!ohms::global::capture->startCapture(dst)) {
		printf_s("Target cannot be captured.\n");
		return;
	}
	if (!ohms::global::helper->start()) {
		std::cout << "Start Failed!" << std::endl;
		ohms::global::capture->stopCapture();
		return;
	}
	setBtnEnabled(false);
	return;
}

void MainWindow::stop() {
	ohms::global::helper->askForStop();
	setBtnEnabled(false);
	return;
}

void MainWindow::update() {
	while (true) {
		ohms::HelperReturnMessage msg;
		{
			std::lock_guard lg(ohms::global::mutexHRM);
			if (ohms::global::helperReturnMessage.empty()) {
				break;
			}
			msg = ohms::global::helperReturnMessage.front();
			ohms::global::helperReturnMessage.pop();
		}
		switch (msg) {
		case HelperReturnMessage::Stopped:
			ohms::global::capture->stopCapture();
			break;
		case HelperReturnMessage::BtnToStop:
			setBtnText(L"Stop");
			setBtnEnabled(true);
			m_isStart = false;
			break;
		case HelperReturnMessage::BtnToStart:
			setBtnText(L"Start");
			setBtnEnabled(true);
			m_isStart = true;
			break;
		}
	}
	return;
}

void MainWindow::setBtnText(const WCHAR* text) {
	SetWindowTextW(m_hBtn, text);
	return;
}

void MainWindow::setBtnEnabled(bool enabled) {
}

} // namespace ohms
