
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include "EyeOnWnd.h"

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

void EyeOnWnd::DrawRectangle(System::Drawing::Rectangle rect, System::Drawing::Color color) {
#ifdef _DEBUG
	cv::rectangle(
		*m_mat,
		cv::Rect(rect.X, rect.Y, rect.Width, rect.Height),
		cv::Scalar(color.R, color.G, color.B),
		2, 8, 0
	);
#endif // _DEBUG
}

void EyeOnWnd::ShowDebugWindow() {
#ifdef _DEBUG
	cv::resize(*m_mat, *m_mat, m_mat->size() / 2, 0.0, 0.0, cv::InterpolationFlags::INTER_LINEAR); // 缩小到一半
	cv::imshow("show", *m_mat); // show
	cv::waitKey(1);
#endif // _DEBUG
}

void EyeOnWnd::Reset() {
	m_hwnd = NULL;
	r_capture->stopCapture(); // 停止截图
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
	wchar_t* cstr0 = nullptr;
	if (cls != nullptr) {
		cli::array<wchar_t>^ wArray0 = cls->ToCharArray();
		int len0 = wArray0->Length;
		cstr0 = new wchar_t[len0 + 2];
		System::IntPtr pcstr0(cstr0);
		System::Runtime::InteropServices::Marshal::Copy(wArray0, 0, pcstr0, len0);
		cstr0[len0] = 0;
		cstr0[len0 + 1] = 0;
	}

	wchar_t* cstr1 = nullptr;
	if (title != nullptr) {
		cli::array<wchar_t>^ wArray1 = title->ToCharArray();
		int len1 = wArray1->Length;
		cstr1 = new wchar_t[len1 + 2];
		System::IntPtr pcstr1(cstr1);
		System::Runtime::InteropServices::Marshal::Copy(wArray1, 0, pcstr1, len1);
		cstr1[len1] = 0;
		cstr1[len1 + 1] = 0;
	}

	HWND hwnd = FindWindowW(cstr0, cstr1);
	if (hwnd == NULL) {
		return 1;
	}
	return SetOnWnd(hwnd);
}

}
