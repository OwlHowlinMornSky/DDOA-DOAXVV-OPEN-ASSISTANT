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
#pragma once

#include <map>
#include <opencv2/core/types.hpp>
#include <opencv2/core/mat.hpp>

namespace ohms {

struct MatchTemplateInfo {
	bool isFixed; // 是否为固定区域检查（true则为固定区域检查，false则为广阔范围搜索）。
	unsigned short thershold; // 判定阈值，差异量上限。
	cv::Rect rect; // 检查范围（固定检查时左上指定位置，大小取决于mat；范围搜索时即范围，必须比mat大）。

	MatchTemplateInfo();
	MatchTemplateInfo(bool _isFixed, unsigned short _thershold, cv::Rect&& _rect);
};

typedef std::map<std::string, MatchTemplateInfo> TemplateListType;

class MatchTemplate final {
public:
	MatchTemplate(const MatchTemplateInfo& _info);
	MatchTemplate(MatchTemplateInfo&& _info);
	~MatchTemplate();

public:
	/**
	 * @brief 输入截图画面检查。
	 * @param sample 截图画面。
	 * @return 检查通过则为 true。
	 */
	bool Match(const cv::Mat& sample) const;

	/**
	 * @brief 加载模板Mat。
	 * @param file 模板文件名。
	 * @return 加载是否成功。
	 */
	bool LoadMat(const std::string& file);

	const cv::Rect& GetLastMatchRect() const;

private:
	MatchTemplateInfo m_info;
	mutable cv::Rect m_lastMatch;
	cv::Mat m_target;
};

}
