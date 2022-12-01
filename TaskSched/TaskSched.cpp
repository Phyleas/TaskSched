// TaskSched.cpp : Defines the entry point for the application.
//

#include "pch.h"
#include "TaskSched.h"
#include "MainFrame.h"
#include "SecurityHelper.h"

CAppModule _Module;

int Run(LPTSTR /*lpstrCmdLine*/ = nullptr, int nCmdShow = SW_SHOWDEFAULT) {
	CMessageLoop theLoop;
	_Module.AddMessageLoop(&theLoop);

	CMainFrame wndMain;

	if (wndMain.CreateEx() == nullptr) {
		ATLTRACE(_T("Main window creation failed!\n"));
		return 0;
	}

	wndMain.ShowWindow(nCmdShow);

	int nRet = theLoop.Run();

	_Module.RemoveMessageLoop();
	return nRet;
}

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow) {
	HRESULT hRes = ::CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
	ATLASSERT(SUCCEEDED(hRes));

	AtlInitCommonControls(ICC_COOL_CLASSES | ICC_BAR_CLASSES | ICC_LISTVIEW_CLASSES);

	hRes = _Module.Init(nullptr, hInstance);
	ATLASSERT(SUCCEEDED(hRes));

	::SetThreadPriority(::GetCurrentThread(), THREAD_PRIORITY_HIGHEST);
	if (SecurityHelper::IsRunningElevated())
		SecurityHelper::EnablePrivilege(SE_DEBUG_NAME);

	int nRet = Run(lpCmdLine, nCmdShow);

	_Module.Term();
	::CoUninitialize();

	return 0;
}


