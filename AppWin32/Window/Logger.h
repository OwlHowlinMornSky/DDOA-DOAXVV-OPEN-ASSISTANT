#pragma once

#include "ILogger.h"
#include "framework.h"

namespace ohms {

class Logger final :
	public ILogger {
public:
	Logger();

public:
	virtual void addString(std::wstring_view str) override;

	virtual void clear() override;

public:
	void reg(HWND target);

protected:
	HWND m_tergetList;
};

} // namespace ohms
