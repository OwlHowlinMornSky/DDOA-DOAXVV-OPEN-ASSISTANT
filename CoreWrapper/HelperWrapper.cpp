#include "HelperWrapper.h"

namespace Wrapper {

HelperWrapper::HelperWrapper() {
	r_helper = ohms::IHelper::instance();
	if (!r_helper) {
		throw gcnew System::NotImplementedException();
	}
}

HelperWrapper::~HelperWrapper() {
	ohms::IHelper::drop();
	r_helper = nullptr;
}

System::Int32 HelperWrapper::set(HelprSet type, System::Int32 val) {
	switch (type) {
	case HelprSet::Cha_New:
		return r_helper->regForNew(val);
	case HelprSet::Ctrl_MouseInput:
		return r_helper->regForMouse(val);
	case HelprSet::ShowCV:
		return r_helper->regShowCV(val);
	case HelprSet::PreventFromSleep:
		return r_helper->regPrevent(val);
	case HelprSet::KeepDisplay:
		return r_helper->regPreventKeepDisplay(val);
	}
	return 1l;
}

System::Boolean HelperWrapper::start() {
	return r_helper->start();
}

System::Void HelperWrapper::askForStop() {
	r_helper->askForStop();
}

System::Boolean HelperWrapper::isRunning() {
	return r_helper->isRunning();
}

ReturnMessage HelperWrapper::msgPop() {
	System::UInt32 res = r_helper->msgPop();
	return ReturnMessage(res);
}

System::UInt32 HelperWrapper::codePop() {
	System::UInt32 res = r_helper->msgPop();
	return res;
}

System::Void HelperWrapper::drop() {
	ohms::IHelper::drop();
	r_helper = nullptr;
}

}
