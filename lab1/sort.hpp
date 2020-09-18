#ifndef SORT_HPP
#define SORT_HPP

#include "pair.hpp"
#include "vector.hpp"

namespace mystd {
	template<class T1, class T2>
	void counting_sort(mystd::vector< mystd::pair<T1, T2> > &data, int n);
}

template<class T1, class T2>
void mystd::counting_sort(mystd::vector< mystd::pair<T1, T2> > &data, int n) {
	int maxkey = 0;
	for (int i = 0; i < n; i++) {
		if (data[i].first() > maxkey) {
			maxkey = data[i].first();
		}
	}
	mystd::vector<int> count(maxkey + 1);
	for (int i = 0; i < n; i++) {
		count[data[i].first()]++;
	}

	for (int i = 1; i < maxkey + 1; i++) {
		count[i] = count[i] + count[i - 1];
	}
	mystd::vector< mystd::pair<T1, T2> > res(n);
	for (int i = n - 1; i >= 0; i--) {
		res[count[data[i].first()] - 1] =  data[i];
		count[data[i].first()]--;
	}
	for (int i = 0; i < n; i++) {
		data[i] = res[i];
	}
}

#endif // SORT_HPP