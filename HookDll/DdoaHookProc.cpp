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
#include "DdoaHookProc.h"

#include <fstream>
#include <filesystem>
#include <queue>

namespace fs = std::filesystem;

namespace {

struct CommandData {
	enum Type {
		stop = -1,
		start = 0,
		sleep,
		move,
		click,
		wheel
	} type;

	struct SleepData {
		long long duration;
	};
	struct MoveData {
		float x;
		float y;
	};
	struct WheelData {
		int delta;
	};

	union Data {
		SleepData sleep;
		MoveData move;
		WheelData wheel;
	} data;
};

std::ofstream g_ofstream;

static std::queue<CommandData> g_cmds;

static const fs::path p("records");

/**
 * @brief 获取内核速度
*/
LARGE_INTEGER getFrequency() {
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);
	return frequency;
}

/**
 * @brief 获取当前时间
*/
long long getCurrentTime() {
	// Calculate inverse of frequency multiplied by 1000000 to prevent overflow in final calculation
	// Frequency is constant across the program lifetime
	static double inverse = 1000000.0 / static_cast<double>(getFrequency().QuadPart);

	LARGE_INTEGER time;

	// Get the current time
	QueryPerformanceCounter(&time);

	// Return the current time as microseconds
	return static_cast<long long>(static_cast<double>(time.QuadPart) * inverse);
}

long long g_lastTime;

} // namespace

DLL_API LRESULT CALLBACK DdoaHookProc(
	_In_ int    code,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
) {
	if (code < 0) {
		return CallNextHookEx(NULL, code, wParam, lParam);
	}
	LPMSG msg = (LPMSG)lParam;
	switch (msg->message) {
	case WM_MOUSEMOVE:
	{
		POINTS pt = MAKEPOINTS(msg->lParam);
		if (pt.y < 0)
			break;
		if (!(msg->wParam & MK_CONTROL))
			msg->message = WM_NULL;
		break;
	}
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_MBUTTONDOWN:
	case WM_XBUTTONDOWN:
	case WM_MOUSEWHEEL:
	{
		if (!(msg->wParam & MK_CONTROL))
			msg->message = NULL;
		break;
	}
	}
	return CallNextHookEx(NULL, code, wParam, lParam);
}

DLL_API LRESULT RecordHookProc(
	_In_ int    code,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
) {
	LPMSG msg = (LPMSG)lParam;
	switch (msg->message) {
	case WM_LBUTTONDOWN:
	{
		POINTS pt = MAKEPOINTS(msg->lParam);
		RECT rect;
		if (GetClientRect(msg->hwnd, &rect) == 0)
			break;
		long long t = ::getCurrentTime();
		CommandData data;
		data.type = CommandData::Type::sleep;
		data.data.sleep.duration = t - ::g_lastTime;
		::g_lastTime = t;
		g_cmds.push(data);
		data.type = CommandData::Type::move;
		data.data.move.x = 1.0f * pt.x / (rect.right - rect.left);
		data.data.move.y = 1.0f * pt.y / (rect.bottom - rect.top);
		g_cmds.push(data);
		data.type = CommandData::Type::click;
		g_cmds.push(data);
		break;
	}
	case WM_MOUSEWHEEL:
	{
		POINTS pt = MAKEPOINTS(msg->lParam);
		RECT rect;
		if (GetClientRect(msg->hwnd, &rect) == 0)
			break;
		long long t = ::getCurrentTime();
		CommandData data;
		data.type = CommandData::Type::sleep;
		data.data.sleep.duration = t - ::g_lastTime;
		::g_lastTime = t;
		g_cmds.push(data);
		data.type = CommandData::Type::move;
		data.data.move.x = 1.0f * pt.x / (rect.right - rect.left);
		data.data.move.y = 1.0f * pt.y / (rect.bottom - rect.top);
		g_cmds.push(data);
		data.type = CommandData::Type::wheel;
		data.data.wheel.delta = GET_WHEEL_DELTA_WPARAM(msg->wParam);
		g_cmds.push(data);
		break;
	}
	}
	return CallNextHookEx(NULL, code, wParam, lParam);
}

namespace Hook {

int StartRecord() {
	return 0;
}

int StopRecord() {
	if (!fs::exists(::p)) {
		fs::create_directory(::p);
	}
	else if (!fs::is_directory(::p)) {
		return 1;
	}
	g_ofstream.open(::p / "temporary.ddoa");
	if (!g_ofstream.is_open()) {
		return 2;
	}
	::g_lastTime = getCurrentTime();
	::g_ofstream << "start" << std::endl;

	while (!g_cmds.empty()) {
		switch (g_cmds.front().type) {
		case CommandData::Type::sleep:
			g_ofstream <<
				"sleep " <<
				g_cmds.front().data.sleep.duration <<
				std::endl;
			break;
		case CommandData::Type::move:
			g_ofstream <<
				"move " <<
				g_cmds.front().data.move.x <<
				" " <<
				g_cmds.front().data.move.y <<
				std::endl;
			break;
		case CommandData::Type::click:
			g_ofstream <<
				"click" <<
				std::endl;
			break;
		case CommandData::Type::wheel:
			g_ofstream <<
				"wheel " <<
				g_cmds.front().data.wheel.delta <<
				std::endl;
			break;
		}
	}
	g_ofstream << "stop" << std::endl;
	g_ofstream.close();
	return 0;
}

}
