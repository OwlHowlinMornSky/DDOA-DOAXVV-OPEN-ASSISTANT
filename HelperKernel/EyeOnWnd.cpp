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
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include "EyeOnWnd.h"
#include <string>

namespace HelperKernel {

EyeOnWnd::EyeOnWnd() :
	m_hwnd(NULL),
	m_mat(new cv::Mat()) {
	if (!ohms::wgc::ICapture::setup(true)) { // 初始化WGC
		throw gcnew System::SystemException(L"Failed to setup WGC.");
	}
	r_capture = ohms::wgc::ICapture::getInstance();
#ifdef _DEBUG
	m_matDebug = new cv::Mat();
#endif // _DEBUG
}

EyeOnWnd::~EyeOnWnd() {
	Reset();
	m_hwnd = NULL;
	ohms::wgc::ICapture::drop();
	r_capture = nullptr;
	delete m_mat;
	m_mat = nullptr;
#ifdef _DEBUG
	delete m_matDebug;
#endif // _DEBUG
}

void EyeOnWnd::RequireRefresh() {
	return r_capture->askForRefresh();
}

bool EyeOnWnd::SaveVision() {
	if (!r_capture->isRefreshed()) { // refresh过再处理画面才有意义
		return false;
	}
	r_capture->askForRefresh();
	if (!r_capture->copyMatTo(*m_mat, true)) { // 要求转换为BGR
		return false;
	}
	if (m_mat->size().width != 960 || m_mat->size().height != 540) { // 确保大小满足要求
		cv::resize(
			*m_mat, *m_mat,
			cv::Size(960, 540),
			0.0, 0.0, cv::InterpolationFlags::INTER_LINEAR
		);
	}
	return true;
}

const cv::Mat* EyeOnWnd::GetVision() {
	if (!IsLooking()) return nullptr;
	return m_mat;
}

bool EyeOnWnd::IsLooking() {
	return NULL != m_hwnd;
}

void EyeOnWnd::BeginDebugDraw() {
#ifdef _DEBUG
	//cv::resize(*m_mat, *m_mat, m_mat->size() / 2, 0.0, 0.0, cv::InterpolationFlags::INTER_LINEAR); // 缩小到一半
#endif // _DEBUG
}

void EyeOnWnd::DrawRectangle(System::Drawing::Rectangle rect, System::Drawing::Color color) {
#ifdef _DEBUG
	cv::rectangle(
		*m_mat,
		cv::Rect(rect.X, rect.Y, rect.Width, rect.Height),
		cv::Scalar(color.B, color.G, color.R),
		2, 8, 0
	);
#endif // _DEBUG
}

void EyeOnWnd::ShowDebugWindow() {
#ifdef _DEBUG
	cv::imshow("show", *m_mat); // show
	cv::waitKey(1);
#endif // _DEBUG
}

void EyeOnWnd::DestroyDebugWindows() {
#ifdef _DEBUG
	cv::waitKey(1);
	cv::destroyAllWindows();
	cv::waitKey(1);
#endif // _DEBUG
}

void EyeOnWnd::Reset() {
	m_hwnd = NULL;
	r_capture->stopCapture(); // 停止截图
	DestroyDebugWindows();
}

int EyeOnWnd::SetOnWnd(HWND hwnd) {
	Reset();
	if (hwnd == NULL) {
		return 1;
	}
	m_hwnd = hwnd;
	if (!IsWindow(m_hwnd) || IsIconic(m_hwnd) || !r_capture->startCaptureWindow(m_hwnd)) { // 这些是能截图的必要条件
		m_hwnd = NULL;
		return 2;
	}
	r_capture->setClipToClientArea(true);
	return 0;
}

int EyeOnWnd::SetOnWnd(System::String^ cls, System::String^ title) {
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

	HWND hwnd = FindWindowW(cstr0.c_str(), cstr1.c_str());
	if (hwnd == NULL) {
		return 1;
	}
	return SetOnWnd(hwnd);
}

}
