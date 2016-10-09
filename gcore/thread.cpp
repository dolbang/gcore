#include "stdafx.h"
#include "thread.h"

namespace gcore
{
    Thread::Thread()
        : m_running(false),
        m_thread(nullptr)
    {
    }

    Thread::~Thread()
    {
        if (m_thread)
            delete m_thread;
    }

    void Thread::begin()
    {
        if (m_thread)
            return;
        m_running = true;
        m_thread = new std::thread(run, this);
    }

    void Thread::close()
    {
        m_running = false;
    }

    void Thread::join()
    {
        if (m_thread)
            m_thread->join();
    }

    void Thread::onBegin()
    {
    }

    void Thread::onRun()
    {
    }

    void Thread::onEnd()
    {
    }

    void Thread::run(Thread* o)
    {
        o->onBegin();
        while (o->m_running)
            o->onRun();
        o->onEnd();
    }

    ThreadQ::ThreadQ()
    {
    }

    ThreadQ::~ThreadQ()
    {
    }

    void ThreadQ::add(Element& v)
    {
        std::lock_guard<std::mutex> l(m_lock);
        m_q.push_back(v);
    }

    void ThreadQ::close()
    {
        std::lock_guard<std::mutex> l(m_lock);
        for (const auto& elem : m_q)
            elem->close();
        for (const auto& elem : m_q)
            elem->join();
        m_q.clear();
    }
}