#include "UniqueInstance.h"

#include <atomic>

//EUI: EnsureUniqueInstance
#pragma data_seg("OHMS_EUI_CaptureWithOpenCV")
std::atomic<bool> g_instanceRunning(false);
#pragma data_seg()
#pragma comment(linker, "/Section:OHMS_EUI_CaptureWithOpenCV,RWS")


namespace UniqueInstance {

bool setup() {
	bool t_instanceRunning = false;
	if (!g_instanceRunning.compare_exchange_strong(t_instanceRunning, true)) {
		return false;
	}
	return true;
}

void drop() {
	g_instanceRunning.store(false);
	return;
}

}// namespace UniqueInstance
