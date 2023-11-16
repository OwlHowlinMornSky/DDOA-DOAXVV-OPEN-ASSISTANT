#include "Window/framework.h"
#include "UniqueInstance.h"
#include "Global.h"
#include "Capture/Capture.h"
#include "Capture/Saver.h"
#include "Window/MainWindow.h"
#include "Helper/Helper.h"

#include "shellapi.h"

int CALLBACK wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nShowCmd
) {
	int cmdCnt = 0;
	LPWSTR* cmds = CommandLineToArgvW(lpCmdLine, &cmdCnt);
	for (int i = 0; i < cmdCnt; ++i) {
		if (std::wstring(cmds[i]) == L"-show") {
			ohms::global::show = true;
			break;
		}
	}

	if (!UniqueInstance::setup()) {
		MessageBoxW(NULL, L"Another instance is running.", L"DOAXVV-helper", MB_ICONERROR);
		return 1;
	}
	// Init
	{
		ohms::global::hInst = hInstance;
		ohms::global::capture = std::make_unique<ohms::capture::wgc::Capture>();
		ohms::Saver::init();

		auto helper = std::make_unique<ohms::Helper>();

		ohms::global::helper = std::move(helper);
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
