
#include <catch2/catch.hpp> // for BENCHMARK()

#include <fmt/core.h> // for format()

#include "sequences-fixed.hpp"


TEST_CASE("Fixed-length sequences")
{
    auto alphabet = FixedAlphabet{ 'c', 'd', 'e', 'f', 'g', 'a', 'b' };

    BENCHMARK(fmt::format("fixedSequences(), A={}, L={}", alphabetSize, wordLength))
    {
        return fixedSequences(alphabet);
    };
    BENCHMARK(fmt::format("fixedSequencesWithoutRepetition(), A={}, L={}", alphabetSize, wordLength))
    {
        return fixedSequencesWithoutRepetition(alphabet);
    };
}
