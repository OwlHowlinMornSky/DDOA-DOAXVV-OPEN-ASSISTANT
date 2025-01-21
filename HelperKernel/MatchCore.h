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
#pragma once

#include "IEye.h"

using namespace System::Drawing;

namespace HelperKernel {

public ref class MatchCore {
protected:
	MatchCore();
	virtual ~MatchCore();

public:
	bool IsFloatingArea();

	/**
	 * @brief 获取搜索之区域。
	 * @return 搜索之区域。
	 */
	Rectangle GetSearchRect();
	/**
	 * @brief 获取上次成功匹配时的区域。搜索区域浮动时 该方法才有意义，因为搜索区域固定时 返回值等于搜索区域。
	 * @return 上次成功匹配时的区域。
	 */
	Rectangle GetPreviousMatchedRect();

protected:
	/**
	 * @brief 输入截图画面检查。
	 * @param eye 眼。
	 * @param threshold 通过之阈值，差异度小于该值 即 匹配成功。
	 * @return 匹配是否成功。
	 */
	bool Match(IEye^ eye, float threshold);

	/**
	 * @brief 加载模板Mat。
	 * @param filepath 模板图片文件路径。
	 * @return 加载是否成功。
	 */
	bool LoadPattern(System::String^ filepath);
	/**
	 * @brief 加载遮罩Mat。
	 * @param filepath 遮罩图片文件路径。
	 * @return 加载是否成功。
	 */
	bool LoadMask(System::String^ filepath);

protected:
	bool m_isFloatingArea; // 是否浮动范围查找。
	Rectangle m_searchRect; // 查找之范围。
	Rectangle m_prevMatchedRect; // 上次成功匹配之范围。
	cv::Mat* m_pattern; // 用于匹配之图案。
	cv::Mat* m_mask;   // 用于匹配之遮罩。
};

}
