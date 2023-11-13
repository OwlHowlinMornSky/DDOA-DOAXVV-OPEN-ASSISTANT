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
	virtual bool startCapture(HWND hwnd) override;
	virtual void stopCapture() override;

	virtual void askForRefresh() override;
	virtual bool isRefreshed() override;

	virtual bool saveMat(bool C3, size_t id) override;
	virtual const cv::Mat* getMat() override;

protected:
	winrt::Windows::Graphics::DirectX::Direct3D11::IDirect3DDevice m_device;
	std::unique_ptr<CaptureCore> m_capture;
};

} // namespace ohms::capture::wgc
