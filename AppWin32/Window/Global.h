#pragma once

#include "../framework.h"
#include <memory>
#include "../Capture/ICapture.h"

namespace ohms::global {

extern HINSTANCE hInst; // 本程序实例。
extern std::unique_ptr<ohms::capture::wgc::ICapture> g_app; // 截图组件实例。

} // namespace
