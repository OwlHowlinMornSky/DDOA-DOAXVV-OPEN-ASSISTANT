#include "AppWin32.h"

#include "UniqueInstance.h"
#include "Window/MainWindow.h"
#include <ohms/WGC.h>
#include "Helper/IHelper.h"

AppWin32 app;

bool AppWin32::Init() {
	if (!UniqueInstance::setup()) {
		MessageBoxW(NULL, L"Another instance is running.", L"DOAXVV-helper", MB_ICONERROR);
		return 1;
	}

	auto wgc = ohms::wgc::ICapture::getInstance();
	if (!wgc) {
		MessageBoxW(NULL, L"Capture initialization failed.", L"DOAXVV-helper", MB_ICONERROR);
		return 1;
	}
	wgc->setClipToClientArea(true);

	auto hlp = ohms::IHelper::instance();
	if (!hlp) {
		MessageBoxW(NULL, L"Helper initialization failed.", L"DOAXVV-helper", MB_ICONERROR);
		return 1;
	}
	return 0;
}

void AppWin32::Run(int nShowCmd) {
	std::unique_ptr<ohms::Window> mainWnd = std::make_unique<ohms::MainWindow>();
	mainWnd->create(nShowCmd);
	MSG msg;
	while (GetMessageW(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
	mainWnd->destroy();
	return;
}

void AppWin32::Drop() {
	ohms::IHelper::drop();
	ohms::wgc::ICapture::drop();
	UniqueInstance::drop();
	return;
}
