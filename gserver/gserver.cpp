// gserver.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "../gcore/thread.h"
#include "../gcore/net.h"


gcore::ThreadQ theThreadQ;
gcore::Iocp theIocp;

class WorkerThread : public gcore::Thread, public std::enable_shared_from_this<WorkerThread>
{
protected:
    virtual void onBegin()
    {
        OutputDebugString(L"onBegin()\r\n");
    }

    virtual void onRun()
    {
        DWORD bytes = 0;
        ULONG_PTR key = 0;
        LPOVERLAPPED o = nullptr;
        theIocp.wait(&bytes, &key, &o, 2000);
        OutputDebugString(L"onRun()\r\n");
    }

    virtual void onEnd()
    {
        OutputDebugString(L"onEnd()\r\n");
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
    theIocp.create(4);

    for (auto i = 0; i < 4; ++i)
    {
        std::shared_ptr<gcore::Thread> t = std::make_shared<WorkerThread>();
        t->begin();
        theThreadQ.add(t);
    }

    bool quit = false;
    while (!quit)
    {
        std::string cmd;
        std::cout << "Enter cmd:";
        std::getline(std::cin, cmd);
        if (0 == cmd.compare("quit"))
        {
            quit = true;
        }
    }

    theThreadQ.close();
    theIocp.close();
    return 0;
}
