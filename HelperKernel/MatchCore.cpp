/*
*    DDOA-DOAXVV-OPEN-ASSISTANT
*
*     Copyright 2023-2025  Tyler Parret True
*
*    Licensed under the Apache License, Version 2.0 (the "License");
*    you may not use this file except in compliance with the License.
*    You may obtain a copy of the License at
*
*        http://www.apache.org/licenses/LICENSE-2.0
*
*    Unless required by applicable law or agreed to in writing, software
*    distributed under the License is distributed on an "AS IS" BASIS,
*    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*    See the License for the specific language governing permissions and
*    limitations under the License.
*
* @Authors
*    Tyler Parret True <mysteryworldgod@outlook.com><https://github.com/OwlHowlinMornSky>
*/
#include "MatchCore.h"

#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>

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

/**
 * @brief 判断两个mat差异是否在规定阈值内，将把遮罩应用于输入
 * @param matSample 输入
 * @param matTemplate 模板
 * @param matMask 遮罩
 * @param thres 差异阈值
 * @return 遮罩范围外 差异程度小于阈值则为true（即足够相似）
 */
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

MatchCore::MatchCore() :
	m_isFloatingArea(false),
	m_searchRect(),
	m_prevMatchedRect(),
	m_pattern(nullptr),
	m_mask(nullptr) {}

MatchCore::~MatchCore() {
	if (m_pattern) delete m_pattern;
	m_pattern = nullptr;
	if (m_mask) delete m_mask;
	m_mask = nullptr;
}

bool MatchCore::Match(IEye^ eye, float threshold) {
	const cv::Mat* vision = eye->GetVision();
	if (nullptr == vision) return false;
	const cv::Mat& sample = *vision;

	cv::Mat srcImage; // 输入
	cv::Rect searchRect(m_searchRect.X, m_searchRect.Y, m_searchRect.Width, m_searchRect.Height);

	switch ((m_isFloatingArea ? 2 : 0) | (m_mask ? 1 : 0)) {
	case 0: // 无遮罩的固定区域。
		sample(searchRect).copyTo(srcImage);
		m_prevMatchedRect = m_searchRect;
		return check(srcImage, *m_pattern, threshold); // 检查区域是否满足阈值
	case 1: // 有遮罩的固定区域。
		sample(searchRect).copyTo(srcImage, *m_mask);
		m_prevMatchedRect = m_searchRect;
		return checkWithMask(srcImage, *m_pattern, *m_mask, threshold); // 检查区域是否满足阈值
	case 2: // 无遮罩的浮动区域。
		sample(searchRect).copyTo(srcImage);
		{
			cv::Size targetSize = m_pattern->size();
			// 计算match结果的大小
			cv::Size size = srcImage.size() - targetSize;
			size += { 1, 1 };
			assert(size.height > 0 && size.width > 0);

			cv::Mat resultImage; // match结果
			resultImage.create(size, CV_32FC1);
			cv::matchTemplate(srcImage, *m_pattern, resultImage, g_nMatchMethod); // match

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

			m_prevMatchedRect = Rectangle(prevMatch.x, prevMatch.y, prevMatch.width, prevMatch.height);
		}
		return check(srcImage, *m_pattern, threshold); // 检查最佳区域是否满足阈值
	case 3: // 有遮罩的浮动区域。
		sample(searchRect).copyTo(srcImage);
		{
			cv::Size targetSize = m_pattern->size();
			// 计算match结果的大小
			cv::Size size = srcImage.size() - targetSize;
			size += { 1, 1 };
			assert(size.height > 0 && size.width > 0);

			cv::Mat resultImage; // match结果
			resultImage.create(size, CV_32FC1);
			cv::matchTemplate(srcImage, *m_pattern, resultImage, g_nMatchMethod, m_mask ? *m_mask : cv::noArray()); // match

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

			m_prevMatchedRect = Rectangle(prevMatch.x, prevMatch.y, prevMatch.width, prevMatch.height);
		}
		// 检查最佳区域是否满足阈值
		return checkWithMask(srcImage, *m_pattern, *m_mask, threshold);
	default:
		break;
	}
	return false;
}

bool MatchCore::IsFloatingArea() {
	return m_isFloatingArea;
}

Rectangle MatchCore::GetSearchRect() {
	return m_searchRect;
}

Rectangle MatchCore::GetPreviousMatchedRect() {
	return m_prevMatchedRect;
}

bool MatchCore::LoadPattern(System::String^ filepath) {
	if (m_pattern) delete m_pattern;

	cli::array<wchar_t>^ wArray = filepath->ToCharArray();
	cli::array<unsigned char, 1>^ arr = System::Text::Encoding::UTF8->GetBytes(wArray);

	int len = arr->Length;
	char* cstr = new char[len + 2];
	System::IntPtr pcstr(cstr);
	System::Runtime::InteropServices::Marshal::Copy(arr, 0, pcstr, len);
	cstr[len] = 0;
	cstr[len + 1] = 0;

	m_pattern = new cv::Mat(cv::imread(cstr));
	if (m_pattern->empty())
		return false;
	if (!m_isFloatingArea) {
		m_searchRect.Width = m_pattern->size().width;
		m_searchRect.Height = m_pattern->size().height;
	}

	if (m_mask && (m_pattern->size() != m_mask->size())) {
		return false;
	}
	return true;
}

bool MatchCore::LoadMask(System::String^ filepath) {
	if (m_mask) delete m_mask;

	cli::array<wchar_t>^ wArray = filepath->ToCharArray();
	cli::array<unsigned char, 1>^ arr = System::Text::Encoding::UTF8->GetBytes(wArray);

	int len = arr->Length;
	char* cstr = new char[len + 2];
	System::IntPtr pcstr(cstr);
	System::Runtime::InteropServices::Marshal::Copy(arr, 0, pcstr, len);
	cstr[len] = 0;
	cstr[len + 1] = 0;

	m_mask = new cv::Mat(cv::imread(cstr, cv::IMREAD_GRAYSCALE));
	if (m_mask->empty())
		return false;

	if (m_pattern && (m_pattern->size() != m_mask->size())) {
		return false;
	}
	return true;
}

}
