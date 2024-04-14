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

namespace Wrapper {

public enum class ReturnMessage {
	None = ohms::ReturnMsgEnum::None,


	_CMD_START = ohms::ReturnMsgEnum::_CMD_START,
	CMD_EmptyLine,  // 添加一个空行。
	CMD_Stopped,    // 任务已停止。
	CMD_BtnToStop,  // 按钮切换为 “停止”。
	CMD_BtnToStart, // 按钮切换为 “开始”。


	_LOG_START = ohms::ReturnMsgEnum::_LOG_START,
	LOG_StartError_Running,
	LOG_Stopping,
	LOG_Stopped,
	LOG_Complete,

	LOG_WorkError_ExceptionInternalError,

	LOG_TaskStop,
	LOG_TaskComplete,
	LOG_TaskError_Exception,
	LOG_TaskError, // 下跟参数

	LOG_Challenge_Start,
	LOG_Challenge_BeginNum, // 挑战赛开始（下跟次数！）
	LOG_Challenge_Over,
	LOG_Challenge_Exit,
	LOG_Challenge_BeginAdd, // 奖励挑战赛开始（下跟次数！）
	LOG_Challenge_IgnoredAdd,
	LOG_Challenge_NotFindAdd,
	LOG_Challenge_FindAdd,
	LOG_Challenge_OpenedAdd,


	_STR_START = ohms::ReturnMsgEnum::_STR_START,
	// 以下都是 LOG_TaskError 指定参数
	STR_Task_Challenge_NoNew,
	STR_Task_Challenge_NoLast,
	STR_Task_Challenge_NoEnter,
	STR_Task_Challenge_NoStart,
	STR_Task_Challenge_TimeOut,
	STR_Task_Challenge_NoEnd,
	STR_Task_Challenge_NoOver,
	STR_Task_Challenge_AddNotSup,
	STR_Task_Challenge_IgnoreAddFailed,
	STR_Task_Challenge_OpenAddFailed,
	STR_Task_FailedToLoadTemplateFile,
	STR_Task_Error_NoWnd,
	STR_Task_Error_FailedCapture,
};

}
