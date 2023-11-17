#pragma once

#include <memory>
#include <queue>
#include <mutex>
#include <atomic>

#include <opencv2/opencv.hpp>
#include "../Window/framework.h"
#include <ohms/WGC.h>

#include "Clock.h"
#include "IHelper.h"

namespace ohms {

class Helper final :
	public IHelper {
	friend class IHelper;
protected:
	Helper();
public:
	virtual ~Helper() override;

public:
	virtual void regLogger(Logger* logger) override;

	virtual bool start() override;
	virtual void askForStop() override;
	virtual bool isRunning() override;
	virtual bool popMessage(HelperReturnMessage& hrm) override;

	/**
	 * @brief 向队列压入消息。
	 * @param hrm: 消息。
	*/
	void pushHRM(ohms::HelperReturnMessage hrm);

protected:
	/**
	 * @brief 运行在子线程的任务。
	*/
	void work();

	/**
	 * @brief 子任务：作战。
	*/
	void subwork_fight();

protected:
	bool copyMatResize(cv::Mat& target);

	bool step_waitFor(
		bool find,
		const cv::Mat& matTemplate,
		cv::Rect& rect,
		Time maxTime = Time::Zero,
		unsigned int threshold = 10
	);
	bool step_check(
		const cv::Mat& matSample,
		const cv::Mat& matTemplate,
		unsigned int threshold = 10
	);
	bool step_find(
		const cv::Mat& matSample,
		const cv::Mat& matTemplate,
		cv::Rect& rect,
		unsigned int threshold = 10
	);
	bool step_click(cv::Point pt);
	bool step_move(cv::Point pt);
	bool keepClickingUntil(
		cv::Point pt,
		cv::Rect rect,
		const cv::Mat& matTemplate,
		unsigned int maxTry = 10,
		Time time = seconds(1.0f),
		unsigned int threshold = 10
	);

protected:
	std::atomic_bool m_running;
	std::atomic_bool m_askedForStop;

	cv::Mat m_lastFight;
	cv::Mat m_newFight;
	cv::Mat m_start;
	cv::Mat m_result;
	cv::Mat m_loading;
	cv::Mat m_fp;
	cv::Mat m_default;

	wgc::ICapture* r_capture;

	std::queue<ohms::HelperReturnMessage> helperReturnMessage;
	std::mutex mutexHRM;

	HWND m_doaxvv;
	Logger* r_logger;
};

} // namespace ohms
