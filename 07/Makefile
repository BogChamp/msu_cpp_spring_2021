CC = g++
FLAGS = -std=c++17 -Wall -Wextra -Werror -g

re: all

all: test.o
		@$(CC) test.o -o main

test: test.o
		@$(CC) test.o -o main
		./main

test.o: test.cpp
		@$(CC) -c $(FLAGS) test.cpp

clean:
		rm -rf *.o

fclean:
		rm -f *.o
		rm main

.PHONY:
		clean all fclean