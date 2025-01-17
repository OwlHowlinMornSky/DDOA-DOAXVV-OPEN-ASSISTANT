#pragma once

#include <opencv2/core/mat.hpp>

namespace HelperKernel {

public interface class IEye {
public:
	bool UpdateVision();
	const cv::Mat* GetVision();
	bool IsLooking();
};

}
