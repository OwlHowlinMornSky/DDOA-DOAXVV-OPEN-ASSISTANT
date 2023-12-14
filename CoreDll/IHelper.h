#pragma once

#include "API.h"

namespace ohms {

namespace HelperReturnMessage {

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

class CORE_API IHelper {
protected:
	IHelper() = default;
public:
	virtual ~IHelper() = default;

	static IHelper* instance();
	static void drop();

public:
	/**
	 * @brief 设置挑战赛打新比赛
	 * @param forNew true则打新比赛，否则打上一次比赛
	*/
	virtual void regForNew(bool forNew) = 0;

	virtual void regForMouse(bool forMouse) = 0;

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
};

} // namespace ohms