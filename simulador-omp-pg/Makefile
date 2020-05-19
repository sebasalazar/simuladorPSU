CXX = g++
CXXFLAGS = -std=c++11 -g3 -Wall -lm -fopenmp 
MKDIR = mkdir -p

LIBS = -lm -fopenmp -lpq 

directorios:
	$(MKDIR) build dist

db.o: directorios db.c
	$(CXX) $(CXXFLAGS) -c db.c -o build/db.o

main.o: directorios main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o build/main.o

all: clean main.o db.o
	$(CXX) $(CXXFLAGS) -o dist/simulador-omp build/main.o build/db.o $(LIBS) 
	rm -fr build

clean:
	rm -fr *.o a.out core simulador-omp dist build

.DEFAULT_GOAL := all