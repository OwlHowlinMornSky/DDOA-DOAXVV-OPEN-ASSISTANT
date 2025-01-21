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

#include "IEye.h"
#include <ohms/WGC.h>
#include "framework.h"

namespace HelperKernel {

public ref class EyeOnWnd sealed : public IEye {
public:
	EyeOnWnd();
	virtual ~EyeOnWnd();

public:
	virtual void RequireRefresh();
	virtual bool SaveVision();
	virtual const cv::Mat* GetVision();
	virtual bool IsLooking();

	virtual void DrawRectangle(System::Drawing::Rectangle rect, System::Drawing::Color color);
	virtual void ShowDebugWindow();

public:
	void Reset();
	int SetOnWnd(HWND hwnd);
	int SetOnWnd(System::String^ cls, System::String^ title);

private:
	HWND m_hwnd; // 窗口句柄
	cv::Mat* m_mat; // 截取到的帧的存储位置。
	ohms::wgc::ICapture* r_capture; // capture索引
#ifdef _DEBUG
	cv::Mat* m_matDebug; // 截取到的帧的存储位置。
#endif // _DEBUG
};

}
