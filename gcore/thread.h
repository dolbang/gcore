
#include <thread>
#include <atomic>
#pragma once
#include <mutex>
#include <deque>
#include <memory>

namespace gcore
{
    class Thread
    {
    public:
        Thread();
        virtual ~Thread();

    public:
        void begin();
        void close();
        void join();

    protected:
        virtual void onBegin();
        virtual void onRun();
        virtual void onEnd();

    private:
        static void run(Thread* o);

    private:
        std::thread* m_thread;
        std::atomic<bool> m_running;
    };

    class ThreadQ
    {
    public:
        using Element = std::shared_ptr<Thread>;

    public:
        ThreadQ();
        virtual ~ThreadQ();

    public:
        void add(Element& v);
        void close();

    private:
        std::mutex m_lock;
        std::deque<Element> m_q;
    };
}