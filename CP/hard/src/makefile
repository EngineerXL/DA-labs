FLAGS_G++ = -g -O2 -pedantic -std=c++17 -Wall -Wextra -lm

build: main.cpp
	g++ $(FLAGS_G++) main.cpp -o solution

# Clean tests and create new template file
new: clean
	bash generate_tests.sh
	cat template.cpp > main.cpp

# Check solution
check: build
	bash checker.sh

# Check solution with valgrind
vcheck: build
	bash vchecker.sh

# Prerocess graph
preprocess: build
	./solution preprocess --edges europe/europe.edges --nodes europe/europe.nodes --output europe/graph.b

# Execute search in preprocessed graph
search: build
	./solution search --graph europe/graph.b --input europe/europe.in --output europe/europe.out

# Execute search with full output in preprocessed graph
searchfull: build
	./solution search --graph europe/graph.b --input europe/europe.in --output europe/europe.out --full-output

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
