#pragma once

#include <queue>
#include <mutex>
#include <atomic>

#include "Time.h"
#include "IHelper.h"

#include <ohms/WGC.h>
#include <opencv2/opencv.hpp>

namespace ohms {

class Helper final :
	public IHelper {
	friend class IHelper;
protected:
	Helper();
public:
	virtual ~Helper() override;

public:
	virtual void regLogger(ILogger* logger) override;
	virtual void regForNew(bool forNew) override;

	virtual bool start() override;
	virtual void askForStop() override;
	virtual bool isRunning() override;
	virtual bool msgPop(HelperReturnMessage& hrm) override;

protected:
	void mainwork(); // 运行在子线程的任务。
	void msgPush(ohms::HelperReturnMessage hrm);

// 子任务（在 Helper.subworks.cpp 实现）
protected:
	void subwork_challenge(); // 挑战赛。

// 单步操作（在 Helper.steps.cpp 实现）
protected:
	bool step_copyMat(cv::Mat& target);

	bool step_waitFor(
		const cv::Mat& matTemplate, const cv::Rect searchRect, cv::Rect& findRect,
		Time maxTime = seconds(10.0f), float thres = 10.0f
	);

	bool step_click(cv::Point pt);
	bool step_move(cv::Point pt);

	bool step_keepClickingUntil(
		const cv::Point clkPt, const cv::Mat& matTemplate, const cv::Rect searchRect,
		Time maxTime = seconds(10.0f), Time clkTime = seconds(1.0f), float thres = 10.0f
	);

	void step_subtaskError(std::wstring_view str);

// 成员变量
protected:
	std::atomic_bool m_running;
	std::atomic_bool m_askedForStop;

	std::queue<ohms::HelperReturnMessage> m_hrm;
	std::mutex m_hrm_mutex;
	ILogger* r_logger;

	HWND m_doaxvv;
	wgc::ICapture* r_capture;

	// 上一次比赛 和 新比赛 的图样，以及查找范围。
	cv::Mat mat_ChaGameLast;
	cv::Mat mat_ChaGameNew;
	cv::Rect rect_ChaGame;
	bool task_ChaGame_ForNew; // 选择新比赛。

	// 编队页面右下角的 挑战按钮。
	cv::Mat mat_StartGame;
	cv::Rect rect_StartGame;

	// 结算页面右上角的 RESULT。
	cv::Mat mat_Result;
	cv::Rect rect_Result;

	// 加载页面左上角的 DOAXVV。
	cv::Mat mat_Loading;
	cv::Rect rect_Loading;

	// 编队页面中间 可能出现的 FP不足。
	cv::Mat mat_LowFP;
	cv::Rect rect_LowFP;

	// 挑战赛页面的 标签页栏 (推荐、主要、每日、活动)。
	cv::Mat mat_ChaTabBar;
	cv::Rect rect_ChaTabBar;
};

} // namespace ohms
