#include "stdio.h"
#include "vector.hpp"

struct TItem {
	unsigned short Key;
	unsigned long long Value;
};

void CountingSort(NMystd::TVector<TItem> &data, int n) {
	int maxKey = 0;
	for (int i = 0; i < n; ++i) {
		if (data[i].Key > maxKey) {
			maxKey = data[i].Key;
		}
	}
	NMystd::TVector<int> count(maxKey + 1);
	for (int i = 0; i < n; ++i) {
		count[data[i].Key]++;
	}

	for (int i = 1; i < maxKey + 1; ++i) {
		count[i] = count[i] + count[i - 1];
	}
	NMystd::TVector<TItem> res(n);
	for (int i = n - 1; i >= 0; --i) {
		res[count[data[i].Key] - 1] =  data[i];
		count[data[i].Key]--;
	}
	for (int i = 0; i < n; ++i) {
		data[i] = res[i];
	}
}

signed main() {
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);

	NMystd::TVector<TItem> a;
	TItem cur;
	while (scanf("%hu%llu", &cur.Key, &cur.Value) > 0) {
		a.PushBack(cur);
	}
	int n = a.Size();
	CountingSort(a, n);
	for (int i = 0; i < n; ++i) {
		printf("%hu %llu\n", a[i].Key, a[i].Value);
	}
	return 0;
}