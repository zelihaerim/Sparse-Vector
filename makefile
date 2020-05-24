all: begin

begin: main.o SparseMatrix.o SparseVector.o
	  g++  main.o SparseMatrix.o SparseVector.o -o exe

main.o: main.cpp
	g++ -std=c++11 -c main.cpp

SparseMatrix.o: SparseMatrix.cpp
	g++ -std=c++11 -c SparseMatrix.cpp

SparseVector.o: SparseVector.cpp
	g++ -std=c++11 -c SparseVector.cpp
clean:
	rm *.o exe
