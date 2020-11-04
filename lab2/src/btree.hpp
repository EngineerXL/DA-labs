#ifndef BTREE_HPP
#define BTREE_HPP

#include "vector.hpp"

const unsigned long long TREE_DEGREE = 2;

template<class T>
struct TBtreeNode {
	TVector<T> Data;
	TVector<TBtreeNode*> Childs;
	TBtreeNode() : Data(1), Childs(2) {}
	~TBtreeNode();
};

template<class T>
void SaveNode(const int & id, TBtreeNode<int>* & node, TVector< TVector<T> > & vec) {
	if (node != nullptr) {
		for (unsigned long long i = 0; i < node->Data.Size(); ++i) {
			vec[id][i] = node->Data[i];
		}
		for (unsigned long long i = 0; i < node->Childs.Size(); ++i) {
			SaveNode(id * (2 * TREE_DEGREE - 1) + i + 1, node->Childs[i], vec);
		}
	}
}

template<class T>
TBtreeNode<T>* LoadNode(const unsigned long long & id, TBtreeNode<int>* & node, TVector< TVector<T> > & vec) {
	if (id >= vec.Size() or vec[id][0] == 0llu) {
		return nullptr;
	}
	node = new TBtreeNode<T>;
	node->Data[0] = vec[id][0];
	for (unsigned long long i = 1; i < TREE_DEGREE * 2 - 2; ++i) {
		if (vec[id][i] == 0llu) {
			break;
		} else {
			node->Data.PushBack(vec[id][i]);
		}
	}
	node->Childs.Resize(node->Data.Size() + 1);
	for (unsigned long long i = 0; i < node->Childs.Size(); ++i) {
		node->Childs[i] = LoadNode(id * (2 * TREE_DEGREE - 1) + i + 1, node->Childs[i], vec);
	}
	return node;
}

template<class T>
TBtreeNode<T>::~TBtreeNode() {
	for (unsigned long long i = 0; i < Childs.Size(); ++i) {
		delete Childs[i];
	}
}

template<class T>
unsigned long long TreeHeight(TBtreeNode<T>* node) {
	if (node != nullptr) {
		unsigned long long res = 0;
		for (unsigned long long i = 0; i < node->Childs.Size(); ++i) {
			res = Max(res, TreeHeight(node->Childs[i]));
		}
		return res + 1;
	} else {
		return 0;
	}
}

