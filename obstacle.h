#include <vector>
#include <iostream>
#include <map>
#include "point.h"

class Point;

using namespace std;

class Obstacle{

  public:
    Obstacle(){};
    Obstacle(vector<Point*> vertices, unsigned int height);
    ~Obstacle();
<<<<<<< HEAD
    void add_vertices(vector<Point*> vertices, unsigned int height);
    unsigned int get_num_vert(unsigned int height);
    Point* next_vertice(unsigned int height, int x, int y);
    Point* previous_vertice(unsigned int height, int x, int y);
    unsigned int get_numPlanes();
    vector<Point*> get_vertices(unsigned int height_search);
    vector<Point*> get_Allvertices();
    unsigned int get_height();
=======
    void add_vertices(vector<Point*> vertices, int height);
    int get_num_vert(int height);
    Point* next_vertice(int height, int x, int y);
    Point* previous_vertice(int height, int x, int y);
    int get_numPlanes();
    vector<Point*> get_vertices(int height_search);
    int get_height();
>>>>>>> dd9c3cff9770c72883b8be12ee5577325cc3f879
    map<int,vector<Point*> > get_vert_map();
    
    unsigned int find_plane(unsigned int);
    
    //debugging
    void print_num_vertices(void);
    
  private:
    unsigned int height_;
    map<int,vector<Point*> > vertices_;
    vector<unsigned int> planes_;
    
    
};
