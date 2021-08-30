#ifndef VECTOR_HPP
#define VECTOR_HPP

template<class T>
class TVector {
private:
	size_t Capacity;
	size_t MaxSize;
	T * Data;
public:
	void Assign(const size_t & n, T elem);
	void Clear();
	void PushBack(T elem);
	size_t Size();
	TVector();
	TVector(const size_t & n);
	TVector(const size_t & n, T elem);
	TVector(const TVector<T> & another);
	~TVector();
	T & operator[](const size_t & index);
};

template<class T>
void TVector<T>::Assign(const size_t & n, T elem) {
	for (size_t i = 0; i < n; ++i) {
		Data[i] = elem;
	}
}

template<class T>
void TVector<T>::Clear() {
	Capacity = 0;
	MaxSize = 0;
	delete [] Data;
	Data = nullptr;
}

template<class T>
void TVector<T>::PushBack(T elem) {
	if (Data == nullptr) {
		MaxSize = 1;
		Data = new T[MaxSize];
	} else if (Capacity == MaxSize) {
		MaxSize = 2 * MaxSize;
		T * newData = new T[MaxSize];
		for (size_t i = 0; i < Capacity; ++i) {
			newData[i] = Data[i];
		}
		delete[] Data;
		Data = newData;
	}
	Data[Capacity++] = elem;
}

template<class T>
size_t TVector<T>::Size() {
	return Capacity;
}

template<class T>
TVector<T>::TVector() {
	Capacity = 0;
	MaxSize = 0;
	Data = nullptr;
}

template<class T>
TVector<T>::TVector(const size_t & n) {
	Capacity = 2 * n;
	MaxSize = n;
	Data = new T[Capacity];
	Assign(n, T());
}

template<class T>
TVector<T>::TVector(const size_t & n, T elem) {
	Capacity = 2 * n;
	MaxSize = n;
	Data = new T[Capacity];
	Assert(n, elem);
}

template<class T>
TVector<T>::TVector(const TVector<T> & another) {
	Capacity = another.Capacity;
	MaxSize = another.MaxSize;
	Data = new T[Capacity];
	for (size_t i = 0; i < Capacity; ++i) {
		Data[i] = another.Data[i];
	}
}

template<class T>
TVector<T>::~TVector() {
	delete [] Data;
}

template<class T>
T & TVector<T>::operator[](const size_t & index) {
	return Data[index];
}

#endif /* VECTOR_HPP */
