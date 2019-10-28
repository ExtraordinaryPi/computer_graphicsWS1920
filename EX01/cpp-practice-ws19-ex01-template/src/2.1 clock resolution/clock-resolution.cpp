
#include <chrono>   // for high_resolution_clock, duration<>
#include <iostream>

#include <fmt/core.h> // for format()


using Clock = std::chrono::high_resolution_clock;
using DNanoseconds = std::chrono::duration<double, std::nano>;


// bad code
DNanoseconds measureClockResolution_bad()
{
    return Clock::now() - Clock::now();
}

DNanoseconds measureClockResolution()
{
    // TODO: implement
    return { };
}

int main()
{
    DNanoseconds clockResolution = measureClockResolution();

    std::cout << fmt::format("Clock resolution: {} ns\n", clockResolution.count());
}
