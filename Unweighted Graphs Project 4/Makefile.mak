CPPFLAGS=-std=c++11 -g -O3

prog: main.o 
	g++ main.o -o prog

main.o: main.cpp graph.h 
	g++ $(CPPFLAGS) -c main.cpp

clean:
	rm *.o -f
