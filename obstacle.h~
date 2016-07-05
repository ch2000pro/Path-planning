#include <vector>
#include <iostream>
#include <map>

class Point;

using namespace std;

class Obstacle{

  public:
    Obstacle(){};
    Obstacle(vector<Point*> vertices, int height);
    ~Obstacle();
    int get_num_vert();
    Point* next_vertice(int x, int y);
    Point* previous_vertice(int x, int y);
    
    
  private:
    int height_;
    map<int,vector<Point*> > vertices_;
};
