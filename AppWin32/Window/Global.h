#pragma once

#include "../framework.h"
#include <memory>
#include "../Capture/ICapture.h"

namespace ohms::global {

extern HINSTANCE hInst;
extern HWND hMain;
extern std::unique_ptr<ohms::capture::wgc::ICapture> g_app;

} // namespace
