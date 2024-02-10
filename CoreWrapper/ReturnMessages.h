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
	None = ohms::HelperReturnMessage::None,

	_CMD_START = ohms::HelperReturnMessage::_CMD_START,
	Cmd_Stopped,
	Cmd_BtnToStop,
	Cmd_BtnToStart,

	_LOG_START = ohms::HelperReturnMessage::_LOG_START,
	Log_ErrorIsRunning,
	Log_Stopping,
	Log_ErrorNotFindWnd,
	Log_ErrorCannotCapture,
	Log_ErrorInWork,
	Log_ErrorInTask,

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

	_STR_START = ohms::HelperReturnMessage::_STR_START,
	Str_Task_Challenge_NoNew,
	Str_Task_Challenge_NoLast,
	Str_Task_Challenge_NoEnter,
	Str_Task_Challenge_LowFP,
	Str_Task_Challenge_NoStart,
	Str_Task_Challenge_TimeOut,
	Str_Task_Challenge_NoEnd,
	Str_Task_Challenge_NoOver
};

}
