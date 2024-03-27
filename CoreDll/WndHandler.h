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

#include <ohms/WGC.h>
#include <opencv2/opencv.hpp>

#include "MatchTemplate.h"
#include <array>

#include "Time.h"

namespace ohms {

class WndHandler {
public:
	enum class SetReturnValue {
		OK = 0,
		WndNotFound,
		CaptureFailed
	};
	enum class StateValue {
		Idle = 0,
		Launcher,
		Game
	};

public:
	WndHandler();
	virtual ~WndHandler();

public:
	void Update();

	SetReturnValue SetForLaucher();
	SetReturnValue SetForGame();
	void Reset();
	StateValue GetState() const;

	int WaitFor(const MatchTemplate& _temp, Time _tlimit);
	int WaitForMultiple(std::vector<const MatchTemplate*> _temps, Time _tlimit);

	/**
	 * @brief 单击。范围是统一尺寸（960 540），自动缩放到当前DOAXVV大小
	 * @param pt 位置
	 * @return 未使用
	*/
	virtual bool ClickAt(cv::Point pt) = 0;
	/**
	 * @brief 移动光标。范围是统一尺寸（960 540），自动缩放到当前DOAXVV大小
	 * @param pt 位置
	 * @return 未使用
	*/
	virtual bool MoveMouseTo(cv::Point pt) = 0;

protected:
	/**
	 * @brief 从capture复制mat，同时检查capture是否refresh，顺便resize到统一尺寸（960 540）。
	 * @param target 保存mat的位置
	 * @return capture已refresh并复制成功则为true，未refresh返回false，复制失败返回false
	*/
	bool CopyMat(cv::Mat& target);

private:
	HWND m_hwnd; // 窗口句柄
	StateValue m_state;
	wgc::ICapture* r_capture; // capture索引
	POINT m_screenSize;
	POINT m_lastMousePoint;
	RECT m_workArea;
};

}
