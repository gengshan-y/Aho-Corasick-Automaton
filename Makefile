CC=g++
CXXFLAGS=-std=c++11 -gdwarf-3 -Wall
LDFLAGS=-g

all: FindAllQueries

FindAllQueries: FindAllQueries.o

FindAllQueries.o: ACNode.o ACAutomaton.o Timer.o

ACNode.o: ACNode.hpp

ACAutomaton.o: ACAutomaton.hpp

Timer.o: Timer.hpp

clean:
	rm -f FindAllQueries *.o core* *~

