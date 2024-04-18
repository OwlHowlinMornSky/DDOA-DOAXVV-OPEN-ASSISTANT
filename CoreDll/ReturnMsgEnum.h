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

namespace ohms {
namespace ReturnMsgCmd {
enum CORE_API ReturnCmd : long {
	None = 0,   // 空。

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
}
namespace ReturnMsgEnum {
/**
 * @brief Helper 向 GUI 的回执。
*/
enum CORE_API ReturnMessage : long {
	None = 0,   // 空。

	WorkStartErrRunning, // 已经有工作在运行，启动失败
	WorkStopping, // askForStop 的 正在停止
	WorkStopped, // 工作已停止（用户操作）
	WorkComplete, // 工作完成

	WorkError, // 【暂未使用】
	WorkErrorInternalException, // 工作遇到未知类型的异常

	TaskStop, // 任务中止（用户操作）
	TaskComplete, // 任务完成
	TaskException, // 任务遇到未知类型的异常
	TaskErr_Format, // TaskError

	ChaStart, // 任务开始：挑战赛
	ChaBegin_I, // 比赛开始（下跟次数！）
	ChaOver, // 比赛结束又回到“挑战赛”界面
	ChaExit, // 任务结束：挑战赛
	ChaBeginAdd_I, // 奖励挑战赛开始（下跟次数！）
	ChaIgnoredAdd, // 忽略了奖励挑战赛
	ChaNotFindAdd, // 没有找到奖励挑战赛
	ChaFindAdd, // 找到奖励挑战赛
	ChaOpenedAdd, // 打开了奖励挑战赛

	TaskErrChaNoNew, // 没找到 new match
	TaskErrChaNoPri, // 没找到 previous match
	TaskErrChaNoEnter, // 点了关卡一直进不去
	TaskErrChaNoStart, // 点了挑战按钮一直进不去
	TaskErrChaTimeOut, // 比赛过程太久了
	TaskErrChaNoEnd, // 结算画面出不去
	TaskErrChaNoOver, // 结算完的加载画面出不去
	TaskErrChaAddNotSup, // 不支持奖励挑战赛（只有选择新比赛才支持）
	TaskErrChaIgnoreAddFailed, // 忽略奖励挑战赛（即点回去的过程）失败
	TaskErrChaOpenAddFailed, // 打开奖励挑战赛失败
	TaskErrFailedToLoadTemplateFile, // 无法加载模板图片
	TaskErrNoWnd, // 没找到游戏窗口
	TaskErrNoCap, // 没法截图

	NotImplemented, // 尚未实现

	TestTaskBegin,
	TestTaskEnd,
};
}
}
