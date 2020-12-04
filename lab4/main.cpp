#include <cstdio>
#include "search.hpp"

void Clear(char arr[MAX_WORD_SIZE]) {
	for (unsigned short i = 0; i < MAX_WORD_SIZE; ++i) {
		arr[i] = 0;
	}
}

int main() {
	bool flagPatternText = 1;
	std::vector<TWord> pattern;
	std::vector<TWord> text;
	TWord cur;
	Clear(cur.Word);
	char c = getchar();
	unsigned short j = 0;
	while (c > 0) {
		if (c == '\n') {
			if (j > 0) {
				text.push_back(cur);
				Clear(cur.Word);
				j = 0;
			}
			++cur.StringId;
			if (flagPatternText) {
				std::swap(pattern, text);
				flagPatternText = 0;
				cur.StringId = 1;
			}
			cur.WordId = 1;
		} else if (c == '\t' or c == ' ') {
			if (j > 0) {
				text.push_back(cur);
				Clear(cur.Word);
				j = 0;
				++cur.WordId;
			}
		} else {
			if ('A' <= c and c <= 'Z') {
				c = c + 'a' - 'A';
			}
			cur.Word[j] = c;
			++j;
		}
	    c = getchar();
	}
	if (j > 0) {
		text.push_back(cur);
	}
	std::vector<unsigned int> ans = KMPStrong(pattern, text);
	for (const unsigned int & id : ans) {
		printf("%d, %d\n", text[id].StringId, text[id].WordId);
	}
}