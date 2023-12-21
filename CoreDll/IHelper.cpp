/*
*    DDOA-DOAXVV-OPEN-ASSISTANT
*
*     Copyright 2023-2024  Tyler Parret True
*
*    Licensed under the Apache License, Version 2.0 (the "License");
*    you may not use this file except in compliance with the License.
*    You may obtain a copy of the License at
*
*        http://www.apache.org/licenses/LICENSE-2.0
*
*    Unless required by applicable law or agreed to in writing, software
*    distributed under the License is distributed on an "AS IS" BASIS,
*    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*    See the License for the specific language governing permissions and
*    limitations under the License.
*
* @Authors
*    Tyler Parret True <mysteryworldgod@outlook.com><https://github.com/OwlHowlinMornSky>
*/
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
