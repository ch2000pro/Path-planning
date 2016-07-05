/*-----------------------------------------------*/
/*  obstacle.cpp                                 */
/*  Obstacle class. Receive a list of vertices   */
/*  Leonardo Castilho                            */
/*  Start: June 15th                             */
/*-----------------------------------------------*/

#include "point.h"
#include "obstacle.h" 


  Obstacle::Obstacle(vector<Point*>vertices, int height){
    vertices_[0] = vertices;
    height_ = height;
    planes_.push_back(0);
    planes_.push_back(height_);
  }
  
  Obstacle::~Obstacle(){

  }

  void Obstacle::add_vertices(vector<Point*> vertices, int height){
    vertices_[height_] = vertices;
    height_ += height;
    planes_.push_back(height_);
  }

  int Obstacle::get_num_vert(int height){
    if(height < height_){
      //search the plane
    }
    return 0;
  }

  Point* Obstacle::next_vertice(int height, int x, int y){
    return 0; //REMOVE
  }

  Point* Obstacle::previous_vertice(int height, int x, int y){
    return 0; //REMOVE
  }
  
  //Return the number of planes of the obstacle. Minimum is 2
  int Obstacle::get_numPlanes(){
    return planes_.size();
  }
