#pragma once

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Graphics.Capture.h>
#include <winrt/Windows.Graphics.DirectX.Direct3d11.h>
#include <d3d11_4.h>
#include <windows.graphics.capture.interop.h>

#include "ICapture.h"

#include "CaptureCore.h"

namespace ohms::capture::wgc {

class Capture final :
	public ICapture {
public:
	Capture();
	virtual ~Capture() = default;

public:
	virtual void Initialize() override;
	virtual bool StartCapture(HWND hwnd) override;
	virtual void Stop() override;

	virtual void setNeedRefresh() override;
	//virtual void setDecimationMode(bool val) override;
	virtual void setClipClientArea(bool val) override;
	//virtual void setShowScale(int val) override;

	virtual bool saveNow(bool C3, size_t id) override;

	virtual const cv::Mat* getCapMat() override;
	virtual bool getUpdated() override;

protected:
	winrt::Windows::Graphics::DirectX::Direct3D11::IDirect3DDevice m_device;
	std::unique_ptr<CaptureCore> m_capture;
};

} // namespace ohms::capture::wgc
