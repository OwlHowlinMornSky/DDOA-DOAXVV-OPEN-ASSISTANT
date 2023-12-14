#pragma once

#include <IHelper.h>

namespace Wrapper {

public enum class ReturnMessage {
	None = ohms::HelperReturnMessage::None,

	Stopped = ohms::HelperReturnMessage::Stopped,
	BtnToStop = ohms::HelperReturnMessage::BtnToStop,
	BtnToStart = ohms::HelperReturnMessage::BtnToStart,

	Log_ErrorIsRunning = ohms::HelperReturnMessage::Log_ErrorIsRunning,
	Log_Stopping = ohms::HelperReturnMessage::Log_Stopping,
	Log_ErrorNotFindWnd = ohms::HelperReturnMessage::Log_ErrorNotFindWnd,
	Log_ErrorCannotCapture = ohms::HelperReturnMessage::Log_ErrorCannotCapture,
	Log_ErrorInWork = ohms::HelperReturnMessage::Log_ErrorInWork,
	Log_ErrorInTask = ohms::HelperReturnMessage::Log_ErrorInTask,

	Log_Challenge_Start = ohms::HelperReturnMessage::Log_Challenge_Start,
	Log_Challenge_BeginNum = ohms::HelperReturnMessage::Log_Challenge_BeginNum, // 挑战赛开始（下跟次数！）
	Log_Challenge_EnterLast = ohms::HelperReturnMessage::Log_Challenge_EnterLast,
	Log_Challenge_EnterNew = ohms::HelperReturnMessage::Log_Challenge_EnterNew,
	Log_Challenge_Play = ohms::HelperReturnMessage::Log_Challenge_Play,
	Log_Challenge_WaitForEnd = ohms::HelperReturnMessage::Log_Challenge_WaitForEnd,
	Log_Challenge_End = ohms::HelperReturnMessage::Log_Challenge_End,
	Log_Challenge_Quiting = ohms::HelperReturnMessage::Log_Challenge_Quiting,
	Log_Challenge_Over = ohms::HelperReturnMessage::Log_Challenge_Over,
	Log_Challenge_Exit = ohms::HelperReturnMessage::Log_Challenge_Exit,

	Log_Task_Stop = ohms::HelperReturnMessage::Log_Task_Stop,
	Log_Task_Exception = ohms::HelperReturnMessage::Log_Task_Exception,

	Log_Task_Challenge_NoNew = ohms::HelperReturnMessage::Log_Task_Challenge_NoNew,
	Log_Task_Challenge_NoLast = ohms::HelperReturnMessage::Log_Task_Challenge_NoLast,
	Log_Task_Challenge_NoEnter = ohms::HelperReturnMessage::Log_Task_Challenge_NoEnter,
	Log_Task_Challenge_LowFP = ohms::HelperReturnMessage::Log_Task_Challenge_LowFP,
	Log_Task_Challenge_NoStart = ohms::HelperReturnMessage::Log_Task_Challenge_NoStart,
	Log_Task_Challenge_TimeOut = ohms::HelperReturnMessage::Log_Task_Challenge_TimeOut,
	Log_Task_Challenge_NoEnd = ohms::HelperReturnMessage::Log_Task_Challenge_NoEnd,
	Log_Task_Challenge_NoOver = ohms::HelperReturnMessage::Log_Task_Challenge_NoOver
};

}
