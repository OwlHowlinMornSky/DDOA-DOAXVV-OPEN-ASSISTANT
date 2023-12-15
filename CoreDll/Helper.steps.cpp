#include "Helper.h"

#include "Clock.h"

namespace {

constexpr int g_nMatchMethod = cv::TM_SQDIFF_NORMED; // opencv match时用的方法。
constexpr bool g_useColorDiff = false; // check函数用的选项。

bool g_showcv = false;
bool g_showopened = false;
std::mutex g_showcvMutex;

/**
 * @brief 比较两个mat，按超过阈值的像素数。
 * @param matSample 输入
 * @param matTemplate 模板
 * @return 差异程度（0~1）。
*/
inline float matDiffrencePixel(const cv::Mat& matSample, const cv::Mat& matTemplate) {
	assert(matSample.size() == matTemplate.size()); // 确保两个mat大小一致。
	cv::Mat matResault;
	cv::absdiff(matSample, matTemplate, matResault); // 计算绝对差
	cv::threshold(matResault, matResault, 48.0, 255.0, cv::ThresholdTypes::THRESH_BINARY); // 阈值
	cv::cvtColor(matResault, matResault, cv::COLOR_BGR2GRAY); // 转换为灰度
	return (static_cast<float>(cv::countNonZero(matResault)) / matResault.size().area()); // 不为黑色的像素数 除以 面积
}
/**
 * @brief 比较两个mat，按超过阈值的像素颜色。
 * @param matSample 输入
 * @param matTemplate 模板
 * @return 差异程度（0~1）.
*/
inline float matDiffrenceColor(const cv::Mat& matSample, const cv::Mat& matTemplate) {
	assert(matSample.size() == matTemplate.size()); // 确保两个mat大小一致。
	cv::Mat matResault;
	cv::absdiff(matSample, matTemplate, matResault); // 计算绝对差值。
	cv::threshold(matResault, matResault, 32.0, 255.0, cv::ThresholdTypes::THRESH_BINARY); // 阈值
	cv::cvtColor(matResault, matResault, cv::COLOR_BGR2GRAY); // 转为灰度
	float res = 0.0f;
	// 把灰度值全部加起来
	for (cv::MatIterator_<unsigned char> i = matResault.begin<unsigned char>(),
		 n = matResault.end<unsigned char>(); i != n; ++i) {
		res += static_cast<float>(*i);
	}
	return (res / 255.0f / matResault.size().area()); // 灰度 除以 255（最大值） 再除以 面积
}

/**
 * @brief 判断两个mat差异是否在规定阈值内
 * @param matSample 输入
 * @param matTemplate 模板
 * @param thres 差异阈值
 * @return 差异程度小于阈值则为true（即足够相似）
*/
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

/**
 * @brief 在“输入”中寻找“模板”，找到则把区域输出到“寻找范围”
 * @param matSample 输入
 * @param matTemplate 模板
 * @param rect 寻找范围，作用于“输入”，为空则限定为整个“输入”。返回true时会保存找到的区域
 * @param thres 阈值
 * @return “输入”中存在一个区域与“模板”的差异小于阈值则为true
*/
inline bool find(const cv::Mat& matSample, const cv::Mat& matTemplate, cv::Rect& rect, float thres) {
	cv::Rect oldRect; // 查找范围
	cv::Mat srcImage; // 输入

	// rect不为0则裁剪。
	if (rect.size().area() > 0) {
		oldRect = rect;
		matSample(oldRect).copyTo(srcImage);
	}
	else {
		matSample.copyTo(srcImage);
	}

	// 计算match结果的大小
	cv::Size size = srcImage.size() - matTemplate.size();
	size.width += 1;
	size.height += 1;
	assert(size.height > 0 && size.width > 0);

	cv::Mat resultImage; // match结果
	resultImage.create(size, CV_32FC1);

	cv::matchTemplate(srcImage, matTemplate, resultImage, g_nMatchMethod); // match

	// 寻找最佳匹配点
	double minValue, maxValue;
	cv::Point minLocation, maxLocation, matchLocation;
	cv::minMaxLoc(resultImage, &minValue, &maxValue, &minLocation, &maxLocation);
	if constexpr (g_nMatchMethod == cv::TM_SQDIFF || g_nMatchMethod == cv::TM_SQDIFF_NORMED)
		matchLocation = minLocation;
	else
		matchLocation = maxLocation;

	// 由匹配点确定匹配区域（相对于原始输入）
	cv::Rect r(matchLocation + oldRect.tl(), matTemplate.size());

	// 检查最佳区域是否满足阈值
	bool res = check(matSample(r), matTemplate, thres);
	if (res) rect = r; // 保存到rect

	std::lock_guard lg(g_showcvMutex);
	if (g_showcv) {
		matSample.copyTo(srcImage); // 复制原始输入
		cv::rectangle(srcImage, oldRect, cv::Scalar(255, 0, 0), 2, 8, 0); // 蓝线画寻找范围框
		cv::rectangle(srcImage, r, res ? cv::Scalar(0, 255, 0) : cv::Scalar(0, 0, 255), 2, 8, 0); // 画最佳匹配框（满足阈值为绿，否则为红）
		cv::resize(srcImage, srcImage, srcImage.size() / 2, 0.0, 0.0, cv::InterpolationFlags::INTER_LINEAR); // 缩小到一般
		g_showopened = true;
		cv::imshow("show", srcImage); // show
	}
#ifndef _DEBUG
	else if (g_showopened) { // Release 时自动关闭 OpenCV 窗口
		cv::destroyAllWindows();
	}
#endif
	return res;
}

}

