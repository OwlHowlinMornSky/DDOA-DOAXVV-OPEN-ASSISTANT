#pragma once

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

public:
	/**
	 * @brief 尝试开始。任务将运行在子线程，如果已经运行则无效。
	*/
	virtual bool start() = 0;
	/**
	 * @brief 要求停止。
	*/
	virtual void askForStop() = 0;
	/**
	 * @brief 是否正在运行。
	*/
	virtual bool isRunning() = 0;
};

}