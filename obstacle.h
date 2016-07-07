#include <vector>
#include <iostream>
#include <map>
#include "point.h"

class Point;

using namespace std;

class Obstacle{

  public:
    Obstacle(){};
    Obstacle(vector<Point*> vertices, int height);
    ~Obstacle();
    void add_vertices(vector<Point*> vertices, int height);
    int get_num_vert(int height);
    Point* next_vertice(int height, int x, int y);
    Point* previous_vertice(int height, int x, int y);
    int get_numPlanes();
    vector<Point*> get_vertices(int height_search);
    int get_height();
    map<int,vector<Point*> > get_vert_map();
    
    //debugging
    void print_num_vertices(void);
    
  private:
    int height_;
    map<int,vector<Point*> > vertices_;
    vector<int> planes_;
};
