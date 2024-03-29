﻿/*
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

#include <Settings.h>

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

System::Int32 HelperWrapper::SetChallengeForNewOrLast(bool forNew) {
	ohms::Settings::mainSettings.ChaGame_ForNew = forNew;
	return System::Int32(0);
}

System::Int32 HelperWrapper::SetMouseSendInputOrSendMessage(bool sendInput) {
	ohms::Settings::mainSettings.Mouse_ForMouse = sendInput;
	return System::Int32(0);
}

System::Int32 HelperWrapper::SetShowCaptureOrNot(bool show) {
	return r_helper->SetShowCaptureOrNot(show);
}

System::Int32 HelperWrapper::SetKeepAwakeOrNot(bool keep) {
	ohms::Settings::mainSettings.PreventFromSleep = keep;
	return System::Int32(0);
}

System::Int32 HelperWrapper::SetKeepScreenOnOrNot(bool keep) {
	ohms::Settings::mainSettings.KeepDisplay = keep;
	return System::Int32(0);
}

System::Int32 HelperWrapper::SetChallengeCheckAwardOrNot(bool check) {
	ohms::Settings::mainSettings.ChaGame_CheckAddition = check;
	return System::Int32(0);
}

System::Int32 HelperWrapper::SetChallengePlayAwardOrNot(bool play) {
	ohms::Settings::mainSettings.ChaGame_EnterAddition = play;
	return System::Int32(0);
}

}
