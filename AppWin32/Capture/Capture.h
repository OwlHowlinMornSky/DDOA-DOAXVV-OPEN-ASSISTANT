#pragma once

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Graphics.Capture.h>
#include <winrt/Windows.Graphics.DirectX.Direct3d11.h>
#include <d3d11_4.h>
#include <windows.graphics.capture.interop.h>

#include "ICapture.h"

#include "CaptureCore.h"

namespace ohms::capture::wgc {

/**
 * @brief 截图组件。
*/
class Capture final :
	public ICapture {
public:
	Capture();
	virtual ~Capture() override;

public:
	/**
	 * @brief 创建对指定窗口的截取。
	 * @param hwnd: 指定窗口。
	 * @return 是否成功。
	*/
	virtual bool startCapture(HWND hwnd) override;
	/**
	 * @brief 停止截取。
	*/
	virtual void stopCapture() override;

	/**
	 * @brief 令截取器在下次捕获到帧时刷新 cv::Mat。
	*/
	virtual void askForRefresh() override;
	/**
	 * @brief cv::Mat 是否已经刷新。
	 * @return true 则从上次 askForRefresh 后已经刷新。
	*/
	virtual bool isRefreshed() override;

	/**
	 * @brief 保存当前 cv::Mat。
	 * @param C3: 是否保存 alpha 通道。
	 * @param id: 指定 id 防止名称重复。
	 * @return 保存是否成功开始。
	*/
	virtual bool saveMat(bool C3, size_t id) override;
	/**
	 * @brief 获取当前 cv::Mat。
	 * @param target: 保存 cv::Mat 的地方。
	 * @return 操作是否成功。
	*/
	virtual bool copyMat(cv::Mat& target) override;

protected:
	winrt::Windows::Graphics::DirectX::Direct3D11::IDirect3DDevice m_device;
	std::unique_ptr<CaptureCore> m_capture; // 截取器实例。
};

} // namespace ohms::capture::wgc
