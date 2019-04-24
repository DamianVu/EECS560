# Makefile for EECS560 Lab 02
# Damian Vu

FLAGS = -std=c++11 -g -Wall -pedantic

Lab02: main.o linkedlist.o hashtable.o
	g++ $(FLAGS) main.o linkedlist.o hashtable.o -o Lab02

main.o: main.cpp
	g++ $(FLAGS) -c main.cpp

hashtable.o: hashtable.cpp hashtable.h linkedlist.o
	g++ $(FLAGS) -c hashtable.cpp

linkedlist.o: node.hpp linkedlist.h linkedlist.cpp
	g++ $(FLAGS) -c linkedlist.cpp

clean:
	rm *.o Lab02
