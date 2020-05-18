CXX = g++
CXXFLAGS = -std=c++11 -g3 -Wall -lm
MKDIR = mkdir -p

LIBS = -lm

directorios:
	$(MKDIR) build dist

main.o: directorios main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o build/main.o

all: clean main.o
	$(CXX) $(CXXFLAGS) $(LIBS) -o dist/promediador-sec build/main.o
	rm -fr build

clean:
	rm -fr *.o a.out core promediador-sec dist build *.csv

.DEFAULT_GOAL := all
