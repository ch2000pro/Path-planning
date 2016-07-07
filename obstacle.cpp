/*-----------------------------------------------*/
/*  obstacle.cpp                                 */
/*  Obstacle class. Receive a list of vertices   */
/*  Leonardo Castilho                            */
/*  Start: June 15th                             */
/*-----------------------------------------------*/

#include "obstacle.h" 


  Obstacle::Obstacle(vector<Point*>vertices, int height){
    vertices_[0] = vertices;
    height_ = height;
    planes_.push_back(0);
    planes_.push_back(height_);
  }
  
  Obstacle::~Obstacle(){

  }
    int Obstacle::get_height(){
        return height_;
    }

    map<int,vector<Point*> > Obstacle::get_vert_map(){
        return vertices_;
    }

  void Obstacle::add_vertices(vector<Point*> vertices, int height){
    vertices_[height_] = vertices;
    height_ += height;
    planes_.push_back(height_);
  }

  int Obstacle::get_num_vert(int height_search){
    //int height_found;
    if(height_search < height_){
      //search the plane
      
    }
    return 0;
  }

    //get vertices at a given height or get at a height below
    vector<Point*> Obstacle::get_vertices(int height_search){
    if(height_search <= height_){
        for(unsigned int i = 0; i< planes_.size() -1; i++){
            if(planes_[i] == height_search){
                return vertices_[height_search];
            }
            if(planes_[i] < height_search && planes_[i+1] > height_search){
                return vertices_[planes_[i]];
            }
        }
    }
    return {};
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
  
  
  
  
  //debugging
  void Obstacle::print_num_vertices(){
    vector<int>::iterator it;
    for(it = planes_.begin(); it != planes_.end(); ++it){
      cout << endl << "Plane " << *it << " has " << (vertices_[*it]).size() << " vertices." << endl;
    }
  }
