CC = g++
FLAGS = -std=c++17 -Wall -Wextra -Werror -g

re: all

all: test.o Matrix.o
		@$(CC) test.o Matrix.o -o main

test: test.o Matrix.o
		@$(CC) test.o Matrix.o -o main
		./main

test.o: test.cpp
		@$(CC) -c $(FLAGS) test.cpp

Matrix.o: Matrix.cpp
		@$(CC) -c $(FLAGS) Matrix.cpp 

clean:
		rm -rf *.o

fclean:
		rm -f *.o
		rm main

.PHONY:
		clean all fclean