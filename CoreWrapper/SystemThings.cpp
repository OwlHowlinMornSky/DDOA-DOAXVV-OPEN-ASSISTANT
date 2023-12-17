#include "SystemThings.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

void Wrapper::SystemThings::SetCloseEnabled(System::IntPtr hwnd, System::Boolean enabled) {
	HMENU hmenu = GetSystemMenu((HWND)(void*)hwnd, FALSE);
	EnableMenuItem(hmenu, SC_CLOSE, enabled ? MF_ENABLED : MF_GRAYED);
}
