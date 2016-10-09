#include "stdafx.h"
#include "net.h"

namespace gcore
{
    Iocp::Iocp()
        : m_handle(INVALID_HANDLE_VALUE),
        m_count(0)
    {
    }

    Iocp::~Iocp()
    {
    }

    bool Iocp::create(DWORD threads)
    {
        if (enabled())
            return true;

        HANDLE iocp = ::CreateIoCompletionPort(
            INVALID_HANDLE_VALUE,
            NULL,
            0,
            threads);
        if (!iocp)
            return false;

        m_handle = iocp;
        m_count = 1;
        return true;
    }

    bool Iocp::add(HANDLE handle, ULONG_PTR key)
    {
        if (INVALID_HANDLE_VALUE == handle)
            return false;

        if (!enabled())
            return false;

        HANDLE iocp = ::CreateIoCompletionPort(
            handle,
            m_handle,
            key,
            0);
        if (!iocp)
            return false;

        ++m_count;
        return true;
    }

    bool Iocp::wait(LPDWORD bytes, PULONG_PTR key, LPOVERLAPPED* o, DWORD sleep)
    {
        if (!enabled())
            return false;

        return ::GetQueuedCompletionStatus(
            m_handle,
            bytes,
            key,
            o,
            sleep) ? true : false;
    }

    void Iocp::close()
    {
        if (!enabled())
            return;

        ::CloseHandle(m_handle);
        if (0 == --m_count)
            m_handle = INVALID_HANDLE_VALUE;
    }
}