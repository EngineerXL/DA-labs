#ifndef PAIR_HPP
#define PAIR_HPP

namespace mystd {
	template<class T1, class T2>
	class pair {
		private:
			T1 first_value;
			T2 second_value;
		public:
			pair();
			pair(const T1 elem1, const T2 elem2);
			~pair() {}
			T1& first();
			T2& second();
	};
}

template<class T1, class T2>
mystd::pair<T1, T2>::pair() {
	first_value = T1();
	second_value = T2();
}

template<class T1, class T2>
mystd::pair<T1, T2>::pair(const T1 elem1, const T2 elem2) {
	first_value = elem1;
	second_value = elem2;
}

template<class T1, class T2>
T1& mystd::pair<T1, T2>::first() {
	return first_value;
}

template<class T1, class T2>
T2& mystd::pair<T1, T2>::second() {
	return second_value;
}

#endif // PAIR_HPP