#pragma once

#include <atomic>

namespace ohms {

extern std::atomic_bool g_askedForStop; // 请求停止的标记。true为需要停止

}
