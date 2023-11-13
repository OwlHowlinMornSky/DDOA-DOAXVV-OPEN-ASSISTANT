#pragma once

#include "Window/framework.h"
#include <memory>
#include "Capture/ICapture.h"
#include "Helper/IHelper.h"

namespace ohms::global {

extern HINSTANCE hInst; // 本程序实例。
extern std::unique_ptr<ohms::capture::wgc::ICapture> capture; // 截图组件实例。
extern std::unique_ptr<ohms::IHelper> helper; // 助手实例。

} // namespace
