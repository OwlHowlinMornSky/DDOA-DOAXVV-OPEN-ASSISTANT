﻿/*
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

namespace ohms {

/**
 * @brief 
 */
class Helper final :
	public IHelper {
	friend class IHelper;
protected:
	Helper();
public:
	virtual ~Helper() override;

// 继承的，接口。
public:
	virtual int setup(bool winrtInited = true) override;
	virtual bool start() override;
	virtual void askForStop() override;
	virtual void resume() override;
	virtual bool isRunning() override;
	virtual long msgPop() override;

public:
	/**
	 * @brief 压入回执消息
	*/
	void GuiLogC_EmptyLine();
	void GuiLogC_Stopped();
	void GuiLogC_BtnToStop();
	void GuiLogC_BtnToStart();
	void GuiLogC_Pause_S(long str);
	virtual void GuiLogF(long fmt) override;
	void GuiLogF_S(long fmt, long str);
	void GuiLogF_I(long fmt, long intval);
	void GuiLogF_SI(long fmt, long str, long intval);
	void GuiLogF_II(long fmt, long intval0, long intval1);

	/**
	 * @brief 从模板列表读取模板创建，并读取图片文件。
	 * @param name 模板名称。
	 * @return 创建结果，为nullptr说明出错。
	 */
	std::unique_ptr<MatchTemplate> CreateTemplate(const std::string& name);

	/**
	 * @brief 报错（写入logger并弹窗），并 throw 0
	 * @param str 报错信息
	*/
	void TaskError(long str);

	/**
	 * @brief 发送等待日志并暂停，直到手动恢复。
	 * @param str 暂停原因描述。
	 */
	void TaskWaitForResume(long str);

// 内部的，具体实现。
protected:
	/**
	 * @brief 运行在子线程的工作。
	*/
	void Work();

// 成员变量
protected:
	std::atomic_bool m_running; // 正在运行的标记。true为正在运行
	std::atomic_bool m_paused; // 是否已暂停。

	std::queue<long> m_hrm; // 返回消息的队列
	std::mutex m_hrm_mutex; // 返回消息的互斥体

	std::filesystem::path m_assets; // 图片资源文件夹
	WndHandler* r_handler; // 对窗口操作器实例的链接。
	TemplateListType m_templateList; // 模板列表。从文件中加载
};

/*
* note:
* 
* throw 0 的原因：task/work通过catch到0判断任务停止。
* 
*/

} // namespace ohms
