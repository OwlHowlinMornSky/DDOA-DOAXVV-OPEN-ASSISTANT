/*
*    DDOA-DOAXVV-OPEN-ASSISTANT
*
*     Copyright 2023-2024  Tyler Parret True
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
#include "MatchTemplate.h"

#include <opencv2/opencv.hpp>

namespace {

constexpr int g_nMatchMethod = cv::TM_SQDIFF_NORMED; // opencv match时用的方法。
constexpr bool g_useColorDiff = false; // check函数用的选项。

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

}

namespace ohms {

MatchTemplateInfo::MatchTemplateInfo() :
	isFixed(false),
	thershold(65535) {}

MatchTemplateInfo::MatchTemplateInfo(bool _isFixed, short _thershold, cv::Rect _rect) :
	isFixed(_isFixed),
	thershold(_thershold),
	rect(_rect) {}

MatchTemplate::MatchTemplate(MatchTemplateInfo&& _info) :
	m_info(_info) {}

MatchTemplate::~MatchTemplate() {}

bool MatchTemplate::Match(const cv::Mat& sample) const {
	cv::Mat srcImage; // 输入
	sample(m_info.rect).copyTo(srcImage);

	if (!m_info.isFixed) {
		// 计算match结果的大小
		cv::Size size = srcImage.size() - m_target.size();
		size.width += 1;
		size.height += 1;
		assert(size.height > 0 && size.width > 0);

		cv::Mat resultImage; // match结果
		resultImage.create(size, CV_32FC1);

		cv::matchTemplate(srcImage, m_target, resultImage, g_nMatchMethod); // match

		// 寻找最佳匹配点
		double minValue, maxValue;
		cv::Point minLocation, maxLocation, matchLocation;
		cv::minMaxLoc(resultImage, &minValue, &maxValue, &minLocation, &maxLocation);
		if constexpr (g_nMatchMethod == cv::TM_SQDIFF || g_nMatchMethod == cv::TM_SQDIFF_NORMED)
			matchLocation = minLocation;
		else
			matchLocation = maxLocation;

		// 由匹配点确定匹配区域（相对于原始输入）
		m_lastMatch = cv::Rect(matchLocation + m_info.rect.tl(), m_target.size()); // 保存匹配区域
		sample(m_lastMatch).copyTo(srcImage);
	}

	// 检查最佳区域是否满足阈值
	bool res = check(srcImage, m_target, m_info.thershold / 65536.0f);

#ifdef _DEBUG
	sample.copyTo(srcImage); // 复制原始输入
	if (m_info.isFixed) {
		cv::rectangle(srcImage, m_info.rect, res ? cv::Scalar(0, 255, 0) : cv::Scalar(0, 0, 255), 2, 8, 0); // 蓝线画寻找范围框
	}
	else {
		cv::rectangle(srcImage, m_info.rect, cv::Scalar(255, 0, 0), 2, 8, 0); // 蓝线画寻找范围框
		cv::rectangle(srcImage, m_lastMatch, res ? cv::Scalar(0, 255, 0) : cv::Scalar(0, 0, 255), 2, 8, 0); // 画最佳匹配框（满足阈值为绿，否则为红）
	}
	cv::resize(srcImage, srcImage, srcImage.size() / 2, 0.0, 0.0, cv::InterpolationFlags::INTER_LINEAR); // 缩小到一半
	cv::imshow("show", srcImage); // show
#endif
	return res;
}

bool MatchTemplate::LoadMat(const std::string& file) {
	m_target = cv::imread(file);
	return !m_target.empty();
}

}
