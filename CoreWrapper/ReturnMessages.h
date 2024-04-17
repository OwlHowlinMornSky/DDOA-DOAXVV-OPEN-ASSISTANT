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

public enum class ReturnCmd : System::UInt32 {
	None = ohms::ReturnMsgCmd::None,   // 空。

	CMD_EmptyLine,  // 添加一个空行。
	CMD_Stopped,    // 任务已停止。
	CMD_BtnToStop,  // 按钮切换为 “停止”。
	CMD_BtnToStart, // 按钮切换为 “开始”。

	LOG_Format,
	LOG_Format_S,
	LOG_Format_I,

	LOG_Format_SS,
	LOG_Format_SI,
	LOG_Format_IS,
	LOG_Format_II,

	LOG_Format_SSS,
	LOG_Format_SSI,
	LOG_Format_SIS,
	LOG_Format_SII,
	LOG_Format_ISS,
	LOG_Format_ISI,
	LOG_Format_IIS,
	LOG_Format_III,

	LOG_Format_SSSS,
	LOG_Format_SSSI,
	LOG_Format_SSIS,
	LOG_Format_SSII,
	LOG_Format_SISS,
	LOG_Format_SISI,
	LOG_Format_SIIS,
	LOG_Format_SIII,
	LOG_Format_ISSS,
	LOG_Format_ISSI,
	LOG_Format_ISIS,
	LOG_Format_ISII,
	LOG_Format_IISS,
	LOG_Format_IISI,
	LOG_Format_IIIS,
	LOG_Format_IIII,
};

/**
 * @brief 返回消息的包装。
 */
public enum class ReturnMessage : System::UInt32 {
	None = ohms::ReturnMsgEnum::None,

	WorkStartErrRunning,
	WorkStopping,
	WorkStopped,
	WorkComplete,

	WorkError,
	WorkErrorInternalException,

	TaskStop,
	TaskComplete,
	TaskException,
	TaskErr_Format,

	ChaStart,
	ChaBegin_I, // 挑战赛开始（下跟次数！）
	ChaOver,
	ChaExit,
	ChaBeginAdd_I, // 奖励挑战赛开始（下跟次数！）
	ChaIgnoredAdd,
	ChaNotFindAdd,
	ChaFindAdd,
	ChaOpenedAdd,

	TaskErrChaNoNew,
	TaskErrChaNoLast,
	TaskErrChaNoEnter,
	TaskErrChaNoStart,
	TaskErrChaTimeOut,
	TaskErrChaNoEnd,
	TaskErrChaNoOver,
	TaskErrChaAddNotSup,
	TaskErrChaIgnoreAddFailed,
	TaskErrChaOpenAddFailed,
	TaskErrFailedToLoadTemplateFile,
	TaskErrNoWnd,
	TaskErrCaptureFailed,
};

}
