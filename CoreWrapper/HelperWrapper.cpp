#include "HelperWrapper.h"

namespace Wrapper {

HelperWrapper::HelperWrapper() {
	m_helper = ohms::IHelper::instance();
	if (!m_helper) {
		throw gcnew System::NotImplementedException();
	}
}

HelperWrapper::~HelperWrapper() {
	ohms::IHelper::drop();
	m_helper = nullptr;
}

void HelperWrapper::set(HelprSet type, System::Int32 val) {
	switch (type) {
	case HelprSet::Cha_New:
		m_helper->regForNew(val);
		break;
	case HelprSet::Ctrl_MouseInput:
		m_helper->regForMouse(val);
		break;
	case HelprSet::ShowCV:
		m_helper->regShowCV(val);
		break;
	}
}

bool HelperWrapper::start() {
	return m_helper->start();
}

void HelperWrapper::askForStop() {
	m_helper->askForStop();
}

bool HelperWrapper::isRunning() {
	return m_helper->isRunning();
}

ReturnMessage HelperWrapper::msgPop() {
	System::UInt32 res = m_helper->msgPop();
	return ReturnMessage(res);
}

System::UInt32 HelperWrapper::codePop() {
	System::UInt32 res = m_helper->msgPop();
	return res;
}

}
