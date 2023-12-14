#include "IHelper.h"
#include "Helper.h"

namespace {

ohms::IHelper* g_helper{ nullptr }; // helper实例

}

namespace ohms {

IHelper* ohms::IHelper::instance() {
	if (!::g_helper) { // 首次获取时构造
		::g_helper = new Helper;
	}
	return ::g_helper;
}

void IHelper::drop() {
	delete ::g_helper;
}

} // namespace ohms
