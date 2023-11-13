#pragma once

#include "IHelper.h"

namespace ohms {

class Helper final :
	public IHelper {
public:
	Helper();
	virtual ~Helper() override;

public:
	virtual void set(HelperMessage h) override;
	virtual void update() override;

protected:
	HelperMessage m_cmd;
	bool running;
};

}
