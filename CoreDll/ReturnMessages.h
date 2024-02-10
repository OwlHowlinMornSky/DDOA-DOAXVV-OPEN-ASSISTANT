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

namespace ohms::HelperReturnMessage {

/**
 * @brief Helper 通知 MainWindow 的消息。
*/
enum CORE_API HelperReturnMessage : unsigned long {
	None = 0,   // 空。


	_CMD_START = 0x00000000ul,
	CMD_Stopped,    // 任务已停止，需要进行如停止截图之类的处理。
	CMD_BtnToStop,  // 按钮切换为 “停止”。
	CMD_BtnToStart, // 按钮切换为 “开始”。


	_LOG_START = 0x000000fful,
	LOG_ErrorIsRunning,
	LOG_Stopping,
	LOG_ErrorNotFindWnd,
	LOG_ErrorCannotCapture,
	LOG_ErrorInWork,
	LOG_ErrorInTask, // 下跟参数

	LOG_Challenge_Start,
	LOG_Challenge_BeginNum, // 挑战赛开始（下跟次数！）
	LOG_Challenge_EnterLast,
	LOG_Challenge_EnterNew,
	LOG_Challenge_Play,
	LOG_Challenge_WaitForEnd,
	LOG_Challenge_End,
	LOG_Challenge_Quiting,
	LOG_Challenge_Over,
	LOG_Challenge_Exit,

	LOG_Task_Stop,
	LOG_Task_Exception,


	_STR_START = 0x0000fffful,
	// 以下都是 Log_ErrorInTask 指定参数
	STR_Task_Challenge_NoNew,
	STR_Task_Challenge_NoLast,
	STR_Task_Challenge_NoEnter,
	STR_Task_Challenge_LowFP,
	STR_Task_Challenge_NoStart,
	STR_Task_Challenge_TimeOut,
	STR_Task_Challenge_NoEnd,
	STR_Task_Challenge_NoOver
};

}
