FLAGS = -std=c++17 -pedantic -O3

all: main.o
	g++ $(FLAGS) main.o -o solution

main.o: main.cpp btree.hpp item.hpp vector.hpp main.cpp
	g++ $(FLAGS) -c main.cpp

clean:
	rm -rf solution *.o
