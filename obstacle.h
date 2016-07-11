#include <vector>
#include <iostream>
#include <map>
#include "point.h"

class Point;

using namespace std;

//class representing a 3D obstacle
class Obstacle{

  public:
    Obstacle(vector<Point*> vertices, unsigned int height); //constructor initializes the obstacle
    ~Obstacle(); //destructor
    
    unsigned int add_vertices(vector<Point*> vertices, unsigned int height); //add vertices of a new plane to the obstacle
    unsigned int get_num_vert(unsigned int height); //returns the number of vertices at a given height (z-coordinate)
    Point* next_vertice(unsigned int height, int x, int y); //next vertice in the same height
    Point* previous_vertice(unsigned int height, int x, int y); //previous vertice in the same height
    unsigned int get_numPlanes(); //returns the number of planes where that obstacle changes
    vector<Point*> get_vertices(unsigned int height_search); //returns the vertices at a given height
    unsigned int get_height(); //getter for the obstacle total height
    map<int,vector<Point*> > get_vert_map(); //getter for the obstacle private map vertices_
    unsigned int find_plane(unsigned int z); //given a z, find the plane z below
    void print_num_vertices(void); //debugging method
    
  private:
    unsigned int height_; //total height of the obstacle
    map<int,vector<Point*> > vertices_; //map of Z coordinates in which the obstacle changes and respective Vertices
    vector<unsigned int> planes_; //list of all Z coordinates
};
