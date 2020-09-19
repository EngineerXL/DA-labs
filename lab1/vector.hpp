#ifndef VECTOR_HPP
#define VECTOR_HPP

namespace mystd {
	template<class T>
	class vector {
		private:
			unsigned int capacity;
			unsigned int maxsize;
			T* data;
		public:
			void assert(const unsigned int n, T elem);
			T& operator[](const unsigned int &index);
			void push_back(T elem);
			unsigned int size();
			vector();
			vector(const unsigned int n);
			vector(const unsigned int n, T elem);
			~vector();
			void f();
	};

	template<class T>
	void vector<T>::assert(const unsigned int n, T elem) {
		for (int i = 0; i < n; i++) {
			data[i] = elem;
		}
	}

	template<class T>
	T& vector<T>::operator[](const unsigned int &index) {
		return data[index];
	}

	template<class T>
	void vector<T>::push_back(T elem) {
		if (data == 0) {
			maxsize = 1;
			data = new T[maxsize];
		}
		if (capacity == maxsize) {
			maxsize = maxsize * 2;
			T* new_data = new T[maxsize];
			for (int i = 0; i < capacity; i++) {
				new_data[i] = data[i];
			}
			delete[] data;
			data = new_data;
		}
		data[capacity] = elem;
		capacity++;
	};

	template<class T>
	unsigned int vector<T>::size() {
		return capacity;
	}

	template<class T>
	vector<T>::vector() {
		capacity = 0;
		maxsize = 0;
		data = 0;
	}

	template<class T>
	vector<T>::vector(const unsigned int n) {
		capacity = n;
		maxsize = n;
		data = new T[capacity];
		assert(n, T());
	}

	template<class T>
	vector<T>::vector(const unsigned int n, T elem) {
		capacity = n;
		maxsize = n;
		data = new T[capacity];
		assert(n, elem);
	}

	template<class T>
	vector<T>::~vector() {
		delete[] data;
	}
}

#endif // VECTOR_HPP