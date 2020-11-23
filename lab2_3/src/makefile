FLAGS = -std=c++17 -pedantic -Wall -Werror -Wextra
FLAGS_GPROF = -std=c++17 -pg
FLAGS_O3 = -std=c++17 -O3

all: main.o
	g++ $(FLAGS_O3) main.o -o solution

main.o: main.cpp btree.hpp item.hpp vector.hpp main.cpp
	g++ $(FLAGS_O3) -c main.cpp

clean:
	rm -rf solution *.o
