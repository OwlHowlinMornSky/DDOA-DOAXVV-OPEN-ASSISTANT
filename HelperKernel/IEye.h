#pragma once

#include <opencv2/core/mat.hpp>

namespace HelperKernel {

/**
 * @brief 眼。
 */
public interface class IEye {
public:
	/**
	 * @brief 刷新视野。
	 * @return 获得了新的视野则为 true，否则视野未刷新 返回 false。
	 */
	bool UpdateVision();
	/**
	 * @brief 获取当前的视野。
	 * @return 当前视野，可能为nullptr（即没有视野）。
	 */
	const cv::Mat* GetVision();
	/**
	 * @brief 检查是否正在观察。
	 * @return 是否正在观察。
	 */
	bool IsLooking();
};

}
