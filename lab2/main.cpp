#include "Header.h"


WNDCLASS NewWindowClass(HBRUSH BGColor, HCURSOR Cursor, HINSTANCE hInst, HICON Icon, LPCWSTR Name, WNDPROC Procedure) {
	WNDCLASS NWC = { 0 };

	NWC.hIcon = Icon;
	NWC.hCursor = Cursor;
	NWC.hInstance = hInst;
	NWC.lpszClassName = Name;
	NWC.hbrBackground = BGColor;
	NWC.lpfnWndProc = Procedure;

	return NWC;
}

void AddText(HWND hWnd, const TCHAR* text)
{
	SendMessage(hWnd, EM_SETSEL, -1, -1);
	SendMessage(hWnd, EM_REPLACESEL, FALSE, reinterpret_cast<LPARAM>(text));
}

DWORD WINAPI ThreadFunc1(LPVOID lpParameter) {
	std::string log;
	std::wstring wide;

	for (int i = 0; i < 50; i++) {
		GlobalData += 1;
		Sleep(1);
		GlobalData -= 1;
		logThread1.push_back(GlobalData);
	}
	for (std::vector<INT>::iterator it = logThread1.begin(); it != logThread1.end(); ++it) {
		log = "";
		log += std::to_string(*it);
		log += "\n";
		wide = std::wstring(log.begin(), log.end());
		AddText(hEditControl1, wide.c_str());	
	}
	
	return 0;
}

DWORD WINAPI ThreadFunc2(LPVOID lpParameter) {
	std::string log;
	std::wstring wide;
	for (int i = 0; i < 50; i++) {
		GlobalData -= 1;
		Sleep(1);
		GlobalData += 1;
		logThread2.push_back(GlobalData);
	}
	for (std::vector<INT>::iterator it = logThread2.begin(); it != logThread2.end(); ++it) {
		log = "";
		log += std::to_string(*it);
		log += "\n";
		wide = std::wstring(log.begin(), log.end());
		AddText(hEditControl2, wide.c_str());
		
	}

	return 0;
}

DWORD WINAPI ThreadFunc1Critical(LPVOID lpParameter) {
	std::string log;
	std::wstring wide;

	for (int i = 0; i < 50; i++) {
		EnterCriticalSection(&CriticalSection);
		GlobalData += 1;
		Sleep(1);
		GlobalData -= 1;
		logThread1.push_back(GlobalData);
		LeaveCriticalSection(&CriticalSection);
	}
	for (std::vector<INT>::iterator it = logThread1.begin(); it != logThread1.end(); ++it) {
		log = "";
		log += std::to_string(*it);
		log += "\n";
		wide = std::wstring(log.begin(), log.end());
		AddText(hEditControl1, wide.c_str());
	}

	return 0;
}

DWORD WINAPI ThreadFunc2Critical(LPVOID lpParameter) {
	std::string log;
	std::wstring wide;
	for (int i = 0; i < 50; i++) {
		EnterCriticalSection(&CriticalSection);
		GlobalData -= 1;
		Sleep(1);
		GlobalData += 1;
		logThread2.push_back(GlobalData);
		LeaveCriticalSection(&CriticalSection);
	}
	for (std::vector<INT>::iterator it = logThread2.begin(); it != logThread2.end(); ++it) {
		log = "";
		log += std::to_string(*it);
		log += "\n";
		wide = std::wstring(log.begin(), log.end());
		AddText(hEditControl2, wide.c_str());

	}

	return 0;
}

DWORD WINAPI ThreadFunc1Mutex(LPVOID lpParameter) {
	std::string log;
	std::wstring wide;
	DWORD result;

	for (int i = 0; i < 50; i++) {
		result = WaitForSingleObject(mut, 1);
		if (result == WAIT_OBJECT_0) {
			GlobalData += 1;
			Sleep(1);
			GlobalData -= 1;
			logThread1.push_back(GlobalData);
		}
		ReleaseMutex(mut);
	}			
	for (std::vector<INT>::iterator it = logThread1.begin(); it != logThread1.end(); ++it) {
		log = "";
		log += std::to_string(*it);
		log += "\n";
		wide = std::wstring(log.begin(), log.end());
		AddText(hEditControl1, wide.c_str());
	}

	return 0;
}

DWORD WINAPI ThreadFunc2Mutex(LPVOID lpParameter) {
	std::string log;
	std::wstring wide;
	DWORD result;
	
	for (int i = 0; i < 50; i++) {
		result = WaitForSingleObject(mut, 1);
		if (result == WAIT_OBJECT_0) {
			GlobalData -= 1;
			Sleep(1);
			GlobalData += 1;
			logThread2.push_back(GlobalData);
		}
		ReleaseMutex(mut);
	}
	for (std::vector<INT>::iterator it = logThread2.begin(); it != logThread2.end(); ++it) {
		log = "";
		log += std::to_string(*it);
		log += "\n";
		wide = std::wstring(log.begin(), log.end());
		AddText(hEditControl2, wide.c_str());
	}

	return 0;
}

