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

#include "MatchTemplate.h"
#include "Time.h"

#include <array>

#include <opencv2/core/types.hpp>
#include <opencv2/core/mat.hpp>

#include "framework.h" // 不能移上去，因为windows头文件不能在opencv头文件之前。

namespace ohms {

/**
 * @brief 窗口操作器。
 */
class WndHandler final {
public:
	enum class SetReturnValue {
		OK = 0,
		WndNotFound,
		CaptureFailed
	};
	enum class StateValue {
		Idle = 0,
		Launcher,
		Game,
		DebuggerGame,
		DebuggerLauncher
	};

protected:
	WndHandler();
public:
	virtual ~WndHandler();

	/**
	 * @brief 获取唯一实例。首次获取时初始化WGC并构造。
	 * @return 指向实例的指针。
	 */
	static WndHandler* Instance(bool winrtInited = true);
	/**
	 * @brief 销毁实例。
	 */
	static void Drop();

public:
	/**
	 * @brief 更新基础信息。请在开始工作时调用一次。
	 * @return 获取wgc实例是否成功。
	 */
	bool Update();

	bool LaucherAvailable();
	bool GameWndAvailable();

	/**
	 * @brief 设定目标窗口为DOAXVV的登录器窗口。
	 * @return “设定”操作的状态。
	 */
	SetReturnValue SetForLauncher();
	/**
	 * @brief 设定目标窗口为DOAXVV的游戏窗口。
	 * @return “设定”操作的状态。
	 */
	SetReturnValue SetForGame();
	/**
	 * @brief 重设状态，清除目标窗口。
	 */
	void Reset();
	/**
	 * @brief 获取当前设定的目标。
	 * @return 设定的目标。
	 */
	StateValue GetState() const;

	/**
	 * @brief 等待画面出现模板。
	 * @param _temp 模板。
	 * @param _tlimit 限时。
	 * @return -1为超时，0为匹配成功。
	 */
	int WaitFor(const MatchTemplate& _temp, Time _tlimit = milliseconds(10'000));
	/**
	 * @brief 等待画面出现模板之一。
	 * @param _temps 模板列。
	 * @param _tlimit 限时。
	 * @return -1为超时，自然数则为匹配到的模板的序号。
	 */
	int WaitForMultiple(std::vector<const MatchTemplate*> _temps, Time _tlimit);

	/**
	 * @brief 单击。范围是统一尺寸（960 540），自动缩放到当前DOAXVV大小
	 * @param pt 位置
	 * @return 未使用
	*/
	bool ClickAt(cv::Point pt);
	/**
	 * @brief 移动光标。范围是统一尺寸（960 540），自动缩放到当前DOAXVV大小
	 * @param pt 位置
	 * @return 未使用
	*/
	bool MoveMouseTo(cv::Point pt);


	/**
	 * @brief 持续点击指定位置，直到画面出现目标。askedForStop则 throw 0
	 * @param clkPt 指定点击位置，范围与 step_click 一致
	 * @param _temp 目标模板
	 * @param maxTime 超时时间（小于等于0则为永久）
	 * @param clkTime 点击间隔（不能小于10毫秒）
	 * @return true则已找到目标，false则为超时
	*/
	bool KeepClickingUntil(
		const cv::Point clkPt, const MatchTemplate& _temp, Time maxTime = seconds(10.0f), Time clkTime = seconds(1.0f)
	);

	/**
	 * @brief 持续点击指定位置，直到画面没有目标。askedForStop则 throw 0
	 * @param clkPt 指定点击位置，范围与 step_click 一致
	 * @param _temp 目标模板
	 * @param maxTime 超时时间（小于等于0则为永久）
	 * @param clkTime 点击间隔（不能小于10毫秒）
	 * @return true则已排除目标，false则为超时
	*/
	bool KeepClickingUntilNo(
		const cv::Point clkPt, const MatchTemplate& _temp, Time maxTime = seconds(10.0f), Time clkTime = seconds(1.0f)
	);

	bool GetOneFrame(cv::Mat& store, Time maxTime = seconds(10.0f));

protected:
	/**
	 * @brief 设定目标窗口为DDOA调试器窗口。
	 * @param isGame 操作重定向类型。
	 * @return “设定”操作的状态。
	 */
	SetReturnValue SetForDebugger(bool isGame);

protected:
	/**
	 * @brief 从capture复制mat到m_mat，同时检查capture是否refresh，顺便resize到统一尺寸（960 540）。
	 * @return capture已refresh并复制成功则为true，未refresh返回false，复制失败返回false
	*/
	bool CopyMat();

	bool LoadHookInfo();
	bool TryHook();
	void DropHook();
	void ClearHookInfo();

private:
	HWND m_hwnd; // 窗口句柄
	StateValue m_state; // 目标状态。
	POINT m_screenSize; // 屏幕大小。
	POINT m_lastMousePoint; // 鼠标位置记录。
	RECT m_workArea; // 工作区域（即除去任务栏）。
	cv::Mat m_mat; // 截取到的帧的存储位置。

	HMODULE m_hmod;
	HHOOK m_hhook;
	FARPROC m_hookproc;
};

}
