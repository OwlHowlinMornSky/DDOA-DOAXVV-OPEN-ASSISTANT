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
#include <filesystem>

#include "Time.h"
#include "IHelper.h"
#include "WndHandler.h"

//#include <opencv2/opencv.hpp>

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
	virtual bool start() override;
	virtual void askForStop() override;
	virtual bool isRunning() override;
	virtual unsigned long msgPop() override;

	//virtual long SetShowCaptureOrNot(bool show) override;

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
	bool Task_StartUp(); // 启动游戏。

	bool Task_Challenge(); // 挑战赛。

// 单步操作
// (在 Helper.steps.cpp 实现)
protected:
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
		const cv::Point clkPt, const MatchTemplate& _temp, Time maxTime = seconds(10.0f), Time clkTime = seconds(1.0f)
	);

	bool Step_KeepClickingUntilNo(
		const cv::Point clkPt, const MatchTemplate& _temp, Time maxTime = seconds(10.0f), Time clkTime = seconds(1.0f)
	);

	/**
	 * @brief 报错（写入logger并弹窗），并 throw 0
	 * @param str 报错信息
	*/
	void Step_TaskError(unsigned long type);

// 成员变量
protected:
	std::atomic_bool m_running; // 正在运行的标记。true为正在运行

	std::queue<unsigned long> m_hrm; // 返回消息的队列
	std::mutex m_hrm_mutex; // 返回消息的互斥体

	std::filesystem::path m_assets;
	WndHandler* m_handler;
	TemplateListType m_templateList;
};

/*
* note:
* 
* throw 0 的原因：subwork通过catch到0判断任务停止。
* 
*/

} // namespace ohms
