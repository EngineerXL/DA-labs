#ifndef SEARCH_HPP
#define SEARCH_HPP

#include <algorithm>
#include <vector>

const unsigned short MAX_WORD_SIZE = 16;

struct TWord {
	char Word[MAX_WORD_SIZE];
	unsigned int StringId, WordId;
};

std::vector<unsigned int> PrefixFunction(const std::vector<TWord> & s);
std::vector<unsigned int> KMPWeak(const std::vector<TWord> & pattern, const std::vector<TWord> & text);

std::vector<unsigned int> ZFunction(const std::vector<TWord> & s);
std::vector<unsigned int> StrongPrefixFunction(const std::vector<TWord> & s);
std::vector<unsigned int> KMPStrong(const std::vector<TWord> & pattern, const std::vector<TWord> & text);

#endif /* SEARCH_HPP */