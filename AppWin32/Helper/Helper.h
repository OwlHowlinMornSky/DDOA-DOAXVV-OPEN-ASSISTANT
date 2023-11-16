#pragma once

#include "IHelper.h"
#include <mutex>
#include <atomic>
#include "Clock.h"
#include <opencv2/opencv.hpp>

namespace ohms {

class Helper final :
	public IHelper {
public:
	Helper();
	virtual ~Helper() override;

public:
	virtual bool start() override;
	virtual void askForStop() override;
	virtual bool isRunning() override;

protected:
	/**
	 * @brief 运行在子线程的任务。
	*/
	void work();

	/**
	 * @brief 子任务：作战。
	*/
	void subwork_fight();

public:
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
	cv::Mat m_start;
	cv::Mat m_result;
	cv::Mat m_loading;
	cv::Mat m_fp;
	cv::Mat m_default;
};

}
