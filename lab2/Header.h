#include <Windows.h>
#include <TlHelp32.h>
#include <tchar.h>
#include <string>
#include <vector>
#include <codecvt>

#pragma once

#define OnButtonClickedCreate	1
#define OnButtonClickedExit		2
#define Option1 10001
#define Option2 10002
#define Option3 10003

HWND hEditControl1;
HWND hEditControl2;

HANDLE hThread1;
HANDLE hThread2;

LRESULT CALLBACK SoftwareMainProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
WNDCLASS NewWindowClass(HBRUSH BGColor, HCURSOR Cursor, HINSTANCE hInst, HICON Icon, LPCWSTR Name, WNDPROC Procedure);
void MainWndAddWidgets(HWND hWnd);

std::vector<INT> logThread1;
std::vector<INT> logThread2;

INT GlobalData = 100;

CRITICAL_SECTION CriticalSection;

HANDLE mut = CreateMutexA(NULL, false, NULL);