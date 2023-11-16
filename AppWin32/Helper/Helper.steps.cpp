#include "Helper.h"

#include "../Global.h"

#include <thread>
#include <iostream>

namespace {

float matDiffrencePixel(const cv::Mat& matSample, const cv::Mat& matTemplate) {
	assert(matSample.size() == matTemplate.size());
	cv::Mat matResault;
	cv::absdiff(matSample, matTemplate, matResault);
	cv::threshold(matResault, matResault, 48.0, 255.0, cv::ThresholdTypes::THRESH_BINARY);
	cv::cvtColor(matResault, matResault, cv::COLOR_BGR2GRAY);
	return (static_cast<float>(cv::countNonZero(matResault)) / matResault.size().area());
}

float matDiffrenceColor(const cv::Mat& matSample, const cv::Mat& matTemplate) {
	assert(matSample.size() == matTemplate.size());
	cv::Mat matResault;
	cv::absdiff(matSample, matTemplate, matResault);
	cv::threshold(matResault, matResault, 32.0, 255.0, cv::ThresholdTypes::THRESH_BINARY);
	cv::cvtColor(matResault, matResault, cv::COLOR_BGR2GRAY);
	float res = 0.0f;
	for (cv::MatIterator_<unsigned char> i = matResault.begin<unsigned char>(),
		 n = matResault.end<unsigned char>(); i != n; ++i) {
		res += static_cast<float>(*i);
	}
	return (res / 255.0f / matResault.size().area());
}

int g_nMatchMethod = cv::TM_SQDIFF_NORMED;

}

namespace ohms {

bool Helper::step_waitFor(
	bool find,
	const cv::Mat& matTemplate,
	cv::Rect& rect,
	Time maxTime,
	unsigned int threshold
) {
	ohms::global::capture->askForRefresh();
	if (!find) {
		rect.width = matTemplate.size().width;
		rect.height = matTemplate.size().height;
	}
	bool res = false;
	Clock clk;
	while (!m_askedForStop) {
		if (MSG msg{ 0 };
#ifndef _DEBUG
			ohms::global::show && 
#endif // !_DEBUG
			PeekMessageW(&msg, NULL, NULL, NULL, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}
		else
		{
			if (ohms::global::capture->isRefreshed()) {
				cv::Mat mat;
				if (ohms::global::capture->copyMat(mat)) {
					cv::Rect trect = rect;
					if (find) {
						res = step_find(mat, matTemplate, trect, threshold);
					}
					else {
						res = step_check(mat(trect), matTemplate, threshold);
					}
					if (res) {
						if (find)
							rect = trect;
						break;
					}
				}
			}
			if (maxTime > Time::Zero && clk.getElapsedTime() > maxTime) {
				break;
			}
			ohms::global::capture->askForRefresh();
			Sleep(30);
		}
	}
	return res || m_askedForStop;
}

bool Helper::step_check(
	const cv::Mat& matSample,
	const cv::Mat& matTemplate,
	unsigned int threshold
) {
	assert(threshold < 100);
	assert(matSample.size() == matTemplate.size());

	float diff = matDiffrencePixel(matSample, matTemplate);
	//float diff = matDiffrenceColor(matSample, matTemplate);
	//std::cout << "diff: " << diff * 100.0 << "% " << std::endl;

	return ((diff * 100.0f) < threshold);
}

bool Helper::step_find(
	const cv::Mat& matSample,
	const cv::Mat& matTemplate,
	cv::Rect& rect,
	unsigned int threshold
) {
	cv::Rect oldRect;
	cv::Mat srcImage;
	if (rect.size().area() > 0) {
		oldRect = rect;
		matSample(oldRect).copyTo(srcImage);
	}
	else {
		matSample.copyTo(srcImage);
	}

	cv::Size size = srcImage.size() - matTemplate.size();
	size.width += 1;
	size.height += 1;
	assert(size.height > 0 && size.width > 0);

	cv::Mat resultImage;
	resultImage.create(size, CV_32FC1);

	cv::matchTemplate(srcImage, matTemplate, resultImage, g_nMatchMethod);

	double minValue, maxValue;
	cv::Point minLocation, maxLocation, matchLocation;
	cv::minMaxLoc(resultImage, &minValue, &maxValue, &minLocation, &maxLocation);

	if (g_nMatchMethod == cv::TM_SQDIFF || g_nMatchMethod == cv::TM_SQDIFF_NORMED)
		matchLocation = minLocation;
	else
		matchLocation = maxLocation;

	cv::Rect r(matchLocation, matTemplate.size());
	bool res = step_check(srcImage(r), matTemplate, threshold);
	if (res) {
		r.x += oldRect.x;
		r.y += oldRect.y;
		rect = r;
	}

#ifndef _DEBUG
	if (ohms::global::show)
#endif
	{
		cv::rectangle(
			srcImage,
			matchLocation,
			cv::Point(matchLocation.x + matTemplate.cols, matchLocation.y + matTemplate.rows),
			cv::Scalar(0, 0, 255),
			2, 8, 0
		);
		cv::imshow("show", srcImage);
	}

	return res;
}

bool Helper::step_click(cv::Point pt) {
	RECT rect{ 0 };
	GetClientRect(ohms::global::doaxvv, &rect);
	pt.x = static_cast<int>(pt.x / 960.0f * (rect.right - rect.left));
	pt.y = static_cast<int>(pt.y / 540.0f * (rect.bottom - rect.top));
	PostMessageW(ohms::global::doaxvv, WM_MOUSEMOVE, 0, MAKELPARAM(pt.x, pt.y));
	PostMessageW(ohms::global::doaxvv, WM_LBUTTONDOWN, 0, MAKELPARAM(pt.x, pt.y));
	PostMessageW(ohms::global::doaxvv, WM_LBUTTONUP, 0, MAKELPARAM(pt.x, pt.y));
	return true;
}

bool Helper::keepClickingUntil(
	cv::Point pt,
	cv::Rect rect,
	const cv::Mat& matTemplate,
	unsigned int maxTry,
	Time time,
	unsigned int threshold
) {
	if (time < Time::Zero)
		time = milliseconds(1000);
	unsigned int tried = 0;
	cv::Rect oldRect = rect;
	do {
		if (m_askedForStop)
			break;
		if (maxTry > 0 && tried >= maxTry)
			return false;
		tried++;
		step_click(pt);
		rect = oldRect;
	} while (!m_askedForStop && !step_waitFor(true, matTemplate, rect, time, threshold));
	return true;
}

}
