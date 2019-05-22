FLAGS = -std=c++11 -g -Wall -pedantic

Lab11: main.o minfiveheap.o maxfiveheap.o bst.o
	g++ $(FLAGS) main.o bst.o minfiveheap.o maxfiveheap.o -o Lab11

main.o: main.cpp minfiveheap.o maxfiveheap.o bst.o
	g++ $(FLAGS) -c main.cpp

bst.o: bst.h bst.cpp node.hpp
	g++ $(FLAGS) -c bst.cpp

minfiveheap.o: minfiveheap.h minfiveheap.cpp fiveheap.hpp
	g++ $(FLAGS) -c minfiveheap.cpp

maxfiveheap.o: maxfiveheap.h maxfiveheap.cpp fiveheap.hpp
	g++ $(FLAGS) -c maxfiveheap.cpp

clean:
	rm Lab11 *.o
