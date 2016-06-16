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
  private:
    vector<Point*> vertices_;
};
