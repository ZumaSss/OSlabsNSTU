#pragma hdrstop
#include "model.h"

RWorker::RWorker()
{
    //������� � ������ �����������, ���������� ��������
    hUpdateEvt = CreateEvent(NULL, TRUE, TRUE, NULL);
    //������� � ������ �����������, ���������� ����������
    hStopEvt = CreateEvent(NULL, TRUE, FALSE, NULL);
    //������, ���� ���������
    hMutex = CreateMutex(NULL, FALSE, NULL);

    waitingTime = 0;
    hThread = INVALID_HANDLE_VALUE; //����� ���� �� �������
}

RWorker::~RWorker()
{
    stopWork();  //���� ��������, ���������������
    CloseHandle(hUpdateEvt);
    CloseHandle(hStopEvt);
    CloseHandle(hMutex);
}

void    RWorker::startWork()
{
    if (hThread != INVALID_HANDLE_VALUE) return; //��� �������
    ResetEvent(hStopEvt); //����� ������� ������ ���������� ���� ���������
    hThread = CreateThread(NULL, 0, ThreadFunc, this, 0, NULL); //����������� � ������
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
    if (hThread == INVALID_HANDLE_VALUE) return; //�� �������
    SetEvent(hStopEvt); //������� ���� ���������
    //����, ����� ����� ������� ��� ���� � �����������
    if (WaitForSingleObject(hThread, 1000) != WAIT_OBJECT_0)
    {
        //�������� ���� �����, �� �����������, "��������" ������, ����������, ����� �� �������
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
    if (!_this) return 1; //������ ��� ���� ������, �� ����� ��������


    for (;;)
    {
        if (_this->waitingTime == 0) {
            _this->waitingTime = _this->getData();
        }
        else {

            //������� ������ ������
            _this->setData(_this->waitingTime);
            //������, ����� �� ���� ����� ������
            if (WaitForSingleObject(_this->hStopEvt, 1000) != WAIT_TIMEOUT)
                break;
        }
    }
    return 0;
}

#pragma package(smart_init)