void ExitProgram(void) {
	//DWORD excode;

	//GetExitCodeThread(hThread1, &excode);
	//if (excode == STILL_ACTIVE)
	//	TerminateThread(hThread1, 0);

	//GetExitCodeThread(hThread2, &excode);
	//if (excode == STILL_ACTIVE)
	//	TerminateThread(hThread2, 0);

	ExitThread(0);
	PostQuitMessage(0);
}

LRESULT CALLBACK SoftwareMainProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
	switch (msg) {
	case WM_COMMAND:
		switch (wp) {
		case OnButtonClickedCreate:
			if (IsDlgButtonChecked(hWnd, Option1) || IsDlgButtonChecked(hWnd, Option2) || IsDlgButtonChecked(hWnd, Option3)) {
				SetWindowText(hEditControl1, L"");
				SetWindowText(hEditControl2, L"");

				if (IsDlgButtonChecked(hWnd, Option1)) {
					hThread1 = CreateThread(NULL, 0, ThreadFunc1, NULL, 0, NULL);
					hThread2 = CreateThread(NULL, 0, ThreadFunc2, NULL, 0, NULL);

				}
				if (IsDlgButtonChecked(hWnd, Option2)) {
					hThread1 = CreateThread(NULL, 0, ThreadFunc1Critical, NULL, 0, NULL);
					hThread2 = CreateThread(NULL, 0, ThreadFunc2Critical, NULL, 0, NULL);

				}
				if (IsDlgButtonChecked(hWnd, Option3)) {
					hThread1 = CreateThread(NULL, 0, ThreadFunc1Mutex, NULL, 0, NULL);
					hThread2 = CreateThread(NULL, 0, ThreadFunc2Mutex, NULL, 0, NULL);

				}
			}
			else
				MessageBox(hWnd, L"Choose a radiobutton first!", L"Warning!", MB_OK);
				
			break;
		case OnButtonClickedExit:
			ExitProgram();
			break;
		default:
			break;
		}

		break;
	case WM_CREATE:
		MainWndAddWidgets(hWnd);
		break;
	case WM_DESTROY:
		ExitProgram();
		break;
	default:
		return DefWindowProc(hWnd, msg, wp, lp);
	}
}

void MainWndAddWidgets(HWND hWnd) {
	CreateWindowA("button", "Launch", WS_VISIBLE | WS_CHILD | ES_CENTER, 5, 20, 120, 30, hWnd, (HMENU)OnButtonClickedCreate, NULL, NULL);

	hEditControl1 = CreateWindowA("edit", "1st thread logs will show here!", WS_VISIBLE | WS_CHILD | ES_MULTILINE | WS_VSCROLL | ES_NUMBER, 150, 20, 250, 250, hWnd, NULL, NULL, NULL);
	hEditControl2 = CreateWindowA("edit", "2nd thread logs will show here!", WS_VISIBLE | WS_CHILD | ES_MULTILINE | WS_VSCROLL | ES_NUMBER, 400, 20, 250, 250, hWnd, NULL, NULL, NULL);

	CreateWindowA("button", "out of sync", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 5, 80, 100, 30, hWnd, (HMENU)Option1, NULL, NULL);
	CreateWindowA("button", "critical section", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 5, 110, 120, 30, hWnd, (HMENU)Option2, NULL, NULL);
	CreateWindowA("button", "mutex", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 5, 140, 100, 30, hWnd, (HMENU)Option3, NULL, NULL);

	CreateWindowA("button", "Exit", WS_VISIBLE | WS_CHILD | ES_CENTER, 5, 220, 120, 30, hWnd, (HMENU)OnButtonClickedExit, NULL, NULL);
}


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {
	if (!InitializeCriticalSectionAndSpinCount(&CriticalSection, 0x00000400))
		return 1;

	WNDCLASS SoftwareMainClass = NewWindowClass((HBRUSH)COLOR_WINDOW, LoadCursor(NULL, IDC_ARROW), hInst, LoadIcon(NULL, IDI_QUESTION), L"MainWndClass", SoftwareMainProcedure);

	if (!RegisterClassW(&SoftwareMainClass)) return -1;

	MSG SoftwareMainMessage = { 0 };

	CreateWindow(L"MainWndClass", L"OS lab2", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 700, 330, NULL, NULL, NULL, NULL);
	while (GetMessage(&SoftwareMainMessage, NULL, NULL, NULL)) {
		TranslateMessage(&SoftwareMainMessage);
		DispatchMessage(&SoftwareMainMessage);
	}
	CloseHandle(mut);
	DeleteCriticalSection(&CriticalSection);
	return 0;
}