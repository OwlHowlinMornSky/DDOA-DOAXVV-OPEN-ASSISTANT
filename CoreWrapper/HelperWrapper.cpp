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

#include <Settings.h>

namespace Wrapper {

HelperWrapper::HelperWrapper() {
	r_helper = ohms::IHelper::instance();
	if (!r_helper) {
		throw gcnew System::TypeLoadException();
	}
}

HelperWrapper::~HelperWrapper() {
	Drop();
}

System::Boolean HelperWrapper::Start() {
	return r_helper->start();
}

System::Void HelperWrapper::AskForStop() {
	r_helper->askForStop();
}

System::Void HelperWrapper::Resume() {
	r_helper->resume();
}

System::Boolean HelperWrapper::IsRunning() {
	return r_helper->isRunning();
}

ReturnCmd HelperWrapper::GetCommand() {
	System::Int32 res = r_helper->msgPop();
    return ReturnCmd(res);
}

ReturnMessage HelperWrapper::GetMessage() {
	System::Int32 res = r_helper->msgPop();
	return ReturnMessage(res);
}

System::Int32 HelperWrapper::GetValueI() {
	System::Int32 res = r_helper->msgPop();
	return res;
}

System::Int32 HelperWrapper::Setup() {
	return r_helper->setup();
}

System::Void HelperWrapper::Drop() {
	ohms::IHelper::drop();
	r_helper = nullptr;
}

System::Int32 HelperWrapper::SetChallengeForNewOrLast(bool forNew) {
	ohms::Settings::Challenge::DEFAULT.PlayNewMatchOrPrevious = forNew;
	return System::Int32(0);
}

System::Int32 HelperWrapper::SetChallengeForRecord(bool forRecord) {
	ohms::Settings::Challenge::DEFAULT.PlayRecord = forRecord;
	return System::Int32(0);
}

System::Int32 HelperWrapper::SetMouseSendInputOrSendMessage(bool sendInput) {
	ohms::Settings::WndHandler::DEFAULT.UseSendInput = sendInput;
	return System::Int32(0);
}

System::Int32 HelperWrapper::SetShowCaptureOrNot(bool show) {
	ohms::Settings::WndHandler::DEFAULT.Debug_ShowCapture = show;
	return System::Int32(0);
}

System::Int32 HelperWrapper::SetKeepAwakeOrNot(bool keep) {
	ohms::Settings::Global::DEFAULT.KeepAwake = keep;
	return System::Int32(0);
}

System::Int32 HelperWrapper::SetKeepScreenOnOrNot(bool keep) {
	ohms::Settings::Global::DEFAULT.KeepScreenOn = keep;
	return System::Int32(0);
}

System::Int32 HelperWrapper::SetChallengeCheckAwardOrNot(bool check) {
	ohms::Settings::Challenge::DEFAULT.CheckAddition = check;
	return System::Int32(0);
}

System::Int32 HelperWrapper::SetChallengePlayAwardOrNot(bool play) {
	ohms::Settings::Challenge::DEFAULT.EnterAddition = play;
	return System::Int32(0);
}

System::Int32 HelperWrapper::SetTaskList(array<System::UInt32>^ list) {
	if (list->Length >= ohms::Settings::Global::ListLength)
		return System::Int32(1);
	ohms::Settings::Global::DEFAULT.ClearList();
	for (int i = 0, n = list->Length; i < n; ++i) {
		ohms::Settings::Global::DEFAULT.Work_TaskList[i] = list[i];
	}
	return System::Int32(0);
}

System::Int32 HelperWrapper::SetUseCamFP(System::Boolean isSettedUse) {
	ohms::Settings::Challenge::DEFAULT.AutoUseCamFP = isSettedUse;
    return System::Int32(0);
}

void HelperWrapper::SetDoDailyCheck(bool setDo) {
	ohms::Settings::Daily::DEFAULT.DoCheck = setDo;
	return;
}

void HelperWrapper::SetDoDailyShot(bool setDo) {
	ohms::Settings::Daily::DEFAULT.DoShot = setDo;
	return;
}

void HelperWrapper::SetUseHook(bool use) {
	ohms::Settings::WndHandler::DEFAULT.UseHook = use;
	return;
}

void HelperWrapper::SetChaAskForManual(bool ask) {
	ohms::Settings::Challenge::DEFAULT.AskForManual = ask;
	return;
}

void HelperWrapper::SetChaAutoUseDrink(bool use) {
	ohms::Settings::Challenge::DEFAULT.AutoUseDrink = use;
	return;
}

int HelperWrapper::StartRecord() {
	return ohms::IHelper::instance()->StartRecord();
}

int HelperWrapper::StopRecord() {
    return ohms::IHelper::instance()->StopRecord();
}

}
