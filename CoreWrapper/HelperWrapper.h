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

#include <IHelper.h>
#include "ReturnMessages.h"
#include "TaskEnumWrap.h"

namespace Wrapper {

/**
 * @brief CLI套壳，向CoreDll的IHelper服务。
 */
public ref class HelperWrapper {
public:
	HelperWrapper();
	~HelperWrapper();

public:
	/**
	 * @brief 开始任务（IHelper::start）
	 * @return 启动是否成功。
	 */
	System::Boolean Start();
	/**
	 * @brief 要求停止（IHelper::askForStop）
	 */
	System::Void AskForStop();
	/**
	 * @brief 是否正在运行（IHelper::isRunning）
	 * @return 是否运行
	 */
	System::Boolean IsRunning();

	/**
	 * @brief 提取指令。
	 * @return 指令枚举。
	 */
	ReturnCmd GetCommand();
	/**
	 * @brief 提取消息字符串。
	 * @return 消息字符串枚举。
	 */
	ReturnMessage GetMessage();
	/**
	 * @brief 提取数值。
	 * @return int32。
	 */
	System::Int32 GetValueI();

	/**
	 * @brief 初始化。
	 * @return 0 为 成功，非零整数为各类错误。
	 */
	System::Int32 Setup();
	/**
	 * @brief 销毁。
	 */
	System::Void Drop();

public:
	/**
	 * @brief 设置是否显示调试性截图。
	 * @param show 为 true 则显示截图。
	 * @return 0 if success.
	*/
	System::Int32 SetShowCaptureOrNot(bool show);
	/**
	 * @brief 设置挑战赛打新比赛或上一次比赛。
	 * @param forNew 为 true 则打新比赛，否则打上一次比赛
	 * @return 0 if success.
	*/
	System::Int32 SetChallengeForNewOrLast(bool forNew);
	/**
	 * @brief 设置鼠标操作 发送输入 还是 窗口消息。
	 * @param sendInput 为 true 则使用鼠标输入，否则发送窗口消息。
	 * @return 0 if success.
	*/
	System::Int32 SetMouseSendInputOrSendMessage(bool sendInput);
	/**
	 * @brief 设置是否阻止睡眠。
	 * @param keep 为 true 则阻止睡眠。
	 * @return 0 if success.
	*/
	System::Int32 SetKeepAwakeOrNot(bool keep);
	/**
	 * @brief 设置阻止关闭屏幕。
	 * @param keep 为 true 则阻止。
	 * @return 0 if success.
	*/
	System::Int32 SetKeepScreenOnOrNot(bool keep);
	/**
	 * @brief 设置挑战赛运行时是否检测奖励挑战赛。
	 * @param check 为 true 则检测。
	 * @return 0 if success.
	*/
	System::Int32 SetChallengeCheckAwardOrNot(bool check);
	/**
	 * @brief 设置是否进入奖励挑战赛。
	 * @param play 为 true 则进入。
	 * @return 0 if success.
	*/
	System::Int32 SetChallengePlayAwardOrNot(bool play);
	/**
	 * @brief 设置任务列表。
	 * @param list 任务列表。
	 * @return 0 if success, 1 if too long.
	 */
	System::Int32 SetTaskList(array<System::UInt32>^ list);
	/**
	 * @brief 设置是否自动使用每日拍摄的补充FP。
	 * @param isSettedUse true则自动使用。
	 * @return 0 if success.
	 */
	System::Int32 SetUseCamFP(System::Boolean isSettedUse);

	void SetDoDailyCheck(bool setDo);
	void SetDoDailyShot(bool setDo);

private:
	ohms::IHelper* r_helper;
};

} // namespace Wrapper
