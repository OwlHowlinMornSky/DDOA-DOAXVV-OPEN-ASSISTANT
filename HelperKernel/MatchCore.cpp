#include "MatchCore.h"

#include <opencv2/imgproc.hpp>

namespace {

constexpr int g_nMatchMethod = cv::TM_SQDIFF_NORMED; // opencv match时用的方法。
constexpr bool g_useColorDiff = false; // check函数用的选项。

/**
 * @brief 比较两个mat，按超过阈值的像素数。
 * @param matSample 输入
 * @param matTemplate 模板
 * @return 差异程度（需要除以有效面积再使用）。
*/
inline float matDiffrencePixel(const cv::Mat& matSample, const cv::Mat& matTemplate) {
	assert(matSample.size() == matTemplate.size()); // 确保两个mat大小一致。
	cv::Mat matResault;
	cv::absdiff(matSample, matTemplate, matResault); // 计算绝对差
	cv::threshold(matResault, matResault, 48.0, 255.0, cv::ThresholdTypes::THRESH_BINARY); // 阈值
	cv::cvtColor(matResault, matResault, cv::COLOR_BGR2GRAY); // 转换为灰度
	return (static_cast<float>(cv::countNonZero(matResault))); // 不为黑色的像素数
}
/**
 * @brief 比较两个mat，按超过阈值的像素颜色。
 * @param matSample 输入
 * @param matTemplate 模板
 * @return 差异程度（需要除以有效面积再使用）.
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
	return (res / 255.0f); // 灰度 除以 255（最大值）
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
		diff = matDiffrenceColor(matSample, matTemplate) / matTemplate.size().area(); // 额外除以面积计算比例
	else
		diff = matDiffrencePixel(matSample, matTemplate) / matTemplate.size().area();
	return (diff < thres);
}

inline bool checkWithMask(const cv::Mat& matSample, const cv::Mat& matTemplate, const cv::Mat& matMask, float thres) {
	assert(thres > 0.0f && thres < 100.0f);
	assert(matSample.size() == matTemplate.size());
	float diff;
	if constexpr (g_useColorDiff)
		diff = matDiffrenceColor(matSample, matTemplate) / cv::countNonZero(matMask); // 额外除以遮罩有效面积计算比例
	else
		diff = matDiffrencePixel(matSample, matTemplate) / cv::countNonZero(matMask);
	return (diff < thres);
}

}

namespace HelperKernel {

MatchCore::MatchCore() {
	throw gcnew System::NotImplementedException();
}

MatchCore::~MatchCore() {
	if (m_target) delete m_target;
	m_target = nullptr;
	if (m_mask) delete m_mask;
	m_mask = nullptr;
}

bool MatchCore::Match(IEye^ eye, float threshold) {
	const cv::Mat* vision = eye->GetVision();
	if (nullptr == vision) return false;
	const cv::Mat& sample = *vision;

	cv::Mat srcImage; // 输入
	cv::Rect searchRect(m_searchRect.X, m_searchRect.Y, m_searchRect.Width, m_searchRect.Height);

	if (nullptr != m_mask) {
		sample(searchRect).copyTo(srcImage, *m_mask);
	}
	else {
		sample(searchRect).copyTo(srcImage);
	}

	if (m_isFloatingArea) {
		cv::Size targetSize = m_target->size();
		// 计算match结果的大小
		cv::Size size = srcImage.size() - targetSize;
		size += { 1, 1 };
		assert(size.height > 0 && size.width > 0);

		cv::Mat resultImage; // match结果
		resultImage.create(size, CV_32FC1);

		cv::matchTemplate(srcImage, *m_target, resultImage, g_nMatchMethod); // match

		// 寻找最佳匹配点
		double minValue, maxValue;
		cv::Point minLocation, maxLocation, matchLocation;
		cv::minMaxLoc(resultImage, &minValue, &maxValue, &minLocation, &maxLocation);
		if constexpr (g_nMatchMethod == cv::TM_SQDIFF || g_nMatchMethod == cv::TM_SQDIFF_NORMED)
			matchLocation = minLocation;
		else
			matchLocation = maxLocation;

		// 由匹配到的点确定匹配到的区域（相对于原始输入）
		cv::Rect prevMatch = cv::Rect(matchLocation + searchRect.tl(), targetSize);
		sample(prevMatch).copyTo(srcImage);

		m_prevMatchedRect = Drawing::Rectangle(prevMatch.x, prevMatch.y, prevMatch.width, prevMatch.height);
	}
	else {
		m_prevMatchedRect = m_searchRect;
	}

	// 检查最佳区域是否满足阈值
	bool res =
		(nullptr != m_mask)
		?
		checkWithMask(srcImage, *m_target, *m_mask, threshold)
		:
		check(srcImage, *m_target, threshold)
		;
	return res;

	return false;
}

bool MatchCore::IsFloatingArea() {
	return m_isFloatingArea;
}

Drawing::Rectangle MatchCore::GetSearchRect() {
	return m_searchRect;
}

Drawing::Rectangle MatchCore::GetPreviousMatchedRect() {
	return m_prevMatchedRect;
}

}
