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

#include <queue>
#include <mutex>
#include <atomic>

#include "Time.h"
#include "IHelper.h"

#include <ohms/WGC.h>
#include <opencv2/opencv.hpp>

namespace ohms {

class Helper final :
	public IHelper {
	friend class IHelper;
protected:
	Helper();
public:
	virtual ~Helper() override;

// 继承的，接口。
public:
	/**
	 * @brief 设置挑战赛打新比赛
	 * @param forNew true则打新比赛，否则打上一次比赛
	*/
	virtual long regForNew(bool forNew) override;

	virtual long regForMouse(bool forMouse) override;

	virtual long regShowCV(bool show) override;

	virtual long regPrevent(bool prevent) override;
	virtual long regPreventKeepDisplay(bool keep) override;

public:
	/**
	 * @brief 尝试开始任务。任务将运行在子线程，如果已经运行则无效。
	 * @return true为成功
	*/
	virtual bool start() override;
	/**
	 * @brief 请求停止
	*/
	virtual void askForStop() override;
	/**
	 * @brief 是否正在运行任务
	 * @return true则正在运行
	*/
	virtual bool isRunning() override;
	/**
	 * @brief 弹出返回消息
	 * @param hrm 保存消息的变量
	 * @return true则获取到，否则没有消息
	*/
	virtual unsigned long msgPop() override;

// 内部的，具体实现。
protected:
	/**
	 * @brief 运行在子线程的工作。
	*/
	void Work();
	/**
	 * @brief 压入回执消息
	 * @param hrm 回执消息
	*/
	void PushMsg(unsigned long hrm);
	/**
	 * @brief 压入回执消息（附带指示代码）
	 * @param hrm 回执消息
	 * @param code 指示代码
	*/
	void PushMsgCode(unsigned long hrm, unsigned long code);

// 任务
// 返回 false 表示无法继续
// (在 Helper.tasks.cpp 实现)
protected:
	bool Task_Challenge(); // 挑战赛。

// 单步操作
// (在 Helper.steps.cpp 实现)
protected:
	/**
	 * @brief 从capture复制mat，同时检查capture是否refresh，顺便resize到统一尺寸（960 540）。
	 * @param target 保存mat的位置
	 * @return capture已refresh并复制成功则为true，未refresh返回false，复制失败返回false
	*/
	bool Step_CopyMat(cv::Mat& target);

	/**
	 * @brief 等待画面出现目标。askedForStop则 throw 0
	 * @param matTemplate 目标
	 * @param searchRect 搜索范围
	 * @param findRect 找到的区域
	 * @param maxTime 超时时间（小于等于0则为永久）
	 * @param thres 差异阈值
	 * @return true则找到目标，findRect保存找到的区域，false则为超时
	*/
	bool Step_WaitFor(
		const cv::Mat& matTemplate, const cv::Rect searchRect, cv::Rect& findRect,
		Time maxTime = seconds(10.0f), float thres = 10.0f
	);

	/**
	 * @brief 单击。范围是统一尺寸（960 540），自动缩放到当前DOAXVV大小
	 * @param pt 位置
	 * @return 未使用
	*/
	bool Step_Click(cv::Point pt);
	/**
	 * @brief 移动光标。范围是统一尺寸（960 540），自动缩放到当前DOAXVV大小
	 * @param pt 位置
	 * @return 未使用
	*/
	bool Step_Move(cv::Point pt);

	/**
	 * @brief 持续点击指定位置，直到画面出现目标。askedForStop则 throw 0
	 * @param clkPt 指定点击位置，范围与 step_click 一致
	 * @param matTemplate 目标
	 * @param searchRect 搜索范围
	 * @param maxTime 超时时间（小于等于0则为永久）
	 * @param clkTime 点击间隔（不能小于10毫秒）
	 * @param thres 阈值
	 * @return true则已找到目标，false则为超时
	*/
	bool Step_KeepClickingUntil(
		const cv::Point clkPt, const cv::Mat& matTemplate, const cv::Rect searchRect,
		Time maxTime = seconds(10.0f), Time clkTime = seconds(1.0f), float thres = 10.0f
	);

	/**
	 * @brief 报错（写入logger并弹窗），并 throw 0
	 * @param str 报错信息
	*/
	void Step_TaskError(unsigned long type);

// 成员变量
protected:
	std::atomic_bool m_running; // 正在运行的标记。true为正在运行
	std::atomic_bool m_askedForStop; // 请求停止的标记。true为需要停止

	std::queue<unsigned long> m_hrm; // 返回消息的队列
	std::mutex m_hrm_mutex; // 返回消息的互斥体

	HWND m_doaxvv; // doaxvv窗口句柄
	wgc::ICapture* r_capture; // capture索引

	// 上一次比赛 和 新比赛 的图样，以及查找范围。
	cv::Mat mat_ChaGameLast;
	cv::Mat mat_ChaGameNew;
	cv::Rect rect_ChaGame;
	bool task_ChaGame_ForNew; // 选择新比赛。
	bool task_Mouse_ForMouse; // 选择控制鼠标。
	bool task_PreventFromSleep; // 阻止睡眠。
	bool task_KeepDisplay; // 阻止睡眠时保持显示。

	// 编队页面右下角的 挑战按钮。
	cv::Mat mat_StartGame;
	cv::Rect rect_StartGame;

	// 结算页面右上角的 RESULT。
	cv::Mat mat_Result;
	cv::Rect rect_Result;

	// 加载页面左上角的 DOAXVV。
	cv::Mat mat_Loading;
	cv::Rect rect_Loading;

	// 编队页面中间 可能出现的 FP不足。
	cv::Mat mat_LowFP;
	cv::Rect rect_LowFP;

	// 挑战赛页面的 标签页栏 (推荐、主要、每日、活动)。
	cv::Mat mat_ChaTabBar;
	cv::Rect rect_ChaTabBar;
};

/*
* note:
* 
* throw 0 的原因：subwork通过catch到0判断任务停止。
* 
*/

} // namespace ohms
