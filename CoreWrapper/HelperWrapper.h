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
	System::Int32 set(HelprSet type, System::Int32 val);

	System::Boolean start();
	System::Void askForStop();
	System::Boolean isRunning();

	ReturnMessage msgPop();
	System::UInt32 codePop();

	System::Void drop();

private:
	ohms::IHelper* r_helper;
};

} // namespace Wrapper
