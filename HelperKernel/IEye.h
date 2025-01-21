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

#include <opencv2/core/mat.hpp>

namespace HelperKernel {

/**
 * @brief 眼。
 */
public interface class IEye {
public:
	/**
	 * @brief 要求刷新视野。
	 */
	void RequireRefresh();
	/**
	 * @brief 把视野内容保存。
	 * @return 获得了新的内容则为 true，否则内容未刷新 返回 false。
	 */
	bool SaveVision();
	/**
	 * @brief 获取当前的视野。
	 * @return 当前视野，可能为nullptr（即没有视野）。
	 */
	const cv::Mat* GetVision();
	/**
	 * @brief 检查是否正在观察。
	 * @return 是否正在观察。
	 */
	bool IsLooking();

	void BeginDebugDraw();
	void DrawRectangle(System::Drawing::Rectangle rect, System::Drawing::Color color);
	void ShowDebugWindow();
	void DestroyDebugWindows();
};

}
