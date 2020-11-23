#ifndef ITEM_HPP
#define ITEM_HPP

#include "vector.hpp"

const unsigned short MAX_KEY_SIZE = 256;

void Clear(char arr[MAX_KEY_SIZE + 1]) {
	for (unsigned long long i = 0; i < MAX_KEY_SIZE + 1; ++i) {
		arr[i] = 0;
	}
}

struct TItem {
	char Key[MAX_KEY_SIZE + 1];
	unsigned short KeySize;
	unsigned long long Value;
	TItem();
	TItem(const TItem & it);
	bool Empty();
	TItem & operator = (const TItem & it);
};

TItem::TItem () {
	Clear(Key);
	KeySize = 0;
	Value = 0;
}

TItem::TItem(const TItem & it) {
	KeySize = it.KeySize;
	Value = it.Value;
	for (unsigned short i = 0; i < MAX_KEY_SIZE + 1; ++i) {
		Key[i] = it.Key[i];
	}
}

TItem & TItem::operator = (const TItem & it) {
	KeySize = it.KeySize;
	Value = it.Value;
	for (unsigned short i = 0; i < MAX_KEY_SIZE + 1; ++i) {
		Key[i] = it.Key[i];
	}
	return *this;
}

bool TItem::Empty() {
	return KeySize == 0 ? true : false;
}

bool operator < (const TItem & lhs, const TItem & rhs) {
	for (unsigned short i = 0; i < Min(lhs.KeySize, rhs.KeySize); ++i) {
		if (lhs.Key[i] != rhs.Key[i]) {
			return lhs.Key[i] < rhs.Key[i];
		}
	}
	return lhs.KeySize < rhs.KeySize;
}

bool operator == (const TItem & lhs, const TItem & rhs) {
	if (lhs.KeySize != rhs.KeySize) {
		return false;
	}
	for (unsigned short i = 0; i < rhs.KeySize; ++i) {
		if (lhs.Key[i] != rhs.Key[i]) {
			return false;
		}
	}
	return true;
}

#endif /* ITEM_HPP */