#pragma once

#include "IHelper.h"
#include <mutex>
#include <atomic>
#include "Clock.h"
#include "Rect.h"

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

	bool step_waitFor(
		bool find,
		const cv::Mat& temp,
		Rect& rect,
		Time maxTime,
		int threshold
	);
	bool step_check(
		const cv::Mat& mat,
		const cv::Mat& Mat,
		int threshold
	);
	bool step_find(
		const cv::Mat& mat,
		const cv::Mat& Mat,
		Rect& rect,
		int threshold
	);
	bool step_moveCursorTo(Point pt, Time time);
	bool step_click(Point pt);
	bool keepClickingUntil(
		Point pt,
		Rect rect,
		const cv::Mat& mat,
		int maxTry,
		Time time,
		int threshold
	);

protected:
	std::atomic_bool m_running;
	std::atomic_bool m_askedForStop;
};

}
