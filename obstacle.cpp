/*-----------------------------------------------*/
/*  obstacle.cpp                                 */
/*  Obstacle class. Receive a list of vertices   */
/*  Leonardo Castilho                            */
/*  Start: June 15th                             */
/*-----------------------------------------------*/

#include "point.h"
#include "obstacle.h"

  Obstacle::~Obstacle(){
    Point* deleting;
    while(vertices_.size() != 0){
      deleting = vertices_[vertices_.size()-1];
      delete deleting;
      vertices_.pop_back();
    }
  }

  int Obstacle::get_num_vert(){
    return vertices_.size();
  }

  Point* Obstacle::next_vertice(int x, int y){
    
  }

  Point* Obstacle::previous_vertice(int x, int y){
    
  }
