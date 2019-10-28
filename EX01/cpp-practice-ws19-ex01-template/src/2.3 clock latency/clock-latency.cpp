
#include <chrono>   // for high_resolution_clock, duration<>
#include <iostream>

#include <fmt/core.h> // for format()


using Clock = std::chrono::high_resolution_clock;
using DNanoseconds = std::chrono::duration<double, std::nano>;


DNanoseconds measureClockLatency(void)
{
    // TODO: implement
    return { };
}

int main()
{
    DNanoseconds clockLatency = measureClockLatency();

    std::cout << fmt::format("Clock latency: {} ns\n", clockLatency.count());
}
