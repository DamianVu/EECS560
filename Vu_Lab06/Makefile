# Makefile for EECS560 Lab 06
# Damian Vu

FLAGS = -std=c++11 -g -Wall -Werror -pedantic

Lab06: main.o bst.o
	g++ $(FLAGS) main.o bst.o -o Lab06

main.o: main.cpp bst.o
	g++ $(FLAGS) -c main.cpp

bst.o: bst.h bst.cpp node.hpp
	g++ $(FLAGS) -c bst.cpp

clean:
	rm Lab06 *.o
