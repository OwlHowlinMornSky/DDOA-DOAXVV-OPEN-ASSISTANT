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
	virtual bool UpdateVision();
	virtual const cv::Mat* GetVision();
	virtual bool IsLooking();

public:
	void Reset();
	bool SetOnWnd(HWND hwnd);

private:
	HWND m_hwnd; // 窗口句柄
	cv::Mat* m_mat; // 截取到的帧的存储位置。
	ohms::wgc::ICapture* r_capture; // capture索引
};

}
