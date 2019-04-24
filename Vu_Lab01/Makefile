# Makefile for EECS560 Lab 01
# Damian Vu

FLAGS = -std=c++11 -g -Wall -pedantic

Lab01: main.o linkedlist.o
	g++ $(FLAGS) main.o linkedlist.o -o Lab01

main.o: main.cpp linkedlist.o
	g++ $(FLAGS) -c main.cpp

linkedlist.o: node.hpp linkedlist.h linkedlist.cpp
	g++ $(FLAGS) -c linkedlist.cpp

clean:
	rm *.o Lab01
