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
#include "ReturnMsgEnum.h"

namespace ohms {

/**
 * @brief Helper的对外接口。
 */
class CORE_API IHelper {
protected:
	IHelper() = default;
public:
	virtual ~IHelper() = default;

	/**
	 * @brief 获取唯一实例。首次获取时构造。
	 * @return 指向实例的指针。
	 */
	static IHelper* instance();
	/**
	 * @brief 销毁实例。
	 */
	static void drop();

public:
	/**
	 * @brief 初始化。
	 * @return 状态代码。
	 */
	virtual int setup(bool winrtInited = true) = 0;
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
	 * @brief 继续任务。
	 */
	virtual void resume() = 0;

	/**
	 * @brief 是否正在运行任务
	 * @return true则正在运行
	*/
	virtual bool isRunning() = 0;

	/**
	 * @brief 弹出返回消息
	*/
	virtual long msgPop() = 0;

	/**
	 * @brief 向主界面日志添加一条文本。
	 * @param fmt 文本编号。
	 */
	virtual void GuiLogF(long fmt) = 0;

	virtual int StartRecord() = 0;
	virtual int StopRecord() = 0;
};

} // namespace ohms