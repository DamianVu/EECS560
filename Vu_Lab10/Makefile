# Makefile for EECS560 Lab 10
# Damian Vu

FLAGS = -std=c++11 -g -Wall -pedantic

Lab10: main.o leftist.o skew.o
	g++ $(FLAGS) main.o leftist.o skew.o -o Lab10

main.o: main.cpp
	g++ $(FLAGS) -c main.cpp

leftist.o: leftist.h leftist.cpp node.hpp mergeheap.hpp
	g++ $(FLAGS) -c leftist.cpp

skew.o: skew.h skew.cpp node.hpp mergeheap.hpp
	g++ $(FLAGS) -c skew.cpp

clean:
	rm *.o Lab10
