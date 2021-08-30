#include "iostream"
#include "vector.hpp"

struct TItem {
    static const size_t RADIX_COUNT = 4;
    static const size_t RADIX_SIZE = 16;
    static const uint64_t RADIX_MASK = (1ull << RADIX_SIZE) - 1;
    static const size_t VALUE_SIZE = 65;

	uint64_t Key;
	char Value[VALUE_SIZE];

    uint64_t GetRadix(const size_t n) {
        return (Key >> (RADIX_SIZE * n)) & RADIX_MASK;
    }
};

void RadixSort(TVector<TItem> & data, const int & n) {
    for (size_t radix = 0; radix < TItem::RADIX_COUNT; ++radix) {
    	uint64_t maxKey = 0;
    	for (int i = 0; i < n; ++i) {
    		if (data[i].GetRadix(radix) > maxKey) {
    			maxKey = data[i].GetRadix(radix);
    		}
    	}
    	TVector<uint64_t> count(maxKey + 1);
    	for (int i = 0; i < n; ++i) {
    		count[data[i].GetRadix(radix)]++;
    	}

    	for (uint64_t i = 1; i < maxKey + 1; ++i) {
    		count[i] = count[i] + count[i - 1];
    	}
    	TVector<TItem> res(n);
    	for (int i = n - 1; i >= 0; --i) {
    		res[count[data[i].GetRadix(radix)] - 1] = data[i];
    		count[data[i].GetRadix(radix)]--;
    	}
    	for (int i = 0; i < n; ++i) {
    		data[i] = res[i];
    	}
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
	RadixSort(a, a.Size());
	for (size_t i = 0; i < a.Size(); ++i) {
        std::cout << a[i].Key << " " << a[i].Value << "\n";
	}
	return 0;
}
