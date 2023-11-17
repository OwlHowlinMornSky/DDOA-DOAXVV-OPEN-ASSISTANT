#pragma once

#include "framework.h"

#include <string>

namespace ohms {

class Logger final {
public:
	Logger();

public:
	void reg(HWND target);

	void addString(const WCHAR* str);

	void addString(std::wstring_view str);

	void clear();

protected:
	HWND m_tergetList;
};

}
