/*
*    DDOA-DOAXVV-OPEN-ASSISTANT
*
*     Copyright 2023-2024  Tyler Parret True
*
*    Licensed under the Apache License, Version 2.0 (the "License");
*    you may not use this file except in compliance with the License.
*    You may obtain a copy of the License at
*
*        http://www.apache.org/licenses/LICENSE-2.0
*
*    Unless required by applicable law or agreed to in writing, software
*    distributed under the License is distributed on an "AS IS" BASIS,
*    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*    See the License for the specific language governing permissions and
*    limitations under the License.
*
* @Authors
*    Tyler Parret True <mysteryworldgod@outlook.com><https://github.com/OwlHowlinMornSky>
*/
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

System::Int32 HelperWrapper::SetSetting(HelprSet type, System::Int32 val) {
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

System::Boolean HelperWrapper::Start() {
	return r_helper->start();
}

System::Void HelperWrapper::AskForStop() {
	r_helper->askForStop();
}

System::Boolean HelperWrapper::IsRunning() {
	return r_helper->isRunning();
}

ReturnMessage HelperWrapper::GetMessage() {
	System::UInt32 res = r_helper->msgPop();
	return ReturnMessage(res);
}

System::UInt32 HelperWrapper::GetCode() {
	System::UInt32 res = r_helper->msgPop();
	return res;
}

System::Void HelperWrapper::Drop() {
	ohms::IHelper::drop();
	r_helper = nullptr;
}

}
