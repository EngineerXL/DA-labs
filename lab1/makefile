FLAGS = -std=c++11

all: main.o
	g++ $(FLAGS) main.o -o solution

main: main.cpp sort.hpp pair.hpp vector.hpp
	g++ $(FLAGS) -c main.cpp

clean:
	rm -rf *.o