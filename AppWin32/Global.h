#pragma once

#include "Window/framework.h"
#include <memory>
#include "Capture/ICapture.h"
#include "Helper/IHelper.h"
#include <queue>
#include <mutex>

namespace ohms::global {

/**
 * @brief 本程序实例。
*/
extern HINSTANCE hInst;
/**
 * @brief 截图组件实例。
*/
extern std::unique_ptr<ohms::capture::wgc::ICapture> capture;
/**
 * @brief 助手实例。
*/
extern std::unique_ptr<ohms::IHelper> helper;

/**
 * @brief helper 向 gui 发回消息的队列。
*/
extern std::queue<ohms::HelperReturnMessage> helperReturnMessage;
/**
 * @brief 上述队列使用的 mutex。
*/
extern std::mutex mutexHRM;

/**
 * @brief doaxvv 窗口的句柄。
 * @brief 在 MainWindow 的 start 里写入，在整个任务周期使用。
*/
extern HWND doaxvv;

/**
 * @brief 向队列压入消息。
 * @param hrm: 消息。
*/
void pushHRM(ohms::HelperReturnMessage hrm);

} // namespace
