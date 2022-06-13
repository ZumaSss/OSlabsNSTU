#include "framework.h"
#include "WindowsProject1.h"
#include "model.h"

#define MAX_LOADSTRING              100
#define OnButtonClickedCreate	    1
#define OnButtonClickedExit 2
#define OnButtonClickedTurnOn1      3
#define OnButtonClickedTurnOn2      4
#define OnButtonClickedTurnOn3      5
#define OnButtonClickedTurnOn4      6
#define OnButtonClickedTurnOn5      7
#define OnButtonClickedTurnOn6      8
#define OnButtonClickedTurnOff1     9
#define OnButtonClickedTurnOff2     10
#define OnButtonClickedTurnOff3     11
#define OnButtonClickedTurnOff4     12
#define OnButtonClickedTurnOff5     13
#define OnButtonClickedTurnOff6     14
#define OnButtonClickedAdd		      15
#define timerTick				            16

HWND hEditControl1;
HWND hEditControl2;
HWND hEditControl3;
HWND hEditControl4;
HWND hEditControl5;
HWND hEditControl6;

HWND hEditStatus1;
HWND hEditStatus2;
HWND hEditStatus3;
HWND hEditStatus4;
HWND hEditStatus5;
HWND hEditStatus6;

RWorker queue[6];

HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSPROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 770, 330, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   SetTimer(hWnd, timerTick, 100, (TIMERPROC)NULL);

   CreateWindowA("button", "Quick start", WS_VISIBLE | WS_CHILD | ES_CENTER, 5, 20, 120, 30, hWnd, (HMENU)OnButtonClickedCreate, NULL, NULL);
   CreateWindowA("button", "Add a client", WS_VISIBLE | WS_CHILD | ES_CENTER, 5, 60, 120, 30, hWnd, (HMENU)OnButtonClickedAdd, NULL, NULL);

   CreateWindowA("button", "Turn on", WS_VISIBLE | WS_CHILD | ES_CENTER, 150, 140, 75, 30, hWnd, (HMENU)OnButtonClickedTurnOn1, NULL, NULL);
   CreateWindowA("button", "Turn off", WS_VISIBLE | WS_CHILD | ES_CENTER, 150, 170, 75, 30, hWnd, (HMENU)OnButtonClickedTurnOff1, NULL, NULL);

   CreateWindowA("button", "Turn on", WS_VISIBLE | WS_CHILD | ES_CENTER, 250, 140, 75, 30, hWnd, (HMENU)OnButtonClickedTurnOn2, NULL, NULL);
   CreateWindowA("button", "Turn off", WS_VISIBLE | WS_CHILD | ES_CENTER, 250, 170, 75, 30, hWnd, (HMENU)OnButtonClickedTurnOff2, NULL, NULL);

   CreateWindowA("button", "Turn on", WS_VISIBLE | WS_CHILD | ES_CENTER, 350, 140, 75, 30, hWnd, (HMENU)OnButtonClickedTurnOn3, NULL, NULL);
   CreateWindowA("button", "Turn off", WS_VISIBLE | WS_CHILD | ES_CENTER, 350, 170, 75, 30, hWnd, (HMENU)OnButtonClickedTurnOff3, NULL, NULL);

   CreateWindowA("button", "Turn on", WS_VISIBLE | WS_CHILD | ES_CENTER, 450, 140, 75, 30, hWnd, (HMENU)OnButtonClickedTurnOn4, NULL, NULL);
   CreateWindowA("button", "Turn off", WS_VISIBLE | WS_CHILD | ES_CENTER, 450, 170, 75, 30, hWnd, (HMENU)OnButtonClickedTurnOff4, NULL, NULL);

   CreateWindowA("button", "Turn on", WS_VISIBLE | WS_CHILD | ES_CENTER, 550, 140, 75, 30, hWnd, (HMENU)OnButtonClickedTurnOn5, NULL, NULL);
   CreateWindowA("button", "Turn off", WS_VISIBLE | WS_CHILD | ES_CENTER, 550, 170, 75, 30, hWnd, (HMENU)OnButtonClickedTurnOff5, NULL, NULL);

   CreateWindowA("button", "Turn on", WS_VISIBLE | WS_CHILD | ES_CENTER, 650, 140, 75, 30, hWnd, (HMENU)OnButtonClickedTurnOn6, NULL, NULL);
   CreateWindowA("button", "Turn off", WS_VISIBLE | WS_CHILD | ES_CENTER, 650, 170, 75, 30, hWnd, (HMENU)OnButtonClickedTurnOff6, NULL, NULL);

   hEditStatus1 = CreateWindowA("edit", "Status", WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_NUMBER, 150, 65, 75, 20, hWnd, NULL, NULL, NULL);
   hEditStatus2 = CreateWindowA("edit", "Status", WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_NUMBER, 250, 65, 75, 20, hWnd, NULL, NULL, NULL);
   hEditStatus3 = CreateWindowA("edit", "Status", WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_NUMBER, 350, 65, 75, 20, hWnd, NULL, NULL, NULL);
   hEditStatus4 = CreateWindowA("edit", "Status", WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_NUMBER, 450, 65, 75, 20, hWnd, NULL, NULL, NULL);
   hEditStatus5 = CreateWindowA("edit", "Status", WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_NUMBER, 550, 65, 75, 20, hWnd, NULL, NULL, NULL);
   hEditStatus6 = CreateWindowA("edit", "Status", WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_NUMBER, 650, 65, 75, 20, hWnd, NULL, NULL, NULL);

   hEditControl1 = CreateWindowA("edit", "1", WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_NUMBER, 150, 110, 75, 20, hWnd, NULL, NULL, NULL);
   hEditControl2 = CreateWindowA("edit", "2", WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_NUMBER, 250, 110, 75, 20, hWnd, NULL, NULL, NULL);
   hEditControl3 = CreateWindowA("edit", "3", WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_NUMBER, 350, 110, 75, 20, hWnd, NULL, NULL, NULL);
   hEditControl4 = CreateWindowA("edit", "4", WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_NUMBER, 450, 110, 75, 20, hWnd, NULL, NULL, NULL);
   hEditControl5 = CreateWindowA("edit", "5", WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_NUMBER, 550, 110, 75, 20, hWnd, NULL, NULL, NULL);
   hEditControl6 = CreateWindowA("edit", "6", WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_NUMBER, 650, 110, 75, 20, hWnd, NULL, NULL, NULL);

   CreateWindowA("button", "Exit", WS_VISIBLE | WS_CHILD | ES_CENTER, 5, 220, 120, 30, hWnd, (HMENU)OnButtonClickedExit, NULL, NULL);

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
        switch (wParam) 
        {
        case OnButtonClickedCreate:
            queue[0].startWork();
            queue[1].startWork();
            queue[2].startWork();
            queue[3].startWork();
            queue[4].startWork();
            queue[5].startWork();

            queue[0].addClient(1);
            queue[1].addClient(2);
            queue[2].addClient(3);
            queue[3].addClient(4);
            queue[4].addClient(5);
            queue[5].addClient(6);

            break;

        case OnButtonClickedTurnOn1:
            queue[0].startWork();
            
            break;
        case OnButtonClickedTurnOff1:
            queue[0].stopWork();

            break;
        case OnButtonClickedTurnOn2:
            queue[1].startWork();

            break;
        case OnButtonClickedTurnOff2:
            queue[1].stopWork();

            break;
        case OnButtonClickedTurnOn3:
            queue[2].startWork();

            break;
        case OnButtonClickedTurnOff3:
            queue[2].stopWork();

            break;
        case OnButtonClickedTurnOn4:
            queue[3].startWork();

            break;
        case OnButtonClickedTurnOff4:
            queue[3].stopWork();

            break;
        case OnButtonClickedTurnOn5:
            queue[4].startWork();

            break;
        case OnButtonClickedTurnOff5:
            queue[4].stopWork();

            break;
        case OnButtonClickedTurnOn6:
            queue[5].startWork();

            break;
        case OnButtonClickedTurnOff6:
            queue[5].stopWork();

            break;
        case OnButtonClickedExit:
            for (int i = 0; i < 6; i++)
                queue[i].stopWork();
            ExitThread(0);
            PostQuitMessage(0);
            break;
        case OnButtonClickedAdd:
            int index = -1;
            int minValue = INT_MAX;
            for (int i = 0; i < 6; i++) {
                if (queue[i].isWorking() == true) {
                    {
                        if (minValue > queue[i].clientsCount()) {
                            minValue = queue[i].clientsCount();
                            index = i;
                        }
                    }                 
                }               
             }
            queue[index].addClient();
            
            break;
      
        }
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_TIMER:

        switch (wParam)
        {
        case timerTick:
            int time = queue[0].getTime();
            wchar_t buff[256];
            swprintf(buff, 256, L"T: %d", time);
            SetWindowText(hEditControl1, buff);

            time = queue[1].getTime();
            swprintf(buff, 256, L"T: %d", time);
            SetWindowText(hEditControl2, buff);

            time = queue[2].getTime();
            swprintf(buff, 256, L"T: %d", time);
            SetWindowText(hEditControl3, buff);

            time = queue[3].getTime();
            swprintf(buff, 256, L"T: %d", time);
            SetWindowText(hEditControl4, buff);

            time = queue[4].getTime();
            swprintf(buff, 256, L"T: %d", time);
            SetWindowText(hEditControl5, buff);

            time = queue[5].getTime();
            swprintf(buff, 256, L"К: %d", time);
            SetWindowText(hEditControl6, buff);


            int clients = queue[0].clientsCount();
            if (!queue[0].isWorking()) SetWindowText(hEditStatus1, L"Inactive");
            else if (queue[0].isWorking() and queue[0].clientsCount() == 0)
                SetWindowText(hEditStatus1, L"Free");
            else if (queue[0].isWorking()) {
                swprintf(buff, 256, L"K: %d", clients);
                SetWindowText(hEditStatus1, buff);
            }           
            

            clients = queue[1].clientsCount();
            if (!queue[1].isWorking()) SetWindowText(hEditStatus2, L"Inactive");
            else if (queue[1].isWorking() and queue[1].clientsCount() == 0)
                SetWindowText(hEditStatus2, L"Free");
            else if (queue[1].isWorking()) {
                swprintf(buff, 256, L"K: %d", clients);
                SetWindowText(hEditStatus2, buff);
            }         

            clients = queue[2].clientsCount();
            if (!queue[2].isWorking()) SetWindowText(hEditStatus3, L"Inactive");
            else if (queue[2].isWorking() and queue[2].clientsCount() == 0)
                SetWindowText(hEditStatus3, L"Free");
            else if (queue[2].isWorking()) {
                swprintf(buff, 256, L"K: %d", clients);
                SetWindowText(hEditStatus3, buff);
            }

            clients = queue[3].clientsCount();
            if (!queue[3].isWorking()) SetWindowText(hEditStatus4, L"Inactive");
            else if (queue[3].isWorking() and queue[3].clientsCount() == 0)
                SetWindowText(hEditStatus4, L"Free");
            else if (queue[3].isWorking()) {
                swprintf(buff, 256, L"K: %d", clients);
                SetWindowText(hEditStatus4, buff);
            }

            clients = queue[4].clientsCount();
            if (!queue[4].isWorking()) SetWindowText(hEditStatus5, L"Inactive");
            else if (queue[4].isWorking() and queue[4].clientsCount() == 0)
                SetWindowText(hEditStatus5, L"Free");
            else if (queue[4].isWorking()) {
                swprintf(buff, 256, L"K: %d", clients);
                SetWindowText(hEditStatus5, buff);
            }           

            clients = queue[5].clientsCount();
            if (!queue[5].isWorking()) SetWindowText(hEditStatus6, L"Inactive");
            else if (queue[5].isWorking() and queue[5].clientsCount() == 0)
                SetWindowText(hEditStatus6, L"Free");
            else if (queue[5].isWorking()) {
                swprintf(buff, 256, L"K: %d", clients);
                SetWindowText(hEditStatus6, buff);
            }         

            return 0;

        }
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
