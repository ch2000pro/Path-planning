/*-----------------------------------------------*/
/*  obstacle.cpp                                 */
/*  Obstacle class. Receive a list of vertices   */
/*  Leonardo Castilho                            */
/*  Start: June 15th                             */
/*-----------------------------------------------*/

#include "obstacle.h"

//constructor, it initializes the obstacle in the plane 0 (terrain ground)
Obstacle::Obstacle(vector<Point*>vertices, unsigned int height){
    vertices_[0] = vertices;
    height_ = height;
    planes_.push_back(0);
    planes_.push_back(height_);
}

//destructor
Obstacle::~Obstacle(){
}

//getter for the obstacle total height
unsigned int Obstacle::get_height(){
    return height_;
}

//getter for the obstacle private map vertices_
map<int,vector<Point*> > Obstacle::get_vert_map(){
    return vertices_;
}

//add vertices of a new plane to the obstacle
unsigned int Obstacle::add_vertices(vector<Point*> vertices, unsigned int height){
    vertices_[height_] = vertices;
    height_ += height;
    planes_.push_back(height_);
    return height_;
}

//returns the number of vertices at a given height
unsigned int Obstacle::get_num_vert(unsigned int height_search){
    return get_vertices(height_search).size();
}

//returns the vertices at a given height or at a height below if the obstacle does not change in that z-coordinate
vector<Point*> Obstacle::get_vertices(unsigned int height_search){
    if(height_search <= height_){
        for(unsigned int i = 0; i< planes_.size() -1; i++){
            if(planes_[i] == height_search){
                vector<Point*> points;
                points.resize(vertices_[height_search].size());
                for(unsigned i = 0; i < vertices_[height_search].size(); ++i)
                    points[i] = vertices_[height_search][i]->clone();
                return points;
            }
            if(planes_[i] < height_search && planes_[i+1] > height_search){
                vector<Point*> points;
                points.resize(vertices_[planes_[i]].size());
                for(unsigned j = 0; j < vertices_[planes_[i]].size(); ++j)
                    points[j] = vertices_[planes_[i]][j]->clone();
                return points;
            }
        }
    }
    return {};
}

//returns the next vertice in the same height (assuming that the points were inserted in clockwise order)
Point* Obstacle::next_vertice(unsigned int height, int x, int y){
    vector<Point*> points_at_height = get_vertices(height);
    for(unsigned int i = 0; i < points_at_height.size(); i++){
        Point* p = points_at_height[i];
        if(p->getX() == x && p->getY() == y){
            if(i == points_at_height.size()-1){
                return points_at_height[0];
            }
            else{
                return points_at_height[i+1];
            }
        }
    }
    return NULL;
}

//returns the previous vertice in the same height (assuming that the points were inserted in clockwise order)
Point* Obstacle::previous_vertice(unsigned int height, int x, int y){
    vector<Point*> points_at_height = get_vertices(height);
    for(unsigned int i = 0; i < points_at_height.size(); i++){
        Point* p = points_at_height[i];
        if(p->getX() == x && p->getY() == y){
            if(i == 0){
                return points_at_height[points_at_height.size()-1];
            }
            else{
                return points_at_height[i-1];
            }
        }
    }
    return NULL;
}

//Return the number of planes of the obstacle. Minimum is 2
unsigned int Obstacle::get_numPlanes(){
    return planes_.size();
}

//Given a z, return that z coordinate if there is a change in the obstacle or returns the z-coordinate of the plane right below
unsigned int Obstacle::find_plane(unsigned int toFind){
    for(unsigned int i = 0; i < planes_.size()-1; i++){
        if(toFind >= planes_[i] && toFind < planes_[i+1]){
            return planes_[i];
        }
    }
    return planes_[planes_.size()-1];
}

//debugging
void Obstacle::print_num_vertices(){
    vector<unsigned int>::iterator it;
    cout << endl << "---DEBUG FUNCTION---";
    for(it = planes_.begin(); it != planes_.end(); ++it){
        cout << endl <<"Plane " << *it << " has " << (vertices_[*it]).size() << " vertices.";
    }
    cout << endl;
    cout << "--------END---------" << endl;
}
