#include "Helper.h"

#include "../Global.h"
#include <opencv2/opencv.hpp>

#include <thread>
#include <iostream>

namespace ohms {

bool Helper::step_waitFor(
	bool find,
	const cv::Mat& temp,
	Rect& rect,
	Time maxTime,
	int threshold
) {
	ohms::global::capture->askForRefresh();
	if (!find) {
		rect.size.x = temp.size().width;
		rect.size.y = temp.size().height;
	}
	bool res = false;
	Clock clk;
	while (!m_askedForStop) {
#ifdef _DEBUG
		MSG msg{ 0 };
		if (PeekMessageW(&msg, NULL, NULL, NULL, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}
		else
#endif // )DEBUG
		{
			if (ohms::global::capture->isRefreshed()) {
				cv::Mat mat;
				if (ohms::global::capture->copyMat(mat)) {
#ifdef _DEBUG
					cv::imshow("show", mat);
#endif // _DEBUG
					Rect trect = rect;
					// 用 rect 裁剪
					res = find ?
						step_find(mat, temp, trect, threshold) :
						step_check(mat, temp, threshold);
					if (res) {
						if (find)
							rect = trect;
						break;
					}
				}
			}
			if (clk.getElapsedTime() > maxTime) {
				break;
			}
			ohms::global::capture->askForRefresh();
			Sleep(30);
		}
	}
	return res;
}

bool Helper::step_check(
	const cv::Mat& mat,
	const cv::Mat& Mat,
	int threshold
) {
	return false;
}

bool Helper::step_find(
	const cv::Mat& mat,
	const cv::Mat& Mat,
	Rect& rect,
	int threshold
) {
	return false;
}

bool Helper::step_moveCursorTo(Point pt, Time time) {
	return false;
}

bool Helper::step_click(Point pt) {
	return false;
}

bool Helper::keepClickingUntil(
	Point pt,
	Rect rect,
	const cv::Mat& mat,
	int maxTry,
	Time time,
	int threshold
) {
	int tried = 0;
	do {
		if (tried >= maxTry)
			return false;
		tried++;
		step_click(pt);
	} while (!step_waitFor(false, mat, rect, seconds(1.0f), threshold));
	return true;
}

}
