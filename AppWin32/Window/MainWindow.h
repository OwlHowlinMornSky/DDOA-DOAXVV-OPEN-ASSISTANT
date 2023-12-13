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
	/**
	 * @brief 主按钮被点击
	*/
	void OnBtnMain_Clicked();
	/**
	 * @brief 计时器消息
	*/
	void OnTimerUpdate();

	void BtnMain_SetText(const WCHAR* text);
	void BtnMain_SetEnabled(bool enabled);
	void BtnSettings_SetEnabled(bool enabled);

protected:
	HFONT hFont; // 字体
	HWND hBtnMain; // 主按钮
	bool m_btnMainIsStart; // 主按钮当前状态
	HWND hBtnSettingsMouse;
	HWND hBtnSettingsMsg;
	HWND hBtnSettingsCtrl;
	HWND hBtnSettingsGame;
	HWND hBtnSettingsLast; // 设置上一次比赛的单选框
	HWND hBtnSettingsNew; // 设置新比赛的单选框
	HWND hListLog; // 显示log的listbox
	Logger m_logger; // logger

	IHelper* r_helper; // helper索引
};

} // namespace ohms
