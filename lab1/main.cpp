#include "Header.h"

std::vector<HANDLE> hProcessContainer;


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

LRESULT CALLBACK SoftwareMainProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
	STARTUPINFO sti;
	PROCESS_INFORMATION pi;
	memset(&sti, 0, sizeof(sti));
	memset(&pi, 0, sizeof(pi));
	sti.cb = sizeof(sti);

	DWORD excode;
	BOOL bCreateProcess = false;


	switch (msg) {
	case WM_COMMAND:
		switch (wp) {
		case OnButtonClickedCreate:
			bCreateProcess = CreateProcess(L"C:\\Users\\ivana\\Desktop\\Project2\\x64\\Release\\Project2.exe",
				NULL, NULL, NULL, false, 0, NULL, NULL, &sti, &pi);
			
			if (bCreateProcess) {
				CloseHandle(pi.hThread);
				hProcessContainer.push_back(pi.hProcess);

			}
			else MessageBoxA(hWnd, "Error while creating a child process!", "Warning", MB_OK);

			break;
		case OnButtonClickedClose:
			if (!hProcessContainer.empty()) {
				////WaitForSingleObject(hProcessContainer.back(), INFINITE);
				GetExitCodeProcess(hProcessContainer.back(), &excode);

				if (excode == STILL_ACTIVE)
					TerminateProcess(hProcessContainer.back(), NULL);

				CloseHandle(hProcessContainer.back());
				hProcessContainer.pop_back();
			} else MessageBoxA(hWnd, "Here is no child process!", "Warning", MB_OK);

			break;
		case OnButtonClickedExit:
			PostQuitMessage(0);
			break;
		default:
			break;
		}
		break;

	case WM_CREATE:
		MainWndAddWidgets(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default: 
		return DefWindowProc(hWnd, msg, wp, lp);
	}
}

void MainWndAddWidgets(HWND hWnd) {
	CreateWindowA("static", "Hello World!", WS_VISIBLE | WS_CHILD | ES_CENTER, 5, 5, 490, 20, hWnd, NULL, NULL, NULL);

	CreateWindowA("button", "Create a process", WS_VISIBLE | WS_CHILD | ES_CENTER, 5, 30, 120, 30, hWnd, (HMENU)OnButtonClickedCreate, NULL, NULL);

	CreateWindowA("button", "Close a process", WS_VISIBLE | WS_CHILD | ES_CENTER, 5, 70, 120, 30, hWnd, (HMENU)OnButtonClickedClose, NULL, NULL);

	CreateWindowA("button", "Exit", WS_VISIBLE | WS_CHILD | ES_CENTER, 5, 110, 120, 30, hWnd, (HMENU)OnButtonClickedExit, NULL, NULL);
}


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {

	WNDCLASS SoftwareMainClass = NewWindowClass((HBRUSH)COLOR_WINDOW, LoadCursor(NULL, IDC_ARROW), hInst, LoadIcon(NULL, IDI_QUESTION), L"MainWndClass", SoftwareMainProcedure);

	if (!RegisterClassW(&SoftwareMainClass)) return -1;

	MSG SoftwareMainMessage = { 0 };

	CreateWindow(L"MainWndClass", L"OS lab1", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 500, 250, NULL, NULL, NULL, NULL);
	while (GetMessage(&SoftwareMainMessage, NULL, NULL, NULL)) {
		TranslateMessage(&SoftwareMainMessage);
		DispatchMessage(&SoftwareMainMessage);
	}

	return 0;
}