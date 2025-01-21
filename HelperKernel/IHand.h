/*
*    DDOA-DOAXVV-OPEN-ASSISTANT
*
*     Copyright 2023-2025  Tyler Parret True
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

using namespace System;

namespace HelperKernel {

public interface class IHand {
public:
	bool IsOperating();
	
	void MoveCursorTo(Drawing::Point target);
	void MoveMouseWheel(bool isDown, unsigned int cnt);
	Drawing::Point GetCursorPosition();

	void ClickAt(Drawing::Point target);

	int SetUserCursorInterceptionEnabled(bool enabled);
	bool GetUserCursorInterceptionEnabled();

	//void PressKey();
};

}
