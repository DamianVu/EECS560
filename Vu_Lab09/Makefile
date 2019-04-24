# Makefile for EECS560 Lab 09
# Damian Vu

FLAGS = -std=c++11 -g -Wall -pedantic

Lab09: main.o minmax.o process.o
	g++ $(FLAGS) main.o minmax.o process.o -o Lab09

main.o: main.cpp minmax.o
	g++ $(FLAGS) -c main.cpp

minmax.o: minmax.h minmax.cpp process.o
	g++ $(FLAGS) -c minmax.cpp

process.o: process.h process.cpp
	g++ $(FLAGS) -c process.cpp

clean:
	rm Lab09 *.o
