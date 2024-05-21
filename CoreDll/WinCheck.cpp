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

std::string ParseErrorCode(long code) {
	DWORD lasterrcode = code;
	LPSTR pBuffer = NULL;
	std::string msgstr_en;// , msgstr_user;
	FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, lasterrcode, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), (LPSTR)&pBuffer, 0, NULL);
	if (pBuffer) {
		pBuffer[lstrlenA(pBuffer) - 1] = '\0';
		msgstr_en.append(pBuffer);
		LocalFree(pBuffer);
	}
	return msgstr_en;
}

}

std::string ParseWin32Error() {
	return ::ParseErrorCode(GetLastError());
}
