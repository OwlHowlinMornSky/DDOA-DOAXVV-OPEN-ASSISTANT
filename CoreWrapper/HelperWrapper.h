#pragma once

#include <IHelper.h>
#include "ReturnMessages.h"
#include "SettingsEnum.h"

namespace Wrapper {

public ref class HelperWrapper {
public:
	HelperWrapper();
	~HelperWrapper();

public:
	void set(HelprSet type, System::Int32 val);

	bool start();
	void askForStop();
	bool isRunning();

	ReturnMessage msgPop();
	System::UInt32 codePop();

	void drop();

private:
	ohms::IHelper* m_helper;
};

} // namespace Wrapper
