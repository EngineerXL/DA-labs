#include "iostream"
#include "vector.hpp"

struct TString {
    static const size_t MAX_STRING_SIZE = 2049;

    size_t Size;
	char* Data;

    TString() {
        Size = 0;
        Data = nullptr;
    }

    TString(const char str[MAX_STRING_SIZE]) {
        for (size_t i = 0; i < MAX_STRING_SIZE; ++i) {
            if (str[i] == 0) {
                Size = i;
                break;
            }
        }
        Data = new char[Size];
        for (size_t i = 0; i < Size; ++i) {
            Data[i] = str[i];
        }
    }

    TString & operator = (const TString & another) {
        delete [] Data;
        Size = another.Size;
        Data = new char[Size];
        for (size_t i = 0; i < Size; ++i) {
            Data[i] = another.Data[i];
        }
        return *this;
    }

    friend std::ostream & operator << (std::ostream & out, const TString & str) {
        for (size_t i = 0; i < str.Size; ++i) {
            out << str.Data[i];
        }
        return out;
    }

    ~TString() {
        delete [] Data;
    }
};

struct TItem {
	uint16_t Key;
    size_t Value;
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
    TVector<TString> strings;
	TItem elem;
    char tmpValue[TString::MAX_STRING_SIZE];
    while (std::cin >> elem.Key >> tmpValue) {
        elem.Value = a.Size();
        a.PushBack(elem);
        strings.PushBack(TString(tmpValue));
    }
	CountingSort(a, a.Size());
	for (size_t i = 0; i < a.Size(); ++i) {
        std::cout << a[i].Key << " " << strings[a[i].Value] << "\n";
	}
	return 0;
}