template<class T>
void EraseNode(TBtreeNode<T>* & node, const T & elem) {
	TBtreeNode<T>* curNode = node;
	TVector< TBtreeNode<T>* > path;
	TVector<unsigned long long> indexes;
	unsigned long long index = BinSearch(curNode->Data, elem);
	while (1) {
		path.PushBack(curNode);
		indexes.PushBack(index);
		if (index < curNode->Data.Size() and curNode->Data[index] == elem) {
			break;
		}
		curNode = curNode->Childs[index];
		index = BinSearch(curNode->Data, elem);
	}
	if (curNode->Childs[index] != nullptr) {
			TBtreeNode<T>* curPathNode = curNode->Childs[index];
			while (curPathNode->Childs[curPathNode->Childs.Size() - 1] != nullptr) {
				curPathNode = curPathNode->Childs[curPathNode->Childs.Size() - 1];
			}
			T value = curPathNode->Data[curPathNode->Data.Size() - 1];
			EraseNode(node, value);
			curNode->Data[index] = value;
			return;
	}
	while (path.Size() > 1) {
		TBtreeNode<T>* curPathNode = path[path.Size() - 1];
		path.PopBack();
		unsigned long long curPathIndex = indexes[indexes.Size() - 1];
		indexes.PopBack();
		if (curPathNode->Data.Size() == TREE_DEGREE - 1) {
			TBtreeNode<T>* curPathNodeParent = path[path.Size() - 1];
			unsigned long long curPathIndexParent = indexes[indexes.Size() - 1];
			TBtreeNode<T>* leftBrother = nullptr;
			if (curPathIndexParent > 0) {
				leftBrother = curPathNodeParent->Childs[curPathIndexParent - 1];
			}
			if (leftBrother != nullptr and leftBrother->Data.Size() > TREE_DEGREE - 1) {
				curPathNode->Data.Erase(curPathIndex);
				curPathNode->Childs.Erase(curPathIndex);
				curPathNode->Data.Insert(0, curPathNodeParent->Data[curPathIndexParent - 1]);
				curPathNode->Childs.Insert(0, leftBrother->Childs[leftBrother->Childs.Size() - 1]);
				curPathNodeParent->Data[curPathIndexParent - 1] = leftBrother->Data[leftBrother->Data.Size() - 1];
				leftBrother->Data.PopBack();
				leftBrother->Childs.PopBack();
				return;
			}
			TBtreeNode<T>* rightBrother = nullptr;
			if (curPathIndexParent < curPathNodeParent->Childs.Size() - 1) {
				rightBrother = curPathNodeParent->Childs[curPathIndexParent + 1];	
			}
			if (rightBrother != nullptr and rightBrother->Data.Size() > TREE_DEGREE - 1) {
				curPathNode->Data.Erase(curPathIndex);
				curPathNode->Childs.Erase(curPathIndex);
				curPathNode->Data.PushBack(curPathNodeParent->Data[curPathIndexParent]);
				curPathNode->Childs.PushBack(rightBrother->Childs[0]);
				curPathNodeParent->Data[curPathIndexParent] = rightBrother->Data[0];
				rightBrother->Data.Erase(0);
				rightBrother->Childs.Erase(0);
				return;
			}
			curPathNode->Data.Erase(curPathIndex);
			curPathNode->Childs.Erase(curPathIndex);
			TBtreeNode<T>* newNode = new TBtreeNode<T>;
			newNode->Data.Resize(2 * TREE_DEGREE - 2);
			newNode->Childs.Resize(2 * TREE_DEGREE - 1);
			if (leftBrother != nullptr) {
				indexes.PopBack();
				indexes.PushBack(curPathIndexParent - 1);
				for (unsigned long long i = 0; i < TREE_DEGREE - 1; ++i) {
					newNode->Data[i] = leftBrother->Data[i];
					newNode->Childs[i] = leftBrother->Childs[i];
				}
				newNode->Data[TREE_DEGREE - 1] = curPathNodeParent->Data[curPathIndexParent - 1];
				newNode->Childs[TREE_DEGREE - 1] = leftBrother->Childs[TREE_DEGREE - 1];
				for (unsigned long long i = 0; i < TREE_DEGREE - 2; ++i) {
					newNode->Data[TREE_DEGREE + i] = curPathNode->Data[i];
					newNode->Childs[TREE_DEGREE + i] = curPathNode->Childs[i];
				}
				newNode->Childs[2 * TREE_DEGREE - 2] = curPathNode->Childs[TREE_DEGREE - 2];
				for (unsigned long long i = 0; i < leftBrother->Childs.Size(); ++i) {
					leftBrother->Childs[i] = nullptr;
				}
				delete leftBrother;
				for (unsigned long long i = 0; i < curPathNode->Childs.Size(); ++i) {
					curPathNode->Childs[i] = nullptr;
				}
				delete curPathNode;
				curPathNodeParent->Childs[curPathIndexParent] = newNode;
				curPathNodeParent->Childs[curPathIndexParent - 1] = nullptr;
			} else if (rightBrother != nullptr) {
				for (unsigned long long i = 0; i < TREE_DEGREE - 2; ++i) {
					newNode->Data[i] = curPathNode->Data[i];
					newNode->Childs[i] = curPathNode->Childs[i];
				}
				newNode->Data[TREE_DEGREE - 2] = curPathNodeParent->Data[curPathIndexParent];
				newNode->Childs[TREE_DEGREE - 2] = curPathNode->Childs[TREE_DEGREE - 2];
				for (unsigned long long i = 0; i < TREE_DEGREE - 1; ++i) {
					newNode->Data[TREE_DEGREE - 1 + i] = rightBrother->Data[i];
					newNode->Childs[TREE_DEGREE - 1 + i] = rightBrother->Childs[i];
				}
				newNode->Childs[2 * TREE_DEGREE - 2] = rightBrother->Childs[TREE_DEGREE - 1];
				for (unsigned long long i = 0; i < curPathNode->Childs.Size(); ++i) {
					curPathNode->Childs[i] = nullptr;
				}
				delete curPathNode;
				for (unsigned long long i = 0; i < rightBrother->Childs.Size(); ++i) {
					rightBrother->Childs[i] = nullptr;
				}
				delete rightBrother;
				curPathNodeParent->Childs[curPathIndexParent] = nullptr;
				curPathNodeParent->Childs[curPathIndexParent + 1] = newNode;
			}
		} else {
			curPathNode->Data.Erase(curPathIndex);
			curPathNode->Childs.Erase(curPathIndex);
			return;
		}
	}
	TBtreeNode<T>* curPathNode = path[path.Size() - 1];
	path.PopBack();
	unsigned long long curPathIndex = indexes[indexes.Size() - 1];
	indexes.PopBack();
	if (curPathNode->Data.Size() > 1) {
		curPathNode->Data.Erase(curPathIndex);
		curPathNode->Childs.Erase(curPathIndex);
	} else {
		if (curPathNode->Childs[0] == nullptr) {
			node = curPathNode->Childs[1];
			curPathNode->Childs[1] = nullptr;
		} else if (curPathNode->Childs[1] == nullptr) {
			node = curPathNode->Childs[0];
			curPathNode->Childs[0] = nullptr;
		}
		delete curPathNode;
	}
}

