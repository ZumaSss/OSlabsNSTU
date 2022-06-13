#ifndef workerH
#define workerH
#include <windows.h>
#include <ctime>
#include <queue>
#include <algorithm>


//Вспомогательный класс, очень помогает защищать данные.
//Защищает данные буквально до самой смерти
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
    HANDLE hUpdateEvt; //событие "данные обновились"
    HANDLE hStopEvt;   //событие "конец работы"

    HANDLE hMutex;  //защита данных
        
    HANDLE hThread; //дескриптор потока

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