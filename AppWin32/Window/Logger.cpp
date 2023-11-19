#include "Logger.h"

namespace ohms {

Logger::Logger() :
	m_tergetList(NULL) {}

void Logger::reg(HWND target) {
	m_tergetList = target;
}

void Logger::addString(std::wstring_view str) {
	// 向目标listbox添加一行
	SendMessageW(m_tergetList, LB_ADDSTRING, 0, (LPARAM)str.data());
	SendMessageW(m_tergetList, WM_VSCROLL, SB_LINEDOWN, NULL);
}

void Logger::clear() {
	SendMessageW(m_tergetList, LB_RESETCONTENT, 0, 0);
}

} // namespace ohms
