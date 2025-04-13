#include "DropFileProc.h"

#include <thread>
#include <mutex>
#include <iostream>
#include <vector>

#include "TaskClipPicture.h"

namespace {

std::mutex g_mutex;
bool g_haveTask = false;
std::vector<std::string> g_strings;

}

void OnDropFiles(HWND hwnd, HDROP hDropInfo) {
	g_mutex.lock();
	if (g_haveTask) {
		g_mutex.unlock();
		std::cout << "There is already a task." << std::endl;
		return;
	}
	g_haveTask = true;
	g_mutex.unlock();

	UINT  nFileCount = DragQueryFileW(hDropInfo, (UINT)-1, NULL, 0);
	CHAR szFileName[MAX_PATH] = "";
	DWORD dwAttribute;

	std::cout << "Drag in " << nFileCount << " files:" << std::endl;
	g_strings.clear();
	g_strings.reserve(nFileCount);

	// 获取拖拽进来文件和文件夹
	for (UINT i = 0; i < nFileCount; i++) {
		DragQueryFileA(hDropInfo, i, szFileName, sizeof(szFileName));
		dwAttribute = ::GetFileAttributesA(szFileName);

		// 不为文件夹
		if (!(dwAttribute & FILE_ATTRIBUTE_DIRECTORY)) {
			std::cout << szFileName << std::endl;
			g_strings.emplace_back(szFileName);
		}
	}

	if (g_strings.size() == 1) {
		std::thread th(TaskClipPicture, std::ref(g_strings));
		th.detach();
		//std::thread th(TaskMask, std::ref(g_strings));
		//th.detach();
	}
	else {

	}

	DragFinish(hDropInfo);
}

void TaskOver() {
	g_mutex.lock();
	g_haveTask = false;
	g_mutex.unlock();
	std::cout << "Task Over." << std::endl;
}
