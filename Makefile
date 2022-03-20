CXX=g++
CXXFLAGS=-Wall -Wextra -g -std=c++11
LDFLAGS=
EXEC=main
SRC=$(wildcard *.cpp)
OBJ=$(SRC:.cpp=.o)
 
main: $(OBJ)
	$(CXX) -o $@  $^ $(LDFLAGS)

Dijsktra : Dijsktra.o Arc.o Point.o
	$(CXX) -o Dijsktra $^


all : 
	make clean
	make 
	./main

 
.PHONY: clean mrproper

reload:
	make clean
	make
 
clean:
	rm -rf *.o
	rm -rf main
	rm -rf Dijsktra
	rm -rf Graphe

 
mrproper: clean
	rm -rf $(EXEC)