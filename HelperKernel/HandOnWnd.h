#pragma once

#include "IHand.h"
#include "framework.h"

namespace HelperKernel {

public ref class HandOnWnd sealed : public IHand {
public:
	HandOnWnd();
	virtual ~HandOnWnd();

public:
	virtual bool IsOperating();

	virtual void MoveCursorTo(Drawing::Point target);
	virtual void MoveMouseWheel(bool isDown, unsigned int cnt);
	virtual Drawing::Point GetCursorPosition();

	virtual void ClickAt(Drawing::Point target);

	virtual bool SetUserCursorInterceptionEnabled(bool enabled);
	virtual bool GetUserCursorInterceptionEnabled();

public:
	void Reset();
	bool SetOnWnd(HWND hwnd);
	bool SetOnWnd(System::String^ cls, System::String^ title);

protected:
	bool InitHookMod();
	bool TryHook();
	void DropHook();
	void DropHookMod();

private:
	HWND m_hwnd; // 窗口句柄
	Drawing::Point m_screenSize; // 屏幕大小。
	Drawing::Point m_lastMousePoint; // 鼠标位置记录。
	Drawing::Rectangle m_workArea; // 工作区域（即除去任务栏）。

	HMODULE m_hmod; // 挂钩模块句柄。
	FARPROC m_hookproc; // 挂钩过程。
	HHOOK m_hhook; // 挂钩句柄。
};

}
