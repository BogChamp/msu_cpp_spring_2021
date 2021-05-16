CC = g++
FLAGS = -std=c++17 -Wall -Wextra -Werror -g

re: all

all: parser.o
		ar r libparser.a parser.o

parser.o: parser.cpp
		@$(CC) -c $(FLAGS) parser.cpp

test: Test.o parser.o
		ar r libparser.a parser.o
		@$(CC) -o main Test.o -L./ -lparser
		./main

Test.o: Test.cpp
		@$(CC) -c $(FLAGS) Test.cpp

clean:
		rm -rf *.o

fclean:
		rm -f *.o
		rm main
		rm libparser.a

.PHONY:
		clean all fclean