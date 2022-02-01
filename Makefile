CXX=g++
CXXFLAGS=-Wall -Wextra -g
LDFLAGS=
EXEC=main
SRC=$(wildcard *.cpp)
OBJ=$(SRC:.cpp=.o)
 
all: $(EXEC)
 
main: $(OBJ)
	$(CXX) -o $@  $^ $(LDFLAGS)

Dijsktra : Dijsktra.o Arc.o Point.o
	$(CXX) -o Dijsktra $^
 
.PHONY: clean mrproper

reload:
	make clean
	make
 
clean:
	rm -rf *.o
	rm -rf main
	rm -rf Dijsktra

 
mrproper: clean
	rm -rf $(EXEC)