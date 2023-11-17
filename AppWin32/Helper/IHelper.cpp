#include "IHelper.h"
#include "Helper.h"

namespace {

ohms::IHelper* g_helper;

}

namespace ohms {

IHelper* ohms::IHelper::instance() {
	if (!::g_helper) {
		::g_helper = new Helper;
	}
    return g_helper;
}

void IHelper::drop() {
	delete ::g_helper;
}

} // namespace ohms
