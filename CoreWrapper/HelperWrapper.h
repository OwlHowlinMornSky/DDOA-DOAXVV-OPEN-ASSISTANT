#pragma once

#include <IHelper.h>
#include "ReturnMessages.h"

namespace Wrapper {

public ref class HelperWrapper {
public:
	HelperWrapper();
	~HelperWrapper();

public:
	void regForNew(bool forNew);
	void regForMouse(bool forMouse);

	bool start();
	void askForStop();
	bool isRunning();

	ReturnMessage msgPop();
	System::UInt32 codePop();

private:
	ohms::IHelper* m_helper;
};

} // namespace Wrapper
