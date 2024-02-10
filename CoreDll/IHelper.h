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

#include "API.h"
#include "ReturnMessages.h"

namespace ohms {

class CORE_API IHelper {
protected:
	IHelper() = default;
public:
	virtual ~IHelper() = default;

	static IHelper* instance();
	static void drop();

public:
	/**
	 * @brief 尝试开始任务。任务将运行在子线程，如果已经运行则无效。
	 * @return true为成功
	*/
	virtual bool start() = 0;
	/**
	 * @brief 请求停止
	*/
	virtual void askForStop() = 0;
	/**
	 * @brief 是否正在运行任务
	 * @return true则正在运行
	*/
	virtual bool isRunning() = 0;

	/**
	 * @brief 弹出返回消息
	*/
	virtual unsigned long msgPop() = 0;

public:
	/**
	 * @brief 设置挑战赛打新比赛
	 * @param forNew 为 true 则打新比赛，否则打上一次比赛
	 * @return 0 if success.
	*/
	virtual long setPlayChallengeForNew(bool forNew) = 0;
	/**
	 * @brief 设置使用鼠标输入。
	 * @param forMouse 为 true 则使用鼠标输入，否则发送窗口消息。
	 * @return 0 if success.
	*/
	virtual long setUseMouseInput(bool forMouse) = 0;
	/**
	 * @brief 
	 * @param show 
	 * @return 0 if success.
	*/
	virtual long setShowCapture(bool show) = 0;
	/**
	 * @brief 
	 * @param prevent 
	 * @return 0 if success.
	*/
	virtual long setPreventSleep(bool prevent) = 0;
	/**
	 * @brief 
	 * @param keep 
	 * @return 0 if success.
	*/
	virtual long setPreventCloseDisplay(bool keep) = 0;

};

} // namespace ohms