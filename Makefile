CC=g++
CXXFLAGS=-std=c++11 -gdwarf-3 -Wall
LDFLAGS=-g

all: FindAllQueries

FindAllQueries: FindAllQueries.o

FindAllQueries.o: ACNode.o ACAutomaton.o

ACNode.o: ACNode.hpp

ACAutomaton.o: ACAutomaton.hpp

clean:
	rm -f FindAllQueries *.o core* *~

