#pragma once

#include "framework.h"

namespace ohms {

class Window {
protected:
	Window();

public:
	virtual ~Window() noexcept;

public:
	bool isOpen() const noexcept;

	virtual bool create(int nShowCmd = SW_NORMAL) noexcept;
	virtual void destroy() noexcept;
	virtual LRESULT procedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) noexcept;

protected:
	HWND m_hwnd;
};

}

