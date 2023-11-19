#pragma once

#include "ILogger.h"
#include "framework.h"

namespace ohms {

class Logger final :
	public ILogger {
public:
	Logger();

public:
	/**
	 * @brief 添加一行
	 * @param str 字符串
	*/
	virtual void addString(std::wstring_view str) override;
	/**
	 * @brief 清空
	*/
	virtual void clear() override;

public:
	/**
	 * @brief 注册目标listbox控件
	 * @param target 目标
	*/
	void reg(HWND target);

protected:
	HWND m_tergetList; // 目标listbox控件
};

} // namespace ohms
