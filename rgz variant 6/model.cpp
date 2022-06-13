#pragma hdrstop
#include "model.h"

RWorker::RWorker()
{
    //—обытие с ручным управлением, изначально активное
    hUpdateEvt = CreateEvent(NULL, TRUE, TRUE, NULL);
    //—обытие с ручным управлением, изначально неактивное
    hStopEvt = CreateEvent(NULL, TRUE, FALSE, NULL);
    //ћютекс, пока свободный
    hMutex = CreateMutex(NULL, FALSE, NULL);

    waitingTime = 0;
    hThread = INVALID_HANDLE_VALUE; //поток пока не запущен
}

RWorker::~RWorker()
{
    stopWork();  //если работали, останавливаемс€
    CloseHandle(hUpdateEvt);
    CloseHandle(hStopEvt);
    CloseHandle(hMutex);
}

void    RWorker::startWork()
{
    if (hThread != INVALID_HANDLE_VALUE) return; //уже запущен
    ResetEvent(hStopEvt); //перед началом работы сбрасываем флаг остановки
    hThread = CreateThread(NULL, 0, ThreadFunc, this, 0, NULL); //запускаемс€ в работу
}

void RWorker::addClient()
{
    srand(time(NULL));
    clients.push(1 + rand() % 10);
}

void RWorker::addClient(int count)
{
    while (count > 0) {
        srand(time(NULL));
        clients.push(1 + rand() % 10);
        count--;
    }
}

int RWorker::clientsCount()
{
    return clients.size();
}

bool RWorker::isWorking()
{
    return (hThread != INVALID_HANDLE_VALUE);
}

void    RWorker::stopWork()
{
    if (hThread == INVALID_HANDLE_VALUE) return; //не запущен
    SetEvent(hStopEvt); //взводим флаг остановки
    //ждем, когда поток заметит наш флаг и остановитс€
    if (WaitForSingleObject(hThread, 1000) != WAIT_OBJECT_0)
    {
        //прождали п€ть минут, не остановилс€, "приболел" видимо, пристрелим, чтобы не мучалс€
        TerminateThread(hThread, 1);
    }
    CloseHandle(hThread);
    hThread = INVALID_HANDLE_VALUE;
}

int  RWorker::getData()
{
    RMutexLocker guard(hMutex);
    if (clients.size() == 0) return 0;
    WaitForSingleObject(hThread, 1000);

    int time = clients.front();
    clients.pop();

    ResetEvent(hUpdateEvt);
    return time;
}

void RWorker::setData(int& waitingTime)
{
    RMutexLocker guard(hMutex);
    waitingTime--;
    SetEvent(hUpdateEvt);
}

int RWorker::getTime()
{
    return waitingTime;
}


DWORD WINAPI RWorker::ThreadFunc(LPVOID ptr)
{
    RWorker* _this = (RWorker*)ptr;
    if (!_this) return 1; //забыли нам дать объект, не будем работать


    for (;;)
    {
        if (_this->waitingTime == 0) {
            _this->waitingTime = _this->getData();
        }
        else {

            //сделаем важную работу
            _this->setData(_this->waitingTime);
            //поспим, гл€д€ на флаг конца работы
            if (WaitForSingleObject(_this->hStopEvt, 1000) != WAIT_TIMEOUT)
                break;
        }
    }
    return 0;
}

#pragma package(smart_init)