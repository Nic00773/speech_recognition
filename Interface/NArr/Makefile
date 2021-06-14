SRCS    = src/narr.c
HEADERS = src/narr.h
TESTS   = tests/main.c
CCFLAGS = clang -std=c99 -Werror -O3 -pedantic
DEBUG   = -g

test: CCFlAGS += DEBUG
test: ./tests/main
	./tests/main

./tests/main: ./tests/narr.o ./tests/main.c
	$(CCFLAGS) $^ -o $@

./tests/narr.o: src/narr.c src/narr.h
	$(CCFLAGS) -c $< -o $@
