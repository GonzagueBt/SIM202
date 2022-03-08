CXX=g++
CXXFLAGS=-Wall -Wextra -g -std=c++11
LDFLAGS=
EXEC=main
SRC=$(wildcard *.cpp)
OBJ=$(SRC:.cpp=.o)
 
all: $(EXEC)
 
main: $(OBJ)
	$(CXX) -o $@  $^ $(LDFLAGS)

Dijsktra : Dijsktra.o Arc.o Point.o
	$(CXX) -o Dijsktra $^

Graphe : Graphe.o Obstacle.o Arc.o Point.o
	$(CXX) -o Graphe $^

m : 
	make clean
	make 
	./main

d : 
	make clean
	make Dijsktra
	./Dijsktra
 
.PHONY: clean mrproper

reload:
	make clean
	make
 
clean:
	rm -rf *.o
	rm -rf main
	rm -rf Dijsktra
	rm -rf Graphe
	rm -rf Graphe.txt

 
mrproper: clean
	rm -rf $(EXEC)