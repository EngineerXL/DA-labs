FLAGS = -O2 -g -pedantic -std=c++17 -Wall -Werror

all: search main
	g++ $(FLAGS) search.o main.o -o solution

search: search.hpp search.cpp
	g++ $(FLAGS) -c search.cpp

main: main.cpp
	g++ $(FLAGS) -c main.cpp

clean:
	rm -rf *.o solution