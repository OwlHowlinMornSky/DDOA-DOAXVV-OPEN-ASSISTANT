#include "Window/framework.h"
#include "UniqueInstance.h"
#include "Global.h"
#include "Capture/Capture.h"
#include "Capture/Saver.h"
#include "Window/MainWindow.h"
#include "Helper/Helper.h"

int CALLBACK wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nShowCmd
) {
	if (!UniqueInstance::setup()) {
		MessageBoxW(NULL, L"Another instance is running.", L"DOAXVV-helper", MB_ICONERROR);
		return 1;
	}
	// Init
	{
		ohms::global::hInst = hInstance;
		ohms::global::capture = std::make_unique<ohms::capture::wgc::Capture>();
		ohms::Saver::init();
		ohms::global::helper = std::make_unique<ohms::Helper>();
	}
	// Run
	{
		std::unique_ptr<ohms::MainWindow> mainWnd =
			std::make_unique<ohms::MainWindow>();
		mainWnd->create(nShowCmd);
		MSG msg;
		while (GetMessageW(&msg, NULL, 0, 0)) {
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}
		mainWnd->destroy();
	}
	// Clear
	{
		ohms::global::helper.reset();
		ohms::Saver::drop();
		ohms::global::capture.reset();
		ohms::global::hInst = 0;
	}
	UniqueInstance::drop();
	return 0;
}
