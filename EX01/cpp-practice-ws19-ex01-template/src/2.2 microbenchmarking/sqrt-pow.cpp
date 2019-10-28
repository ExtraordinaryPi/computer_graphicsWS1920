
#include <cmath>    // for sqrt(), pow()
#include <chrono>   // for high_resolution_clock, duration<>
#include <iostream>

#include <fmt/core.h> // for format()


using Clock = std::chrono::high_resolution_clock;
using DNanoseconds = std::chrono::duration<double, std::nano>;


DNanoseconds measureDuration_sqrt_bad(int iterations)
{
    double v = 42;
    auto t0 = Clock::now();
    for (int i = 0; i < iterations; ++i)
    {
        std::sqrt(v);
    }
    auto t1 = Clock::now();
    return DNanoseconds(t1 - t0) / iterations;
}
DNanoseconds measureDuration_pow_bad(int iterations)
{
    double v = 42;
    auto t0 = Clock::now();
    for (int i = 0; i < iterations; ++i)
    {
        std::pow(v, 0.5);
    }
    auto t1 = Clock::now();
    return DNanoseconds(t1 - t0) / iterations;
}


DNanoseconds measureDuration_sqrt(int iterations)
{
    // TODO: implement
    return { };
}
DNanoseconds measureDuration_pow(int iterations)
{
    // TODO: implement
    return { };
}

int main()
{
    int iterations = 10'100'000;

    DNanoseconds sqrtDuration = measureDuration_sqrt(iterations);
    DNanoseconds powDuration = measureDuration_pow(iterations);

    std::cout << fmt::format("sqrt(42): {} ns\n", sqrtDuration.count());
    std::cout << fmt::format("pow(42, 0.5): {} ns\n", powDuration.count());
}
