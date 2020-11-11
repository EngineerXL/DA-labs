#include <stdio.h>
#include "btree.hpp"

// Use this to debug your B-tree!
// void Print(TBtreeNode<TItem>* node, int depth) {
// 	if (node != nullptr) {
// 		for (unsigned long long i = 0; i < node->Data.Size(); ++i) {
// 			Print(node->Childs[i], depth + 1);
// 			for (int j = 0; j < 4 * depth; ++j) {
// 				printf(" ");
// 			}
// 			printf("%s %d %llu\n", node->Data[i].Key, node->Data[i].KeySize, node->Data[i].Value);
// 		}
// 		Print(node->Childs[node->Data.Size()], depth + 1);
// 	}
// }

int main() {
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
			btree.Find(curSearchNode, curSearchPos, curItem);
			if (curSearchNode != nullptr) {
				printf("Exist\n");
			} else {
				btree.Insert(curItem);
				printf("OK\n");
			}
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
			btree.Find(curSearchNode, curSearchPos, curItem);
			if (curSearchNode != nullptr) {
				btree.Erase(curItem);
				printf("OK\n");
			} else {
				printf("NoSuchWord\n");
			}
		} else if (q[0] == '!') {
			scanf("%s", q);
			if (q[0] == 'L') {
				scanf("%s", q);
				FILE* toReadFile = nullptr;
				toReadFile = fopen(q, "rb");
				if (toReadFile == nullptr) {
					printf("ERROR: error opening file to read!\n");
				} else {
					btree.LoadFromFile(toReadFile);
					printf("OK\n");
					fclose(toReadFile);
				}
			} else {
				scanf("%s", q);
				FILE* toWriteFile = nullptr;
				toWriteFile = fopen(q, "wb");
				if (toWriteFile == nullptr) {
					printf("ERROR: error opening file to write!\n");
				} else {
					btree.WriteInFile(toWriteFile);
					printf("OK\n");
					fclose(toWriteFile);
				}
			}
		}else {
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
			btree.Find(curSearchNode, curSearchPos, curItem);
			if (curSearchNode != nullptr) {
				printf("OK: %llu\n", curSearchNode->Data[curSearchPos].Value);
			} else {
				printf("NoSuchWord\n");
			}
		}
		Clear(curItem.Key);
	}
	return 0;
}