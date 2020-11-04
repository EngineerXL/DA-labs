#ifndef VECTOR_HPP
#define VECTOR_HPP

const unsigned long long SHRINK_FACTOR = 4;
const unsigned long long MIN_VECTOR_SIZE = 2;

template<class T>
class TVector {
private:
	T* Data;
	unsigned long long DataCurSize;
	unsigned long long DataMaxSize;
public:
	TVector();
	TVector(const unsigned long long n);
	TVector(const unsigned long long n, const T & elem);
	TVector(const TVector & vec);
	~TVector();

	bool Empty();
	void Erase(const unsigned long long & pos);
	void Insert(const unsigned long long & pos, const T & elem);
	void PopBack();
	void PushBack(const T & elem);
	void Resize(const unsigned long long & n);
	unsigned long long Size();

	T & operator [] (const unsigned long long & index);
	TVector & operator = (const TVector & vec);
};

/* Useful functions */

template<class T>
void Swap(T & lhs, T & rhs) {
	T tmp = lhs;
	lhs = rhs;
	rhs = tmp;
}

template<class T>
T Max(const T & lhs, const T & rhs) {
	return lhs > rhs ? lhs : rhs;
}

template<class T>
T Min(const T & lhs, const T & rhs) {
	return lhs < rhs ? lhs : rhs;
}

template<class T>
unsigned long long BinSearch(TVector<T> & vec, const T & elem) {
	long long l = -1;
	long long r = (long long)vec.Size();
	while (l + 1 < r) {
		long long m = (l + r) / 2;
		if (vec[m] < elem) {
			l = m;
		} else {
			r = m;
		}
	}
	return (unsigned long long)r;
}

unsigned long long Pow(unsigned long long x, unsigned long long y) {
	unsigned long long res = 1;
	while (y) {
		if (y & 1) {
			res = res * x;
		}
		y = y >> 1;
		x = x * x;
	}
	return res;
}

/* Class methods implementation */

template<class T>
TVector<T>::TVector() {
	DataCurSize = 0;
	DataMaxSize = MIN_VECTOR_SIZE;
	Data = new T[DataMaxSize];
}

template<class T>
TVector<T>::TVector(const unsigned long long n) {
	DataCurSize = Max(0llu, n);
	DataMaxSize = Max(2llu * n, MIN_VECTOR_SIZE);
	Data = new T[DataMaxSize];
	for (unsigned long long i = 0; i < DataCurSize; ++i) {
		Data[i] = T();
	}
}

template<class T>
TVector<T>::TVector(const unsigned long long n, const T & elem) {
	DataCurSize = Max(0llu, n);
	DataMaxSize = Max(2llu * n, MIN_VECTOR_SIZE);
	Data = new T[DataMaxSize];
	for (unsigned long long i = 0; i < DataCurSize; ++i) {
		Data[i] = elem;
	}
}

template<class T>
TVector<T>::TVector(const TVector<T> & vec) {
	DataCurSize = vec.DataCurSize;
	DataMaxSize = vec.DataMaxSize;
	Data = new T[DataMaxSize];
	for (unsigned long long i = 0; i < DataCurSize; ++i) {
		Data[i] = vec.Data[i];
	}
}

template<class T>
TVector<T>::~TVector() {
	if (Data != nullptr) {
		delete [] Data;
	}
}

template<class T>
void TVector<T>::Erase(const unsigned long long & pos) {
	if (pos < DataCurSize) {
		for (unsigned long long i = pos; i < DataCurSize - 1; ++i) {
			Data[i] = Data[i + 1];
		}
	}
	PopBack();
}

template<class T>
void TVector<T>::Insert(const unsigned long long & pos, const T & elem) {
	if (pos < DataCurSize) {
		PushBack(T());
		for (unsigned long long i = DataCurSize - 1; i > pos; --i) {
			Data[i] = Data[i - 1];
		}
		Data[pos] = elem;
	} else {
		PushBack(elem);
	}
}

template<class T>
void TVector<T>::PopBack() {
	if (DataCurSize > 0) {
		--DataCurSize;
		if (SHRINK_FACTOR * DataCurSize < DataMaxSize) {
			Resize(DataCurSize);
		}
	}
}

template<class T>
void TVector<T>::PushBack(const T & elem) {
	if (DataCurSize == DataMaxSize) {
		DataMaxSize = DataMaxSize * 2;
		T* TmpData = new T[DataMaxSize];
		for (unsigned long long i = 0; i < DataCurSize; ++i) {
			TmpData[i] = Data[i];
		}
		delete [] Data;
		Data = TmpData;
	}
	Data[DataCurSize++] = elem;
}

template<class T>
void TVector<T>::Resize(const unsigned long long & n) {
	DataMaxSize = Max(2 * n, MIN_VECTOR_SIZE);
	T* TmpData = new T[DataMaxSize];
	if (n < DataCurSize) {
		for (unsigned long long i = 0; i < n; ++i) {
			TmpData[i] = Data[i];
		}
	} else {
		for (unsigned long long i = 0; i < DataCurSize; ++i) {
			TmpData[i] = Data[i];
		}
		for (unsigned long long i = DataCurSize; i < n; ++i) {
			TmpData[i] = T();
		}
	}
	delete [] Data;
	Data = TmpData;
	DataCurSize = n;
}

template<class T>
unsigned long long TVector<T>::Size() {
	return DataCurSize;
}

template<class T>
T & TVector<T>::operator [] (const unsigned long long & index) {
	return Data[index];
}

template<class T>
TVector<T> & TVector<T>::operator = (const TVector<T> & vec) {
	Resize(vec.DataCurSize);
	for (unsigned long long i = 0; i < vec.DataCurSize; ++i) {
		Data[i] = vec.Data[i];
	}
	return *this;
}

#endif /* VECTOR_HPP */