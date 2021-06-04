CPPFLAGS = -std=c++17 -Wall -Wextra -Werror -g

all: Allocator.o mainTest.o
		g++ Allocator.o mainTest.o -o main

test: Allocator.o mainTest.o
		g++ mainTest.o Allocator.o -o test
		./test

.PHONY: clean
clean:
		rm -f *.o

.PHONY: fclean
fclean:
		rm -f *.o
		rm main
		rm test

