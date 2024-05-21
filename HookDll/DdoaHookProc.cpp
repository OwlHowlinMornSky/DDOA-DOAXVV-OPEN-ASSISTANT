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
#include "DdoaHookProc.h"

#ifdef __cplusplus    // If used by C++ code, 
extern "C" {          // we need to export the C interface
#endif

	DLL_API LRESULT CALLBACK DdoaHookProc(
		_In_ int    code,
		_In_ WPARAM wParam,
		_In_ LPARAM lParam
	) {
		if (code < 0) {
			return CallNextHookEx(NULL, code, wParam, lParam);
		}
		LPMSG msg = (LPMSG)lParam;
		switch (msg->message) {
		case WM_MOUSEMOVE:
		{
			POINTS pt = MAKEPOINTS(msg->lParam);
			if (pt.y < 0)
				break;
			if (!(msg->wParam & MK_CONTROL))
				msg->message = WM_NULL;
			break;
		}
		case WM_LBUTTONDOWN:
		{
			if (!(msg->wParam & MK_CONTROL))
				msg->message = NULL;
			break;
		}
		}
		return CallNextHookEx(NULL, code, wParam, lParam);
	}

#ifdef __cplusplus
}
#endif
