# Makefile for EECS560 Lab 03
# Damian Vu

FLAGS = -std=c++11 -g -Wall -pedantic

Lab03: main.o qphashtable.o dhhashtable.o
	g++ $(FLAGS) main.o qphashtable.o dhhashtable.o -o Lab03

main.o: main.cpp qphashtable.o dhhashtable.o
	g++ $(FLAGS) -c main.cpp

qphashtable.o: qphashtable.h qphashtable.cpp hashtable.hpp
	g++ $(FLAGS) -c qphashtable.cpp

dhhashtable.o: dhhashtable.h dhhashtable.cpp hashtable.hpp
	g++ $(FLAGS) -c dhhashtable.cpp

clean:
	rm *.o Lab03
