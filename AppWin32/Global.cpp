#include "Global.h"

namespace ohms::global {

HINSTANCE hInst = 0;
std::unique_ptr<ohms::capture::wgc::ICapture> capture;
std::unique_ptr<ohms::IHelper> helper;

std::queue<ohms::HelperReturnMessage> helperReturnMessage;
std::mutex mutexHRM;

void pushHRM(ohms::HelperReturnMessage hrm) {
	std::lock_guard lg(mutexHRM);
	helperReturnMessage.push(hrm);
	return;
}

}
