#include <bits/stdc++.h>
#include "btree.hpp"

int main() {
	long double stdMapTime = 0;
	long double bTreeTime = 0;
	long double start, end;
	std::map<std::string, unsigned long long> mp;

	TBtree<TItem> btree;
	char q[MAX_KEY_SIZE + 1];
	unsigned short curSize = 0;
	unsigned long long curValue;
	TItem curItem;
	TBtreeNode<TItem>* curSearchNode;
	unsigned long long curSearchPos;
	while (scanf("%s", q) > 0) {
		if (q[0] == '+') {
			scanf("%s%llu", q, &curValue);
			for (unsigned short i = 0; i < MAX_KEY_SIZE + 1; ++i) {
				if ('A' <= q[i] and q[i] <= 'Z') {
					q[i] = q[i] - 'A' + 'a';
				}
				curItem.Key[i] = q[i];
				if (q[i] == 0) {
					curSize = i;
					break;
				}
			}
			curItem.KeySize = curSize;
			curItem.Value = curValue;
			curSearchNode = nullptr;
			curSearchPos = 0;

			// B-tree
			start = clock();
			btree.Find(curSearchNode, curSearchPos, curItem);
			if (curSearchNode == nullptr) {
				btree.Insert(curItem);
			}
			end = clock();
			bTreeTime = bTreeTime + end - start;

			// std::map
			start = clock();
			if (mp.find(curItem.Key) == mp.end()) {
				mp[curItem.Key] = curItem.Value;
			}
			end = clock();
			stdMapTime = stdMapTime + end - start;
		} else if (q[0] == '-') {
			scanf("%s", q);
			for (unsigned short i = 0; i < MAX_KEY_SIZE + 1; ++i) {
				if ('A' <= q[i] and q[i] <= 'Z') {
					q[i] = q[i] - 'A' + 'a';
				}
				curItem.Key[i] = q[i];
				if (q[i] == 0) {
					curSize = i;
					break;
				}
			}
			curItem.KeySize = curSize;
			curSearchNode = nullptr;
			curSearchPos = 0;

			// B-tree
			start = clock();
			btree.Find(curSearchNode, curSearchPos, curItem);
			if (curSearchNode != nullptr) {
				btree.Erase(curItem);
			}
			end = clock();
			bTreeTime = bTreeTime + end - start;

			// std::map
			start = clock();
			if (mp.find(curItem.Key) != mp.end()) {
				mp.erase(curItem.Key);
			}
			end = clock();
			stdMapTime = stdMapTime + end - start;

		} else {
			for (unsigned short i = 0; i < MAX_KEY_SIZE + 1; ++i) {
				if ('A' <= q[i] and q[i] <= 'Z') {
					q[i] = q[i] - 'A' + 'a';
				}
				curItem.Key[i] = q[i];
				if (q[i] == 0) {
					curSize = i;
					break;
				}
			}
			curItem.KeySize = curSize;
			curSearchNode = nullptr;
			curSearchPos = 0;
			// B-tree
			start = clock();
			btree.Find(curSearchNode, curSearchPos, curItem);
			end = clock();
			bTreeTime = bTreeTime + end - start;

			// std::map
			start = clock();
			mp.find(curItem.Key);
			end = clock();
			stdMapTime = stdMapTime + end - start;
		}
		Clear(curItem.Key);
	}
	printf("B-tree: %.3Lf ms\n", bTreeTime / 1000.0);
	printf("std::map: %.3Lf ms\n", stdMapTime / 1000.0);
	return 0;
}