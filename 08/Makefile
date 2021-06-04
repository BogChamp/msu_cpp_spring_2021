CPPFLAGS = -std=c++17 -Wall -Wextra -Werror -g
LDLIBS = -lpthread

all: test.o
		g++ test.o -o main -lpthread

.PHONY: test
test: test.o
		g++ test.o -o main -lpthread
		./main

.PHONY: clean
clean:
		rm -rf *.o

.PHONY: fclean
fclean:
		rm -f *.o
		rm main
