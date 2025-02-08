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

#include "IHand.h"
#include "framework.h"

namespace HelperKernel {

public ref class HandOnWnd sealed : public IHand {
public:
	HandOnWnd();
	virtual ~HandOnWnd();

public:
	virtual bool IsOperating();

	virtual void MoveCursorTo(Drawing::Point target);
	virtual void MoveMouseWheel(bool isDown, unsigned int cnt);
	virtual Drawing::Point GetCursorPosition();

	virtual void ClickAt(Drawing::Point target);

	virtual int SetUserCursorInterceptionEnabled(bool enabled);
	virtual bool GetUserCursorInterceptionEnabled();

public:
	void Reset();
	int SetOnWnd(HWND hwnd);
	int SetOnWnd(System::String^ cls, System::String^ title);

protected:
	int InitHookMod();
	int TryHook();
	void DropHook();
	void DropHookMod();

private:
	HWND m_hwnd; // ´°¿Ú¾ä±ú
	Drawing::Point m_lastMousePoint; // Êó±êÎ»ÖÃ¼ÇÂ¼¡£

	HMODULE m_hmod; // ¹Ò¹³Ä£¿é¾ä±ú¡£
	FARPROC m_hookproc; // ¹Ò¹³¹ý³Ì¡£
	HHOOK m_hhook; // ¹Ò¹³¾ä±ú¡£
};

}
