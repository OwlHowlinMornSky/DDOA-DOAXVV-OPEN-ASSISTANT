#pragma once

#include "../Window/ILogger.h"

namespace ohms {

/**
 * @brief Helper 通知 MainWindow 的消息。
*/
enum class HelperReturnMessage {
	None = 0,   // 空。
	Stopped,    // 任务已停止，需要进行如停止截图之类的处理。
	BtnToStop,  // 按钮切换为 “停止”。
	BtnToStart  // 按钮切换为 “开始”。
};

class IHelper {
protected:
	IHelper() = default;
public:
	virtual ~IHelper() = default;

	static IHelper* instance();
	static void drop();

public:
	/**
	 * @brief 注册 logger，必须在 start() 前注册
	 * @param logger 指针
	*/
	virtual void regLogger(ILogger* logger) = 0;
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
	 * @param hrm 保存消息的变量
	 * @return true则获取到，否则没有消息
	*/
	virtual bool msgPop(HelperReturnMessage& hrm) = 0;
};

} // namespace ohms