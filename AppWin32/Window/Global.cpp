#include "Global.h"

namespace ohms::global {

HINSTANCE hInst = 0;
std::unique_ptr<ohms::capture::wgc::ICapture> g_app;

}
