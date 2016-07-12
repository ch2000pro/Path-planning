#Makefile for path planinning

CC=g++
CFLAGS=-g -Wall

all: pathPlanning

pathPlanning: obstacle.o graph.o plane.o test.o
	$(CC) obstacle.o graph.o plane.o test.o -o test
	
obstacle.o: obstacle.cpp
	$(CC) $(CFLAGS) obstacle.cpp

graph.o: graph.cpp
	$(CC) $(CFLAGS) graph.cpp

plane.o: plane.cpp
	$(CC) $(CFLAGS) plane.cpp

test.o: test.cpp
	$(CC) $(CFLAGS) test.cpp

clean: 
	rm *o test
