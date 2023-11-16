#include "Window.h"

#include <stdio.h>

namespace {

const WCHAR g_clsName[] = L"OHMS.WNDCLS.DEFAULT";

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	if (hwnd) {
		if (msg == WM_CREATE) {
			LONG_PTR window = reinterpret_cast<LONG_PTR>(reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams);
			SetWindowLongPtrW(hwnd, GWLP_USERDATA, window);

		}
		ohms::Window* window = reinterpret_cast<ohms::Window*>(GetWindowLongPtrW(hwnd, GWLP_USERDATA));
		if (window) {
			return window->procedure(hwnd, msg, wParam, lParam);
		}
	}
	return DefWindowProcW(hwnd, msg, wParam, lParam);
}

bool g_clsRegistered{ false };

bool registerClass() noexcept {
	if (g_clsRegistered)
		return true;
	WNDCLASSEX wcex{ 0 };
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.hInstance = GetModuleHandleW(NULL);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOWFRAME);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = g_clsName;
	auto res = RegisterClassExW(&wcex);
	if (res != 0)
		g_clsRegistered = true;
	return g_clsRegistered;
}

} // namespace

namespace ohms {

Window::Window() :
	m_hwnd(NULL) {
	return;
}

Window::~Window() {
	destroy();
	m_hwnd = NULL;
	return;
}

bool Window::isOpen() const noexcept {
	return m_hwnd != NULL;
}

bool Window::create(int nShowCmd) noexcept {
	if (m_hwnd != NULL || !::registerClass())
		return false;
	m_hwnd = CreateWindowExW(
		0L, g_clsName, L"",
		WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
		NULL, NULL, GetModuleHandleW(NULL), this
	);
	if (m_hwnd == NULL)
		return false;
	ShowWindow(m_hwnd, nShowCmd);
	UpdateWindow(m_hwnd);
	return true;
}

void Window::destroy() noexcept {
	DestroyWindow(m_hwnd);
	m_hwnd = NULL;
	return;
}

LRESULT Window::procedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) noexcept {
	return DefWindowProcW(hwnd, msg, wp, lp);
}

} // namespace ohms
