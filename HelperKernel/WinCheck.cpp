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
#include "WinCheck.h"
#include "framework.h"


namespace {

std::wstring ParseErrorCode(long code) {
	DWORD lasterrcode = code;
	LPWSTR pBuffer = NULL;
	std::wstring msgstr_user;
	FormatMessageW(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, lasterrcode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPWSTR)&pBuffer, 8, NULL
	);
	if (pBuffer) {
		msgstr_user.append(pBuffer);
		LocalFree(pBuffer);
	}
	return msgstr_user;
}

}

std::wstring ParseWin32Error() {
	return ::ParseErrorCode(GetLastError());
}
