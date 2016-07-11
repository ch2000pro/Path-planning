#include <vector>
#include <iostream>
#include <map>

class Point;
class Plane;
class Obstacle;

using namespace std;

class Graph{
    
    public:
    Graph(vector<Obstacle*> obstacles_);
    ~Graph();
    
    
    private:
    vector<Obstacle*> obstacles;
    
};