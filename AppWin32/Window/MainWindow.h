#pragma once

#include "../framework.h"

namespace ohms {

class MainWindow {
public:
	MainWindow();

public:
	bool create(int nShowCmd = SW_NORMAL);
	void destroy();
	bool available() const;

protected:
	HWND m_hwnd;
};

} // namespace ohms
