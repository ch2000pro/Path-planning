#include <vector>
#include <iostream>

class Point;

using namespace std;

class Obstacle{

  public:
    Obstacle(){};
    Obstacle(vector<Point*> vertices){
      vertices_ = vertices;
    };
    ~Obstacle();
    int get_num_vert();
    Point* next_vertice(int x, int y);
    Point* previous_vertice(int x, int y);
    
    
  private:
    vector<Point*> vertices_;
};
