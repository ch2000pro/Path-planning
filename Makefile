#Makefile for path planinning

path: src/obstacle.cpp src/plane.cpp src/shortestPath.cpp
	g++ -std=c++11 -framework OpenGL -framework GLUT -o exec src/obstacle.cpp src/plane.cpp src/shortestPath.cpp -I /usr/local/include
