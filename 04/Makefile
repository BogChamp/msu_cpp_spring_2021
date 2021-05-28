CC = g++
FLAGS = -std=c++17 -Wall -Wextra -Werror -g

re: all

all: test.o bigint.o
		@$(CC) test.o bigint.o -o main

test: test.o bigint.o
		@$(CC) test.o bigint.o -o main
		./main

test.o: test.cpp
		@$(CC) -c $(FLAGS) test.cpp

bigint.o: bigint.cpp
		@$(CC) -c $(FLAGS) bigint.cpp 

clean:
		rm -rf *.o

fclean:
		rm -f *.o
		rm main

.PHONY:
		clean all fclean