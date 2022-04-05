#include <Windows.h>
#include <TlHelp32.h>
#include <tchar.h>
#include <string>
#include <vector>

#pragma once

#define OnButtonClickedCreate	1
#define OnButtonClickedClose	2
#define OnButtonClickedExit		3


LRESULT CALLBACK SoftwareMainProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
WNDCLASS NewWindowClass(HBRUSH BGColor, HCURSOR Cursor, HINSTANCE hInst, HICON Icon, LPCWSTR Name, WNDPROC Procedure);
void MainWndAddWidgets(HWND hWnd);