template<class T>
void InsertNode(TBtreeNode<T>* & node, TBtreeNode<T>* & toInsertNode, const T & elem) {
	unsigned long long index = BinSearch(node->Data, elem);
	if (node->Childs[index] == nullptr) {
		node->Data.Insert(index, elem);
		node->Childs.Insert(index, nullptr);
	} else {
		TBtreeNode<T>* newToInsertNode = nullptr;
		InsertNode(node->Childs[index], newToInsertNode, elem);
		if (newToInsertNode != nullptr) {
			node->Childs[index] = newToInsertNode->Childs[1];
			node->Data.Insert(index, newToInsertNode->Data[0]);
			node->Childs.Insert(index, newToInsertNode->Childs[0]);
			newToInsertNode->Childs[0] = nullptr;
			newToInsertNode->Childs[1] = nullptr;
			delete newToInsertNode;
		}
	}
	if (node->Data.Size() == 2 * TREE_DEGREE - 1) {
		TBtreeNode<T>* leftNode = new TBtreeNode<T>;
		leftNode->Data.Resize(TREE_DEGREE - 1);
		leftNode->Childs.Resize(TREE_DEGREE);
		TBtreeNode<T>* rightNode = new TBtreeNode<T>;
		rightNode->Data.Resize(TREE_DEGREE - 1);
		rightNode->Childs.Resize(TREE_DEGREE);
		for (unsigned long long i = 0; i < TREE_DEGREE - 1; ++i) {
			leftNode->Data[i] = node->Data[i];
			leftNode->Childs[i] = node->Childs[i];
			rightNode->Data[i] = node->Data[TREE_DEGREE + i];
			rightNode->Childs[i] = node->Childs[TREE_DEGREE + i];
		}
		leftNode->Childs[TREE_DEGREE - 1] = node->Childs[TREE_DEGREE - 1];
		rightNode->Childs[TREE_DEGREE - 1] = node->Childs[2 * TREE_DEGREE - 1];
		TBtreeNode<T>* midNode = new TBtreeNode<T>;
		midNode->Data[0] = node->Data[TREE_DEGREE - 1];
		midNode->Childs[0] = leftNode;
		midNode->Childs[1] = rightNode;
		toInsertNode = midNode;
		for (unsigned long long i = 0; i < 2 * TREE_DEGREE; ++i) {
			node->Childs[i] = nullptr;
		}
		delete node;
	}
}

template<class T>
class TBtree {
public:
	TBtreeNode<T>* Root;
public:
	TBtree();
	~TBtree();
	void Erase(const T & elem);
	void Find(TBtreeNode<T>* & res, unsigned long long & pos,const T & elem);
	void Insert(const T & elem);
	void WriteInFile(FILE* file);
	void LoadFromFile(FILE* file);
};

/* Class methods implementation */

template<class T>
TBtree<T>::TBtree() {
	Root = nullptr;
}

template<class T>
TBtree<T>::~TBtree() {
	delete Root;
}

template<class T>
void TBtree<T>::Erase(const T & elem) {
	EraseNode(Root, elem);
}

template<class T>
void TBtree<T>::Find(TBtreeNode<T>* & res, unsigned long long & pos, const T & elem) {
	TBtreeNode<T>* node = Root;
	while (node != nullptr) {
		unsigned long long index = BinSearch(node->Data, elem);
		if (elem == node->Data[index]) {
			res = node;
			pos = index;
			return;
		} else {
			node = node->Childs[index];
		}
	}
	res = nullptr;
}

template<class T>
void TBtree<T>::Insert(const T & elem) {
	if (Root == nullptr) {
		Root = new TBtreeNode<T>;
		Root->Data[0] = elem;
		Root->Childs[0] = nullptr;
		Root->Childs[1] = nullptr;
	} else {
		TBtreeNode<T>* toInsertNode = nullptr;
		InsertNode(Root, toInsertNode, elem);
		if (toInsertNode != nullptr) {
			Root = toInsertNode;
		}
	}
}

template<class T>
void TBtree<T>::WriteInFile(FILE* file) {
	unsigned long long height = TreeHeight(Root);
	unsigned long long compactTreeSize = 0;
	for (unsigned long long i = 0; i < height; ++i) {
		compactTreeSize = compactTreeSize + Pow(2 * TREE_DEGREE - 1, i);
	}
	TVector< TVector<T> > compactData(compactTreeSize, TVector<T>(TREE_DEGREE * 2 - 2));
	SaveNode(0, Root, compactData);
	for (unsigned long long i = 0; i < compactTreeSize; ++i) {
		for(unsigned long long j = 0; j < compactData[i].Size(); ++j) {
			fwrite(&compactData[i][j], sizeof(T), 1, file);
		}
	}
}

template<class T>
void TBtree<T>::LoadFromFile(FILE* file) {
	TVector< TVector<T> > compactData;
	compactData.PushBack(TVector<T>());
	T elem;
	unsigned long long i = 0, j = 0;
	while (fread(&elem, sizeof(T), 1, file) > 0) {
		compactData[i].PushBack(elem);
		++j;
		if (j == TREE_DEGREE * 2 - 2) {
			compactData.PushBack(TVector<T>());
			j = 0;
			++i;
		}
	}
	compactData.PopBack();
	delete Root;
	LoadNode(0, Root, compactData);
	for (unsigned long long i = 0; i < compactData.Size(); ++i) {
		for(unsigned long long j = 0; j < compactData[i].Size(); ++j) {
			printf("%d ", compactData[i][j]);
		}
		printf("\n");
	}
}

#endif /* BTREE_HPP */