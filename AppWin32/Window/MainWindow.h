#pragma once

#include "Window.h"

namespace ohms {

class MainWindow :
	public Window {
public:
	MainWindow();
	virtual ~MainWindow() noexcept override;

public:
	virtual bool create(int nShowCmd = SW_NORMAL) noexcept override;
	virtual void destroy() noexcept override;
	virtual LRESULT procedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) noexcept override;

public:
	void start();
	void stop();
	void update();

	void setBtnText(const WCHAR* text);
	void setBtnEnabled(bool enabled);

protected:
	HFONT m_hFont;
	HWND m_hBtn;
	HWND m_hButtonSave;
	HWND m_hButtonSaveC3;

	bool m_isStart;
	size_t m_saveCount;
};

} // namespace ohms
