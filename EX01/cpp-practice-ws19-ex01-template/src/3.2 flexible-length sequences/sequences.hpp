
#ifndef INCLUDED_CPP_PRACTICE_EX01_SEQUENCES_HPP_
#define INCLUDED_CPP_PRACTICE_EX01_SEQUENCES_HPP_


#include <vector>


using Alphabet = std::vector<char>;
using Word = std::vector<char>;

std::vector<Word> sequences(Alphabet const& alphabet, int wordLength);
std::vector<Word> sequencesWithoutRepetition(Alphabet const& alphabet, int wordLength);


#endif // INCLUDED_CPP_PRACTICE_EX01_SEQUENCES_HPP_
