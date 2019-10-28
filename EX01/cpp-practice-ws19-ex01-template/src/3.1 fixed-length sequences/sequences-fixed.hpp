
#ifndef INCLUDED_CPP_PRACTICE_EX01_SEQUENCES_FIXED_HPP_
#define INCLUDED_CPP_PRACTICE_EX01_SEQUENCES_FIXED_HPP_


#include <array>
#include <vector>
#include <cstddef> // for size_t


constexpr std::size_t alphabetSize = 7;
using FixedAlphabet = std::array<char, alphabetSize>;

constexpr std::size_t wordLength = 3;
using FixedWord = std::array<char, wordLength>;

std::vector<FixedWord> fixedSequences(FixedAlphabet const& alphabet);
std::vector<FixedWord> fixedSequencesWithoutRepetition(FixedAlphabet const& alphabet);


#endif // INCLUDED_CPP_PRACTICE_EX01_SEQUENCES_FIXED_HPP_
