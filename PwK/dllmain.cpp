#include "pch.h"
#include "PW.h"

DWORD WINAPI Main(HMODULE hModule)
{
	AllocConsole();
	HWND whConsole = GetConsoleWindow();
	RECT r;
	GetWindowRect(whConsole, &r);
	MoveWindow(whConsole, r.left, r.top, 700, 500, TRUE);
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);

	std::wstring title = L"pwk - PID: ";
	title.append(std::to_wstring(_getpid()));
	HWND hWindow = FindWindowW(L"ElementClient Window", NULL);
	SetConsoleTitle(title.c_str());
	SetWindowText(hWindow, title.c_str());

	PW pw;
	pw.StartAutoFarming();
	pw.StartAutoTrivia();

	if(f) fclose(f);
	FreeConsole();
	FreeLibraryAndExitThread(hModule, 0);
	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch(ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)Main, hModule, 0, nullptr);
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
