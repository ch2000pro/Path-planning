/*-----------------------------------------------*/
/*  obstacle.cpp                                 */
/*  Obstacle class. Receive a list of vertices   */
/*  Leonardo Castilho                            */
/*  Start: June 15th                             */
/*-----------------------------------------------*/

#include "obstacle.h" 


  Obstacle::Obstacle(vector<Point*>vertices, unsigned int height){
    vertices_[0] = vertices;
    height_ = height;
    planes_.push_back(0);
    planes_.push_back(height_);
  }
  
  Obstacle::~Obstacle(){

  }
    unsigned int Obstacle::get_height(){
        return height_;
    }

    map<int,vector<Point*> > Obstacle::get_vert_map(){
        return vertices_;
    }

  void Obstacle::add_vertices(vector<Point*> vertices, unsigned int height){
    vertices_[height_] = vertices;
    height_ += height;
    planes_.push_back(height_);
  }

<<<<<<< HEAD
  unsigned int Obstacle::get_num_vert(unsigned int height_search){
    //int height_found;
    if(height_search < height_){
      //search the plane
      
=======
    int Obstacle::get_num_vert(int height_search){
        return get_vertices(height_search).size();
>>>>>>> dd9c3cff9770c72883b8be12ee5577325cc3f879
    }

    //get vertices at a given height or get at a height below
    vector<Point*> Obstacle::get_vertices(unsigned int height_search){
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

<<<<<<< HEAD
  Point* Obstacle::next_vertice(unsigned int height, int x, int y){
    return 0; //REMOVE
  }

  Point* Obstacle::previous_vertice(unsigned int height, int x, int y){
    return 0; //REMOVE
=======
  Point* Obstacle::next_vertice(int height, int x, int y){
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

  Point* Obstacle::previous_vertice(int height, int x, int y){
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
>>>>>>> dd9c3cff9770c72883b8be12ee5577325cc3f879
  }
  
  //Return the number of planes of the obstacle. Minimum is 2
  unsigned int Obstacle::get_numPlanes(){
    return planes_.size();
  }
  
<<<<<<< HEAD
  unsigned int Obstacle::find_plane(unsigned int toFind){
    for(unsigned int i = 0; i < planes_.size()-1; i++){
      if(toFind >= planes_[i] && toFind < planes_[i+1]){
        return planes_[i];
      }
    }
    return planes_[planes_.size()-1];
  }
  
  
=======
>>>>>>> dd9c3cff9770c72883b8be12ee5577325cc3f879
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
