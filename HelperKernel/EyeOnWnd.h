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
