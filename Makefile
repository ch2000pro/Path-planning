#Makefile for path planinning

CC=g++
CFLAGS=-g -Wall

all: pathPlanning

pathPlanning: test.o plane.o obstacle.o graph.o  
	$(CC) test.o plane.o obstacle.o graph.o -o test

test.o: test.cpp
	$(CC) $(CFLAGS) test.cpp

plane.o: plane.cpp
	$(CC) $(CFLAGS) plane.cpp

obstacle.o: obstacle.cpp
	$(CC) $(CFLAGS) obstacle.cpp

graph.o: graph.cpp
	$(CC) $(CFLAGS) graph.cpp

clean: 
	rm *o test
