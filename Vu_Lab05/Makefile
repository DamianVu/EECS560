# Makefile for EECS560 Lab 05
# Damian Vu

FLAGS = -std=c++11 -g -Wall

Lab05: main.o bst.o
	g++ $(FLAGS) main.o bst.o -o Lab05

main.o: main.cpp bst.o
	g++ $(FLAGS) -c main.cpp

bst.o: bst.h bst.cpp node.hpp
	g++ $(FLAGS) -c bst.cpp

clean:
	rm Lab05 *.o
