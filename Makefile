#Makefile for path planinning

CC=g++
CFLAGS=-g -Wall -c -I /home/student/boost-library/boost_1_61_0

all: pathPlanning

pathPlanning: obstacle.o plane.o graph.o test.o
	$(CC) obstacle.o plane.o graph.o test.o -o test

obstacle.o: obstacle.cpp
	$(CC) $(CFLAGS) obstacle.cpp

plane.o: plane.cpp
	$(CC) $(CFLAGS) plane.cpp

graph.o: graph.cpp
	$(CC) $(CFLAGS) graph.cpp

test.o: test.cpp
	$(CC) $(CFLAGS) test.cpp

clean: 
	rm *o test
