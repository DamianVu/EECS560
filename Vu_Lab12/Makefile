FLAGS = -std=c++11 -g -Wall -pedantic

Lab12: main.o graph.o edgehandler.o minfiveheap.o edge.o
	g++ $(FLAGS) main.o graph.o edgehandler.o minfiveheap.o edge.o -o Lab12

main.o: main.cpp graph.o
	g++ $(FLAGS) -c main.cpp

graph.o: graph.h graph.cpp edge.o queue.hpp node.hpp findnode.hpp vertexset.hpp
	g++ $(FLAGS) -c graph.cpp

edgehandler.o: edgehandler.h edgehandler.cpp
	g++ $(FLAGS) -c edgehandler.cpp

minfiveheap.o: minfiveheap.h minfiveheap.cpp fiveheap.hpp
	g++ $(FLAGS) -c minfiveheap.cpp

edge.o: edge.h edge.cpp
	g++ $(FLAGS) -c edge.cpp

clean:
	rm *.o Lab12
