FLAGS_G++ = -g -O2 -pedantic -std=c++17 -Wall -Wextra -Werror

all: main.cpp
	g++ $(FLAGS_G++) main.cpp -o solution

dfs: dfs.cpp
	g++ $(FLAGS_G++) dfs.cpp -o dfs

bfs: bfs.cpp
	g++ $(FLAGS_G++) bfs.cpp -o bfs

# Clean tests and create new template file
new: clean
	bash generate_tests.sh
	cat template.cpp > main.cpp

# Check solution
check: all
	bash checker.sh

# Check solution with valgrind
vcheck: all
	bash vchecker.sh

# Run solution
run: all
	./solution

# Run solution with valgrind
vrun: all
	valgrind ./solution

# Generate tests
test: test_gen.py
	bash generate_tests.sh
	python3 test_gen.py

# Generate tests and run check
testcheck: test check

# Generate tests and run check with valgrind
vtestcheck: test vcheck

clean:
	rm -rf *.o solution
