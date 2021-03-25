all: program

program: mainTest.o Allocator.o
	g++ mainTest.o Allocator.o -o program

mainTest.o: mainTest.cpp
	g++ -c mainTest.cpp

Allocator.o: Allocator.cpp
	g++ -c Allocator.cpp

clean:
	rm -rf *.o program

test: program
	./program
