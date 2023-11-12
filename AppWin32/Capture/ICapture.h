#pragma once

namespace ohms::capture::wgc {

class ICapture {
public:
	ICapture() = default;
	virtual ~ICapture() = default;

	virtual void Initialize() = 0;

	virtual bool StartCapture(HWND hwnd) = 0;

	virtual void Stop() = 0;

	virtual void setNeedRefresh() = 0;

	virtual void setDecimationMode(bool val) = 0;

	virtual void setClipClientArea(bool val) = 0;

	virtual void setShowScale(int val) = 0;

	virtual bool saveNow(bool C3, size_t id) = 0;
};

} // namespace ohms::capture::wgc