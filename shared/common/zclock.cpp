#include <common/zclock.h>

#include <chrono>

ztime get_millis()
{
    auto now = std::chrono::high_resolution_clock::now();
    auto duration = now.time_since_epoch();
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    return static_cast<ztime>(millis);
}
