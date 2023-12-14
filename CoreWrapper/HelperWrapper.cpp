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

void HelperWrapper::regForNew(bool forNew) {
	m_helper->regForNew(forNew);
}

void HelperWrapper::regForMouse(bool forMouse) {
	m_helper->regForMouse(forMouse);
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
