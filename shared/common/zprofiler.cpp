#include <iostream>

#include "zprofiler.h"

zprofiler::zprofiler(const std::string& name, size_t critical) :
    m_name(name),
    m_critical(critical)
{
    m_start = std::chrono::high_resolution_clock::now();
}

zprofiler::~zprofiler()
{
    auto end = std::chrono::high_resolution_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - m_start).count();
    if(ms > m_critical) {
        std::cout << "profiler " << m_name << ": " << ms << " ms" << std::endl;
    }
}
