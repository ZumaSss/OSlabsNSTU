#include <windows.h> 
#include <TlHelp32.h>

LRESULT CALLBACK SoftwareMainProcedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
WNDCLASS NewWindowClass(HBRUSH BGColor, HCURSOR Cursor, HINSTANCE hInst, HICON Icon, LPCWSTR Name, WNDPROC Procedure);
void MainWndAddWidgets(HWND hWnd);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow)
{
	WNDCLASS SoftwareMainClass = NewWindowClass((HBRUSH)COLOR_WINDOW, LoadCursor(NULL, IDC_ARROW), hInst, LoadIcon(NULL, IDI_QUESTION),
		L"MainWndClass", SoftwareMainProcedure);
	if (!RegisterClass(&SoftwareMainClass)) { return -1; }
	MSG SoftwareMainMessage = { 0 };

	CreateWindow(L"MainWndClass", L"Child process", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 400, 100, NULL, NULL, NULL, NULL);
	while (GetMessage(&SoftwareMainMessage, NULL, NULL, NULL))
	{

		TranslateMessage(&SoftwareMainMessage);
		DispatchMessage(&SoftwareMainMessage);
	}
}

WNDCLASS NewWindowClass(HBRUSH BGColor, HCURSOR Cursor, HINSTANCE hInst, HICON Icon, LPCWSTR Name, WNDPROC Procedure)
{
	WNDCLASS NWC = { 0 };

	NWC.hbrBackground = BGColor;
	NWC.hCursor = Cursor;
	NWC.hInstance = hInst;
	NWC.hIcon = Icon;
	NWC.lpszClassName = Name;
	NWC.lpfnWndProc = Procedure;

	return NWC;
}

LRESULT CALLBACK SoftwareMainProcedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{

	switch (msg)
	{
	case WM_CREATE:
		MainWndAddWidgets(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default: return DefWindowProc(hwnd, msg, wp, lp);
	}
}

void MainWndAddWidgets(HWND hWnd)
{
	CreateWindowA("Static", "Hello World! I'm a child process.", WS_VISIBLE | WS_CHILD | ES_CENTER, 5, 5, 390, 20, hWnd, NULL, NULL, NULL);
}