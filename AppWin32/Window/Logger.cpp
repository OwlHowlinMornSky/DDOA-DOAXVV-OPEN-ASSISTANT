#include "Logger.h"

#include <iostream>

ohms::Logger::Logger(HWND target) :
	m_tergetList(target) {}

void ohms::Logger::addString(const WCHAR* str) {
#ifdef _DEBUG
	std::wcout << str << std::endl;
#endif // _DEBUG
	SendMessageW(m_tergetList, LB_ADDSTRING, 0, (LPARAM)str);
	SendMessageW(m_tergetList, WM_VSCROLL, SB_LINEDOWN, NULL);
}

void ohms::Logger::addString(std::wstring_view str) {
#ifdef _DEBUG
	std::wcout << str << std::endl;
#endif // _DEBUG
	SendMessageW(m_tergetList, LB_ADDSTRING, 0, (LPARAM)str.data());
	SendMessageW(m_tergetList, WM_VSCROLL, SB_LINEDOWN, NULL);
}

void ohms::Logger::clear() {
	SendMessageW(m_tergetList, LB_RESETCONTENT, 0, 0);
}
