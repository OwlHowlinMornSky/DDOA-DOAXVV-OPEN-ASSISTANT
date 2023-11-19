#include "Helper.h"

#include "Clock.h"

#define SHOW_WHOLE

namespace {

constexpr int g_nMatchMethod = cv::TM_SQDIFF_NORMED;
constexpr bool g_useColorDiff = false;

inline float matDiffrencePixel(const cv::Mat& matSample, const cv::Mat& matTemplate) {
	assert(matSample.size() == matTemplate.size());
	cv::Mat matResault;
	cv::absdiff(matSample, matTemplate, matResault);
	cv::threshold(matResault, matResault, 48.0, 255.0, cv::ThresholdTypes::THRESH_BINARY);
	cv::cvtColor(matResault, matResault, cv::COLOR_BGR2GRAY);
	return (static_cast<float>(cv::countNonZero(matResault)) / matResault.size().area());
}

inline float matDiffrenceColor(const cv::Mat& matSample, const cv::Mat& matTemplate) {
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

inline bool check(const cv::Mat& matSample, const cv::Mat& matTemplate, float thres) {
	assert(thres > 0.0f && thres < 100.0f);
	assert(matSample.size() == matTemplate.size());
	float diff;
	if constexpr (g_useColorDiff)
		diff = matDiffrenceColor(matSample, matTemplate);
	else
		diff = matDiffrencePixel(matSample, matTemplate);
	return ((diff * 100.0f) < thres);
}

inline bool find(const cv::Mat& matSample, const cv::Mat& matTemplate, cv::Rect& rect, float thres) {
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

	if constexpr (g_nMatchMethod == cv::TM_SQDIFF || g_nMatchMethod == cv::TM_SQDIFF_NORMED)
		matchLocation = minLocation;
	else
		matchLocation = maxLocation;

	cv::Rect r(matchLocation, matTemplate.size());
	bool res = check(srcImage(r), matTemplate, thres);
	if (res) {
		r.x += oldRect.x;
		r.y += oldRect.y;
		rect = r;
	}

#ifdef OHMS_DDOA_SHOW
#ifdef SHOW_WHOLE
	cv::Rect tttrect(matchLocation + oldRect.tl(), matTemplate.size());
	cv::rectangle(srcImage, oldRect, cv::Scalar(255, 0, 0), 2, 8, 0);
	cv::rectangle(srcImage, tttrect, res ? cv::Scalar(0, 255, 0) : cv::Scalar(0, 0, 255), 2, 8, 0);
#else
	cv::rectangle(
		srcImage, cv::Rect(matchLocation, matTemplate.size()),
		res ? cv::Scalar(0, 255, 0) : cv::Scalar(0, 0, 255), 2, 8, 0
	);
#endif
	cv::resize(srcImage, srcImage, { 480, 270 }, 0.0, 0.0, cv::InterpolationFlags::INTER_LINEAR);
	cv::imshow("show", srcImage);
#endif // OHMS_DDOA_SHOW

	return res;
}

}

namespace ohms {

bool ohms::Helper::step_copyMat(cv::Mat& target) {
	if (r_capture->copyMatTo(target, true)) {
		if (target.size().width != 960 || target.size().height != 540) {
			auto sz = target.size();
			cv::resize(
				target, target,
				cv::Size(960, 540),
				0.0, 0.0, cv::InterpolationFlags::INTER_CUBIC
			);
		}
		return true;
	}
	return false;
}

bool Helper::step_waitFor(
	const cv::Mat& matTemplate, const cv::Rect searchRect, cv::Rect& findRect,
	Time maxTime, float thres
) {
	r_capture->askForRefresh();
	bool res = false;
	Clock clk;
	cv::Mat mat;
	cv::Rect trect;
	while (!m_askedForStop) {
#ifdef OHMS_DDOA_SHOW
		if (MSG msg{ 0 };
			PeekMessageW(&msg, NULL, NULL, NULL, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}
		else
#endif // OHMS_DDOA_SHOW
		{
			if (r_capture->isRefreshed()) {
				if (step_copyMat(mat)) {
					trect = searchRect;
					if (find(mat, matTemplate, trect, thres)) {
						findRect = trect;
						break;
					}
				}
			}
			if (maxTime > Time::Zero && clk.getElapsedTime() > maxTime)
				break;
			r_capture->askForRefresh();
			Sleep(30);
		}
	}
	if (m_askedForStop)
		throw 0;
	return res;
}

bool Helper::step_click(cv::Point pt) {
	RECT rect{ 0 };
	GetClientRect(m_doaxvv, &rect);
	pt.x = static_cast<int>(pt.x / 960.0f * (rect.right - rect.left));
	pt.y = static_cast<int>(pt.y / 540.0f * (rect.bottom - rect.top));
	PostMessageW(m_doaxvv, WM_MOUSEMOVE, 0, MAKELPARAM(pt.x, pt.y));
	PostMessageW(m_doaxvv, WM_LBUTTONDOWN, 0, MAKELPARAM(pt.x, pt.y));
	PostMessageW(m_doaxvv, WM_LBUTTONUP, 0, MAKELPARAM(pt.x, pt.y));
	return true;
}

bool Helper::step_move(cv::Point pt) {
	RECT rect{ 0 };
	GetClientRect(m_doaxvv, &rect);
	pt.x = static_cast<int>(pt.x / 960.0f * (rect.right - rect.left));
	pt.y = static_cast<int>(pt.y / 540.0f * (rect.bottom - rect.top));
	PostMessageW(m_doaxvv, WM_MOUSEMOVE, 0, MAKELPARAM(pt.x, pt.y));
	return true;
}

bool Helper::step_keepClickingUntil(
	const cv::Point clkPt, const cv::Mat& matTemplate, const cv::Rect searchRect,
	Time maxTime, Time clkTime, float thres
) {
	if (clkTime < Time::Zero)
		clkTime = milliseconds(1000);
	unsigned int tried = 0;
	cv::Rect trect;
	Clock clock;
	do {
		if (maxTime > Time::Zero && clock.getElapsedTime() >= maxTime)
			return false;
		step_click(clkPt);
	} while (!m_askedForStop && !step_waitFor(matTemplate, searchRect, trect, clkTime, thres));
	if (m_askedForStop)
		throw 0;
	return true;
}

void Helper::step_subtaskError(std::wstring_view str) {
	r_logger->addString(L" ");
	r_logger->addString(std::wstring(L"任务出错: ").append(str));
	m_askedForStop = true;
	MessageBoxW(NULL, str.data(), L"DOAXVV-helper: Task Error", MB_ICONERROR);
	throw 0;
}

} // namespace ohms
