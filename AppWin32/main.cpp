#include "framework.h"
#include "UniqueInstance.h"
#include "Window/Global.h"
#include "Capture/Capture.h"
#include "Capture/Saver.h"
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
		ohms::global::hInst = hInstance;

		winrt::init_apartment(winrt::apartment_type::single_threaded);
		ohms::global::g_app = std::move(std::make_unique<ohms::capture::wgc::Capture>());
		ohms::global::g_app->Initialize();

		ohms::Saver::init();
	}
	// Run
	{
		ohms::MainWindow mainWnd;
		mainWnd.create(nShowCmd);
		MSG msg;
		while (GetMessageW(&msg, NULL, 0, 0)) {
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}
		mainWnd.destroy();
	}
	// Clear
	{
		ohms::Saver::drop();

		ohms::global::g_app->Stop();
		ohms::global::g_app.reset();

		ohms::global::hInst = 0;
	}
	UniqueInstance::drop();
	return 0;
}
