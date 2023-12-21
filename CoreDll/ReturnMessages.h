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

	Stopped,    // 任务已停止，需要进行如停止截图之类的处理。
	BtnToStop,  // 按钮切换为 “停止”。
	BtnToStart, // 按钮切换为 “开始”。

	Log_ErrorIsRunning,
	Log_Stopping,
	Log_ErrorNotFindWnd,
	Log_ErrorCannotCapture,
	Log_ErrorInWork,
	Log_ErrorInTask, // 下跟参数

	Log_Challenge_Start,
	Log_Challenge_BeginNum, // 挑战赛开始（下跟次数！）
	Log_Challenge_EnterLast,
	Log_Challenge_EnterNew,
	Log_Challenge_Play,
	Log_Challenge_WaitForEnd,
	Log_Challenge_End,
	Log_Challenge_Quiting,
	Log_Challenge_Over,
	Log_Challenge_Exit,

	Log_Task_Stop,
	Log_Task_Exception,

	// 以下都是 Log_ErrorInTask 指定参数
	Log_Task_Challenge_NoNew,
	Log_Task_Challenge_NoLast,
	Log_Task_Challenge_NoEnter,
	Log_Task_Challenge_LowFP,
	Log_Task_Challenge_NoStart,
	Log_Task_Challenge_TimeOut,
	Log_Task_Challenge_NoEnd,
	Log_Task_Challenge_NoOver
};

}
