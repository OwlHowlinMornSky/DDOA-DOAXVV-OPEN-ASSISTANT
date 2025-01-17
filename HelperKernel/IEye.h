#pragma once

#include <opencv2/core/mat.hpp>

namespace HelperKernel {

/**
 * @brief 眼。
 */
public interface class IEye {
public:
	/**
	 * @brief 要求刷新视野。
	 */
	void RequireRefresh();
	/**
	 * @brief 把视野内容保存。
	 * @return 获得了新的内容则为 true，否则内容未刷新 返回 false。
	 */
	bool SaveVision();
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

	void DrawRectangle(System::Drawing::Rectangle rect, System::Drawing::Color color);
	void ShowDebugWindow();
};

}
