# Makefile for EECS560 Lab 07
# Damian Vu

FLAGS = -std=c++11 -g -Wall -Werror -pedantic

Lab07: main.o
	g++ $(FLAGS) main.o twothree.o -o Lab07

main.o: main.cpp twothree.o
	g++ $(FLAGS) -c main.cpp

twothree.o: twothree.h twothree.cpp twothreenode.hpp
	g++ $(FLAGS) -c twothree.cpp

clean:
	rm Lab07 *.o
