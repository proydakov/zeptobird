#pragma once

#include <chrono>
#include <string>

class zprofiler final
{
public:
    zprofiler(const std::string& name, size_t critical);
    ~zprofiler();

private:
    std::string m_name;
    std::size_t m_critical;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_start;
};
