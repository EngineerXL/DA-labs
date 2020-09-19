FLAGS = -std=c++14

all: main.o
	g++ $(FLAGS) main.o -o solution

main: main.cpp vector.hpp
	g++ $(FLAGS) -c main.cpp

clean:
	rm -rf *.o