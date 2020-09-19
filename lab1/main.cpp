#include "vector.hpp"
#include <stdio.h>

struct item {
	unsigned short key;
	unsigned long long value;
};

void counting_sort(mystd::vector<item> &data, int n) {
	int maxkey = 0;
	for (int i = 0; i < n; i++) {
		if (data[i].key > maxkey) {
			maxkey = data[i].key;
		}
	}
	mystd::vector<int> count(maxkey + 1);
	for (int i = 0; i < n; i++) {
		count[data[i].key]++;
	}

	for (int i = 1; i < maxkey + 1; i++) {
		count[i] = count[i] + count[i - 1];
	}
	mystd::vector<item> res(n);
	for (int i = n - 1; i >= 0; i--) {
		res[count[data[i].key] - 1] =  data[i];
		count[data[i].key]--;
	}
	for (int i = 0; i < n; i++) {
		data[i] = res[i];
	}
}

signed main() {
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);

	mystd::vector<item> a;
	item cur;
	while (scanf("%hu%llu", &cur.key, &cur.value) > 0) {
		a.push_back(cur);
	}
	int n = a.size();
	counting_sort(a, n);
	for (int i = 0; i < n; i++) {
		printf("%hu %llu\n", a[i].key, a[i].value);
	}
	return 0;
}