CXX = g++
CXXFLAGS = -std=c++11 -g3 -Wall -lm -fopenmp
MKDIR = mkdir -p

LIBS = -lm -fopenmp

directorios:
	$(MKDIR) build dist

main.o: directorios main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o build/main.o

all: clean main.o
	$(CXX) $(CXXFLAGS) $(LIBS) -o dist/simulador-omp build/main.o
	rm -fr build

clean:
	rm -fr *.o a.out core simulador-omp dist build

.DEFAULT_GOAL := all