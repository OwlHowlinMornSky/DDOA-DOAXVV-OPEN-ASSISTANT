#include "AppWin32.h"
#include "Window/framework.h"

int CALLBACK wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nShowCmd
) {
	int code = 0;
	if (app.Init())
		return 1;
	try {
		app.Run(nShowCmd);
	}
	catch (...) {
		code = 1;
	}
	app.Drop();
	return code;
}
