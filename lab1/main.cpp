#include "sort.hpp"
#include <stdio.h>

signed main() {
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);

	mystd::vector< mystd::pair<unsigned short, unsigned long long> > a;
	unsigned short key;
	unsigned long long value;
	mystd::pair<unsigned short, unsigned long long> cur;
	while (scanf("%hu%llu", &key, &value) > 0) {
		cur.first() = key;
		cur.second() = value;
		a.push_back(cur);
	}
	int n = a.size();
	mystd::counting_sort(a, n);
	for (int i = 0; i < n; i++) {
		printf("%hu %llu\n", a[i].first(), a[i].second());
	}
	return 0;
}