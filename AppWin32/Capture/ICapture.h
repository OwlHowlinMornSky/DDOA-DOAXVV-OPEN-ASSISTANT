#pragma once

#include <opencv2/core/mat.hpp>

namespace ohms::capture::wgc {

class ICapture {
public:
	ICapture() = default;
	virtual ~ICapture() = default;

public:
	virtual void Initialize() = 0;
	virtual bool StartCapture(HWND hwnd) = 0;
	virtual void Stop() = 0;

	virtual void setNeedRefresh() = 0;
	virtual void setDecimationMode(bool val) = 0;
	virtual void setClipClientArea(bool val) = 0;
	virtual void setShowScale(int val) = 0;
	virtual bool saveNow(bool C3, size_t id) = 0;

	virtual const cv::Mat* getCapMat() = 0;
	virtual bool getUpdated() = 0;
};

} // namespace ohms::capture::wgc