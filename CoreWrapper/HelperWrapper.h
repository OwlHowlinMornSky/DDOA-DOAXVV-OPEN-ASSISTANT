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
	System::Int32 SetSetting(HelprSet type, System::Int32 val);

	System::Boolean Start();
	System::Void AskForStop();
	System::Boolean IsRunning();

	ReturnMessage GetMessage();
	System::UInt32 GetCode();

	System::Void Drop();

private:
	ohms::IHelper* r_helper;
};

} // namespace Wrapper
