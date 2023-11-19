#pragma once

#include "Window.h"

#include "../Helper/IHelper.h"
#include "Logger.h"

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

protected:
	void OnBtnMain_Clicked();
	void OnTimerUpdate();

	void BtnMain_SetText(const WCHAR* text);
	void BtnMain_SetEnabled(bool enabled);
	void BtnSettings_SetEnabled(bool enabled);

protected:
	HFONT hFont;
	HWND hBtnMain;
	bool m_btnMainIsStart;
	HWND hBtnSettingsLast;
	HWND hBtnSettingsNew;
	HWND hListLog;
	Logger m_logger;

	IHelper* r_helper;
};

} // namespace ohms
