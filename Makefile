CC=g++
CXXFLAGS=-std=c++11 -gdwarf-3 -Wall
LDFLAGS=-g

all: main

main: main.o

main.o: ACNode.o ACAutomaton.o

ACNode.o: ACNode.hpp

ACAutomaton.o: ACAutomaton.hpp

clean:
	rm -f main *.o core* *~

