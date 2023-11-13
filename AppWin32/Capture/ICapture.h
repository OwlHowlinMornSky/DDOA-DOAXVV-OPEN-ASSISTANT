#pragma once

#include <opencv2/core/mat.hpp>

namespace ohms::capture::wgc {

/**
 * @brief 截图组件 的 接口。
*/
class ICapture {
public:
	ICapture() = default;
	virtual ~ICapture() = default;

public:
	/**
	 * @brief 创建对指定窗口的截取。
	 * @param hwnd: 指定窗口。
	 * @return 是否成功。
	*/
	virtual bool startCapture(HWND hwnd) = 0;
	/**
	 * @brief 停止截取。
	*/
	virtual void stopCapture() = 0;

	/**
	 * @brief 令截取器在下次捕获到帧时刷新 cv::Mat。
	*/
	virtual void askForRefresh() = 0;
	/**
	 * @brief cv::Mat 是否已经刷新。
	 * @return true 则从上次 askForRefresh 后已经刷新。
	*/
	virtual bool isRefreshed() = 0;

	/**
	 * @brief 保存当前 cv::Mat。
	 * @param C3: 是否保存 alpha 通道。
	 * @param id: 指定 id 防止名称重复。
	 * @return 保存是否成功开始。
	*/
	virtual bool saveMat(bool C3, size_t id) = 0;
	/**
	 * @brief 获取当前 cv::Mat。
	 * @return 当前 cv::Mat。可能为 nullptr。
	*/
	virtual const cv::Mat* getMat() = 0;
};

} // namespace ohms::capture::wgc