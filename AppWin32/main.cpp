#include "UniqueInstance.h"

#include "Window/framework.h"
#include <ohms/WGC.h>
#include "Helper/IHelper.h"

#include "Window/MainWindow.h"

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
		auto wgc = ohms::wgc::getInstance();
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
	}
	// Run
	{
		std::unique_ptr<ohms::Window> mainWnd =
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
		ohms::IHelper::drop();
		ohms::wgc::drop();
	}
	UniqueInstance::drop();
	return 0;
}
