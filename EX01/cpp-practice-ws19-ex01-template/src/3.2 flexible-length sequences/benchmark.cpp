
#include <numeric> // for iota()

#include <catch2/catch.hpp> // for BENCHMARK()

#include <fmt/core.h> // for format()

#include "sequences.hpp"


Alphabet generateAlphabet(int alphabetSize)
{
    auto result = Alphabet(std::size_t(alphabetSize));
    std::iota(result.begin(), result.end(), 'a');
    return result;
}


TEST_CASE("Flexible-length sequences")
{
    int alphabetSize = 9;
    auto alphabet = generateAlphabet(alphabetSize);

        // Cf. https://github.com/catchorg/Catch2/blob/master/docs/generators.md for documentation on GENERATE() and built-in generators.
    int wordLength = GENERATE(range(1, 10));

    BENCHMARK(fmt::format("sequences(), A={}, L={}", alphabetSize, wordLength))
    {
        return sequences(alphabet, wordLength);
    };
    BENCHMARK(fmt::format("sequencesWithoutRepetition(), A={}, L={}", alphabetSize, wordLength))
    {
        return sequencesWithoutRepetition(alphabet, wordLength);
    };
}
