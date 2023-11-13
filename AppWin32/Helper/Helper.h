#pragma once

#include "IHelper.h"

namespace ohms {

class Helper final :
	public IHelper {

public:
	virtual void start() override;
	virtual void stop() override;

	virtual int update() override;

protected:

};

}
