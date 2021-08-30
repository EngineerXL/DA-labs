#include "iostream"
#include "vector.hpp"

struct TItem {
    static const size_t VALUE_SIZE = 65;

	uint16_t Key;
	char Value[VALUE_SIZE];
};

void CountingSort(TVector<TItem> & data, const int & n) {
	uint16_t maxKey = 0;
	for (int i = 0; i < n; ++i) {
		if (data[i].Key > maxKey) {
			maxKey = data[i].Key;
		}
	}
	TVector<uint64_t> count(maxKey + 1);
	for (int i = 0; i < n; ++i) {
		count[data[i].Key]++;
	}

	for (int i = 1; i < maxKey + 1; ++i) {
		count[i] = count[i] + count[i - 1];
	}
	TVector<TItem> res(n);
	for (int i = n - 1; i >= 0; --i) {
		res[count[data[i].Key] - 1] = data[i];
		count[data[i].Key]--;
	}
	for (int i = 0; i < n; ++i) {
		data[i] = res[i];
	}
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

	TVector<TItem> a;
	TItem elem;
    while (std::cin >> elem.Key >> elem.Value) {
        a.PushBack(elem);
    }
	CountingSort(a, a.Size());
	for (size_t i = 0; i < a.Size(); ++i) {
        std::cout << a[i].Key << " " << a[i].Value << "\n";
	}
	return 0;
}
