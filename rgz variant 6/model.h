#ifndef workerH
#define workerH
#include <windows.h>
#include <ctime>
#include <queue>
#include <algorithm>


//��������������� �����, ����� �������� �������� ������.
//�������� ������ ��������� �� ����� ������
class RMutexLocker
{
    HANDLE hMutex;
public:
    RMutexLocker(HANDLE mutex)
        :hMutex(mutex)
    {
        WaitForSingleObject(hMutex, INFINITE);
    }
    ~RMutexLocker()
    {
        ReleaseMutex(hMutex);
    }
};

class RWorker
{
    HANDLE hUpdateEvt; //������� "������ ����������"
    HANDLE hStopEvt;   //������� "����� ������"

    HANDLE hMutex;  //������ ������
        
    HANDLE hThread; //���������� ������

    std::queue<INT> clients;
    int waitingTime;
public:
    RWorker();
    ~RWorker();

    int     getData();
    void    setData(int& val);

    void    addClient();
    void    addClient(int count);
    void    startWork();
    void    stopWork();
    int     getTime();
    int     clientsCount();
    bool    isWorking();


private:
    static DWORD WINAPI ThreadFunc(LPVOID ptr);
};

#endif