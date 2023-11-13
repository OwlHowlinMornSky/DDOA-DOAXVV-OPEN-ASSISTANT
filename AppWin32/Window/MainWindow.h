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

	void setBtnEnabled_start(bool enabled);
	void setBtnEnabled_stop(bool enabled);

protected:
	HFONT hFont;
	HWND hButtonStart;
	HWND hButtonStop;
	HWND hButtonSave;
	HWND hButtonSaveC3;

	bool running = false;
	size_t saveCount = 0;
};

} // namespace ohms
