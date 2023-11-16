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
	/**
	 * @brief 开始任务。
	*/
	void start();
	/**
	 * @brief 停止任务。
	*/
	void stop();
	/**
	 * @brief 本窗口更新。
	*/
	void update();

	/**
	 * @brief 修改主按钮的文本。
	 * @param text: 文本。
	*/
	void setBtnText(const WCHAR* text);
	/**
	 * @brief 修改主按钮可用性。
	 * @param enabled: true 为 可用。
	*/
	void setBtnEnabled(bool enabled);

protected:
	HFONT m_hFont;
	HWND m_hBtn;
	HWND m_hButtonSave;
	HWND m_hButtonSaveC3;
	HWND m_hList;

	bool m_isStart;
	size_t m_saveCount;
};

} // namespace ohms
