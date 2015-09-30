CPPFLAGS=-std=c++11 -g -O3

hotpotato: main.o random.o
	g++ main.o random.o -o hotpotato

main.o: main.cpp RevList.h random.h
	g++ $(CPPFLAGS) -c main.cpp

random.o: random.cpp random.h
	g++ $(CPPFLAGS) -c random.cpp

clean: 
	rm *.o -f