namespace ohms {

void Helper::regShowCV(bool show) {
	std::lock_guard lg(g_showcvMutex);
	g_showcv = show;
}

bool Helper::step_copyMat(cv::Mat& target) {
	if (r_capture->isRefreshed()) { // refresh过再处理画面才有意义
		if (r_capture->copyMatTo(target, true)) { // 要求转换为BGR
			if (target.size().width != 960 || target.size().height != 540) { // 确保大小满足要求
				auto sz = target.size();
				cv::resize(
					target, target,
					cv::Size(960, 540),
					0.0, 0.0, cv::InterpolationFlags::INTER_LINEAR
				); // 双线性缩放
			}
			return true;
		}
	}
	return false;
}

bool Helper::step_waitFor(
	const cv::Mat& matTemplate, const cv::Rect searchRect, cv::Rect& findRect,
	Time maxTime, float thres
) {
	r_capture->askForRefresh();
	Clock clk;
	cv::Mat mat;
	cv::Rect trect;
	MSG msg{ 0 };
	while (!m_askedForStop) {
		// show mat时必须处理该线程的窗口消息，cv的窗口才正常
		// 没有show mat时也必须处理消息，否则收不到capture到的帧（似乎是分离线程初始化wgc导致的
		if (PeekMessageW(&msg, NULL, NULL, NULL, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}
		else {
			if (step_copyMat(mat)) {
				trect = searchRect;
				if (find(mat, matTemplate, trect, thres)) {
					findRect = trect;
					break;
				}
			}
			if (maxTime > Time::Zero && clk.getElapsedTime() > maxTime) // 应用超时
				return false;
			r_capture->askForRefresh();
			Sleep(30);
		}
	}
	if (m_askedForStop) // throw 0 表示停止
		throw 0;
	return true;
}

bool Helper::step_click(cv::Point pt) {
	// 缩放到当前客户区大小
	RECT rect{ 0 };
	GetClientRect(m_doaxvv, &rect);
	pt.x = static_cast<int>(pt.x / 960.0f * (rect.right - rect.left));
	pt.y = static_cast<int>(pt.y / 540.0f * (rect.bottom - rect.top));

	if (task_Mouse_ForMouse) {
		GetWindowRect(m_doaxvv, &rect);

		//获取可用桌面大小
		RECT sc{ 0 };
		SystemParametersInfoW(SPI_GETWORKAREA, 0, &sc, 0);
		if (rect.right > sc.right)
			rect.left -= rect.right - sc.right;
		if (rect.left < sc.left)
			rect.left = sc.left;
		if (rect.bottom > sc.bottom)
			rect.top -= rect.bottom - sc.bottom;
		if (rect.top < sc.top)
			rect.top = sc.top;
		SetWindowPos(m_doaxvv, NULL, rect.left, rect.top, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOACTIVATE);

		POINT p{ pt.x, pt.y };
		ClientToScreen(m_doaxvv, &p);

		p.x = p.x * 65535ll / 1920;
		p.y = p.y * 65535ll / 1080;

		pt.x = static_cast<int>(pt.x / 960.0f * (rect.right - rect.left));
		pt.y = static_cast<int>(pt.y / 540.0f * (rect.bottom - rect.top));

		INPUT inputs[3] = {};
		ZeroMemory(inputs, sizeof(inputs));

		inputs[0].type = INPUT_MOUSE;
		inputs[0].mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
		inputs[0].mi.dx = p.x;
		inputs[0].mi.dy = p.y;

		inputs[1].type = INPUT_MOUSE;
		inputs[1].mi.dwFlags = MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_ABSOLUTE;
		inputs[1].mi.dx = p.x;
		inputs[1].mi.dy = p.y;

		inputs[2].type = INPUT_MOUSE;
		inputs[2].mi.dwFlags = MOUSEEVENTF_LEFTUP | MOUSEEVENTF_ABSOLUTE;
		inputs[2].mi.dx = p.x;
		inputs[2].mi.dy = p.y;

		UINT uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
		if (uSent != ARRAYSIZE(inputs)) {
			;
			//OutputString(L"SendInput failed: 0x%x\n", HRESULT_FROM_WIN32(GetLastError()));
		}
	}
	else {
		// 发送消息单击
		PostMessageW(m_doaxvv, WM_SETFOCUS, 0, 0);
		PostMessageW(m_doaxvv, WM_MOUSEMOVE, 0, MAKELPARAM(pt.x, pt.y));
		PostMessageW(m_doaxvv, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(pt.x, pt.y));
		PostMessageW(m_doaxvv, WM_LBUTTONUP, 0, MAKELPARAM(pt.x, pt.y));
	}
	return true;
}

bool Helper::step_move(cv::Point pt) {
	// 缩放到当前客户区大小
	RECT rect{ 0 };
	GetClientRect(m_doaxvv, &rect);
	pt.x = static_cast<int>(pt.x / 960.0f * (rect.right - rect.left));
	pt.y = static_cast<int>(pt.y / 540.0f * (rect.bottom - rect.top));

	// 发送消息移动光标
	PostMessageW(m_doaxvv, WM_SETFOCUS, 0, 0);
	PostMessageW(m_doaxvv, WM_MOUSEMOVE, 0, MAKELPARAM(pt.x, pt.y));
	return true;
}

bool Helper::step_keepClickingUntil(
	const cv::Point clkPt, const cv::Mat& matTemplate, const cv::Rect searchRect,
	Time maxTime, Time clkTime, float thres
) {
	if (clkTime < milliseconds(10)) // 点击时间不能小于10毫秒（规定的）
		clkTime = milliseconds(10);
	cv::Rect rect;
	Clock clock;
	do {
		if (maxTime > Time::Zero && clock.getElapsedTime() >= maxTime) // 应用超时
			return false;
		step_click(clkPt); // 点击
	} while (!m_askedForStop && !step_waitFor(matTemplate, searchRect, rect, clkTime, thres));
	if (m_askedForStop)
		throw 0;
	return true;
}

void Helper::step_subtaskError(unsigned long type) {
	msgPush(HelperReturnMessage::Log_ErrorInTask, type);
	throw 0; // 要求停止
}

} // namespace ohms
