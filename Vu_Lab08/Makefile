# Makefile for EECS560 Lab 08
# Damian Vu

FLAGS = -std=c++11 -g -Wall -pedantic

Lab08: main.o minfiveheap.o maxfiveheap.o
	g++ $(FLAGS) main.o minfiveheap.o maxfiveheap.o -o Lab08

main.o: main.cpp minfiveheap.o maxfiveheap.o
	g++ $(FLAGS) -c main.cpp

minfiveheap.o: minfiveheap.h minfiveheap.cpp fiveheap.hpp
	g++ $(FLAGS) -c minfiveheap.cpp

maxfiveheap.o: maxfiveheap.h maxfiveheap.cpp fiveheap.hpp
	g++ $(FLAGS) -c maxfiveheap.cpp


clean:
	rm Lab08 *.o
