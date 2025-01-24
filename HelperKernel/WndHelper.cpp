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
#include <Windows.h>
#include "WndHelper.h"
#include <string>

bool HelperKernel::WndHelper::WindowExist(System::String^ cls, System::String^ title) {
	std::wstring cstr0;
	if (cls != nullptr) {
		cli::array<wchar_t>^ wArray0 = cls->ToCharArray();
		int len0 = wArray0->Length;
		cstr0.resize(len0);
		System::IntPtr pcstr0(cstr0.data());
		System::Runtime::InteropServices::Marshal::Copy(wArray0, 0, pcstr0, len0);
	}

	std::wstring cstr1;
	if (title != nullptr) {
		cli::array<wchar_t>^ wArray1 = title->ToCharArray();
		int len1 = wArray1->Length;
		cstr1.resize(len1);
		System::IntPtr pcstr1(cstr1.data());
		System::Runtime::InteropServices::Marshal::Copy(wArray1, 0, pcstr1, len1);
	}

	return NULL != FindWindowW(cstr0.c_str(), cstr1.c_str());
}

void HelperKernel::WndHelper::ShellStart(System::String^ path) {
	std::wstring cstr;
	if (path != nullptr) {
		cli::array<wchar_t>^ wArray = path->ToCharArray();
		int len = wArray->Length;
		cstr.resize(len);
		System::IntPtr pcstr(cstr.data());
		System::Runtime::InteropServices::Marshal::Copy(wArray, 0, pcstr, len);
	}

	SHELLEXECUTEINFOW info{};
	info.cbSize = sizeof(info);
	info.lpVerb = L"open";
	info.nShow = SW_SHOWNORMAL;

	info.lpFile = cstr.c_str();
	ShellExecuteExW(&info);
}

void HelperKernel::WndHelper::SetState(int continuous, int system, int display, int awaymode) {
	EXECUTION_STATE es{};
	es |= continuous ? ES_CONTINUOUS : 0;
	es |= system ? ES_SYSTEM_REQUIRED : 0;
	es |= display ? ES_DISPLAY_REQUIRED : 0;
	es |= awaymode ? ES_AWAYMODE_REQUIRED : 0;
	SetThreadExecutionState(es);
}
