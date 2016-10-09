#pragma once
#include <atomic>

namespace gcore
{
    class Counter
    {
    public:
        Counter() : m_count(0)  {}
        virtual ~Counter()      {}

    public:
        void clear()    { m_count = 0; }
        int get()       { return m_count; }
        int inc()       { return ++m_count; }
        int dec()       { return --m_count; }

    private:
        std::atomic<int> m_count;
    };
}