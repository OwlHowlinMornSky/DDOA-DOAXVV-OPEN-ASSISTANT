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
#include "SystemThings.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

void Wrapper::SystemThings::SetCloseEnabled(System::IntPtr hwnd, System::Boolean enabled) {
	HMENU hmenu = GetSystemMenu((HWND)(void*)hwnd, FALSE);
	EnableMenuItem(hmenu, SC_CLOSE, enabled ? MF_ENABLED : MF_GRAYED);
}
