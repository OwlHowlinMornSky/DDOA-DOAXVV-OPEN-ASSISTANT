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
#include "CoreLog.h"

#include <filesystem>

namespace ohms {

std::ofstream g_coreLog;

bool SetupLog() {
	std::filesystem::path m_logFolder;
	m_logFolder.assign("corelog.log");
	if (!(std::filesystem::exists(m_logFolder) && std::filesystem::is_directory(m_logFolder)) && !std::filesystem::create_directory(m_logFolder))
		return false;
	// 生成 带当前时间的 输出名称
	/*struct tm t = { 0 };
	time_t ts = time(0);
	localtime_s(&t, &ts);
	char buf[128];
	strftime(buf, sizeof(buf), "CoreLog-%Y-%m-%d-%H-%M-%S.log", &t);*/
	g_coreLog.open(m_logFolder/* / buf*/, std::ios_base::app);
	if (!g_coreLog.is_open())
		return false;
	LogLine("Logger Set.");
	return true;
}

std::ofstream& CoreLog() {
	struct tm t = { 0 };
	time_t ts = time(0);
	localtime_s(&t, &ts);
	char buf[128];
	strftime(buf, sizeof(buf), "[%Y/%m/%d %H:%M:%S] ", &t);
	g_coreLog << buf;
	return g_coreLog;
}

void LogLine(std::string_view str) {
	struct tm t = { 0 };
	time_t ts = time(0);
	localtime_s(&t, &ts);
	char buf[128];
	strftime(buf, sizeof(buf), "[%Y/%m/%d %H:%M:%S] ", &t);
	g_coreLog << buf << str << std::endl;
	return;
}

}
