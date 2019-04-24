# Makefile for EECS560 Lab 10
# Damian Vu

FLAGS = $(FLAGS) -g -Wall -pedantic

Lab04: main.o qphashtable.o dhhashtable.o openhashtable.o linkedlist.o
	g++ $(FLAGS) -g main.o qphashtable.o dhhashtable.o openhashtable.o linkedlist.o -o Lab04

main.o: main.cpp qphashtable.o dhhashtable.o openhashtable.o linkedlist.o
	g++ $(FLAGS) -g -c main.cpp

qphashtable.o: qphashtable.h qphashtable.cpp hashtable.hpp
	g++ $(FLAGS) -g -c qphashtable.cpp

dhhashtable.o: dhhashtable.h dhhashtable.cpp hashtable.hpp
	g++ $(FLAGS) -g -c dhhashtable.cpp

openhashtable.o: openhashtable.h openhashtable.cpp linkedlist.o
	g++ $(FLAGS) -g -c openhashtable.cpp

linkedlist.o: linkedlist.h linkedlist.cpp node.hpp
	g++ $(FLAGS) -g -c linkedlist.cpp

clean:
	rm *.o Lab04
