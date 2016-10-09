#pragma once
#include <atomic>
#include <windows.h>

namespace gcore
{
    class Iocp
    {
    public:
        Iocp();
        virtual ~Iocp();

    public:
        bool create(DWORD threads);
        bool add(HANDLE handle, ULONG_PTR key);
        bool wait(LPDWORD bytes, PULONG_PTR key, LPOVERLAPPED* o, DWORD sleep);
        void close();

        bool enabled()      { return INVALID_HANDLE_VALUE != m_handle; }
        HANDLE handle()     { return m_handle; }

    private:
        HANDLE m_handle;
        std::atomic<int> m_count;
    };
}