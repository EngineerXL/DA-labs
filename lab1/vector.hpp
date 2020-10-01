#ifndef VECTOR_HPP
#define VECTOR_HPP

namespace NMystd {
	template<class T>
	class TVector {
		private:
			unsigned int Capacity;
			unsigned int MaxSize;
			T* Data;
		public:
			void Assert(const unsigned int &n, T elem);
			void PushBack(T elem);
			unsigned int Size();
			TVector();
			TVector(const unsigned int &n);
			TVector(const unsigned int &n, T elem);
			~TVector();
			T& operator[](const unsigned int &index);
	};

	template<class T>
	void TVector<T>::Assert(const unsigned int &n, T elem) {
		for (int i = 0; i < n; ++i) {
			Data[i] = elem;
		}
	}

	template<class T>
	void TVector<T>::PushBack(T elem) {
		if (Data == 0) {
			MaxSize = 1;
			Data = new T[MaxSize];
		} else if (Capacity == MaxSize) {
			MaxSize = MaxSize * 2;
			T* newData = new T[MaxSize];
			for (int i = 0; i < Capacity; ++i) {
				newData[i] = Data[i];
			}
			delete[] Data;
			Data = newData;
		}
		Data[Capacity] = elem;
		Capacity++;
	};

	template<class T>
	unsigned int TVector<T>::Size() {
		return Capacity;
	}

	template<class T>
	TVector<T>::TVector() {
		Capacity = 0;
		MaxSize = 0;
		Data = 0;
	}

	template<class T>
	TVector<T>::TVector(const unsigned int &n) {
		Capacity = n;
		MaxSize = n;
		Data = new T[Capacity];
		Assert(n, T());
	}

	template<class T>
	TVector<T>::TVector(const unsigned int &n, T elem) {
		Capacity = n;
		MaxSize = n;
		Data = new T[Capacity];
		Assert(n, elem);
	}

	template<class T>
	TVector<T>::~TVector() {
		delete[] Data;
	}

	template<class T>
	T& TVector<T>::operator[](const unsigned int &index) {
		return Data[index];
	}
}

#endif // VECTOR_HPP