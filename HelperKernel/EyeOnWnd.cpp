
#include <opencv2/imgproc.hpp>

#include "EyeOnWnd.h"

namespace HelperKernel {

EyeOnWnd::EyeOnWnd() {
	m_mat = new cv::Mat();
	if (!ohms::wgc::ICapture::setup(true)) { // 初始化WGC
		throw gcnew System::SystemException(L"Failed to setup WGC.");
	}
	r_capture = ohms::wgc::ICapture::getInstance();
	m_hwnd = NULL;
}

EyeOnWnd::~EyeOnWnd() {
	m_hwnd = NULL;
	ohms::wgc::ICapture::drop();
	r_capture = nullptr;
	delete m_mat;
	m_mat = nullptr;
}

bool EyeOnWnd::UpdateVision() {
	if (r_capture->isRefreshed()) { // refresh过再处理画面才有意义
		r_capture->askForRefresh();
		if (r_capture->copyMatTo(*m_mat, true)) { // 要求转换为BGR
			if (m_mat->size().width != 960 || m_mat->size().height != 540) { // 确保大小满足要求
				cv::resize(
					*m_mat, *m_mat,
					cv::Size(960, 540),
					0.0, 0.0, cv::InterpolationFlags::INTER_LINEAR
				);
			}
			return true;
		}
	}
	return false;
}

const cv::Mat* EyeOnWnd::GetVision() {
	return m_mat;
}

bool EyeOnWnd::IsLooking() {
	return NULL != m_hwnd;
}

void EyeOnWnd::Reset() {
	m_hwnd = NULL;
	r_capture->stopCapture(); // 停止截图
}

bool EyeOnWnd::SetOnWnd(HWND hwnd) {
	Reset();
	if (m_hwnd == NULL) {
		return false;
	}
	m_hwnd = hwnd;
	if (!IsWindow(m_hwnd) || IsIconic(m_hwnd) || !r_capture->startCaptureWindow(m_hwnd)) { // 这些是能截图的必要条件
		m_hwnd = NULL;
		return false;
		//return SetReturnValue::CaptureFailed;
	}
	r_capture->setClipToClientArea(true);
	//if (Settings::WndHandler::DEFAULT.UseHook && !Settings::WndHandler::DEFAULT.UseSendInput)
	//	if (!TryHook())
	//		IHelper::instance()->GuiLogF(ReturnMsgEnum::HookFailed);
	//m_state = StateValue::Game;
	return true;
}

}
