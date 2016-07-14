/*-----------------------------------------------*/
/*  test.cpp                                     */
/*  Main program to run and test partial parts   */
/*  Leonardo Castilho                            */
/*  Start: June 15th                             */
/*-----------------------------------------------*/

#include "boost/config.hpp"
#include "boost/graph/graph_traits.hpp"
#include "boost/graph/adjacency_list.hpp"
#include "boost/graph/dijkstra_shortest_paths.hpp"
#include "boost/property_map/property_map.hpp"

#include "obstacle.h"
#include "point.h"
#include "plane.h"

using namespace std;

int main (){
    unsigned int option = 0, vertices = 0, planesInserted = 0, flag_planes = 0;
    double height;
    vector<int> total_planes;
    total_planes.push_back(0);
    vector<Obstacle*> obstacles;
    vector<Plane*> planes;
    Point* source;
    Point* target;
    
    do{
      cout << endl;
      cout << "Select an option:" << endl;
      cout << "1 - Create a new obstacle" << endl;
      cout << "2 - Use default map" << endl; //Default map is drawn
      cout << "0 - Proceed" << endl;
      cin >> option;
      
      switch(option){
         case 0:{
           vector<int>::iterator it;
           int z;
           for (it = total_planes.begin() ; it != total_planes.end(); ++it) {
               z = *it;
               Plane* plane = new Plane(z);
               plane -> findObstaclesInPlane(obstacles);
               planes.push_back(plane);
           }
           break;
         }
         
         case 1:{
           do{
               cout << "How many planes does this object have? ";
               cin >> planesInserted;
               if(planesInserted<2) cout << "An object of are non-zero must "
                   << "have at least 2 plane." << endl;
           }while(planesInserted < 2);
           flag_planes = 0;
           while(planesInserted > 1){
               vector<Point*> vertices_input;
               cout << endl << "Input for the new plane..." << endl;
               do{
                   cout << "How many vertices does this plane have? ";
                   cin >> vertices;
                   if(vertices<3) cout << "An object of are non-zero must "
                       << "have at least 3 vertices." << endl;
              }while(vertices < 3);
              cout << "What is the height of these segments? ";
              cin >> height;
              while(vertices > 0){
                  double x, y;
                  cout << "Enter x y: ";
                  cin >> x;
                  cin >> y;
                  vertices_input.push_back(new Point(x,y));
                  vertices --;
               }
               if(flag_planes == 0){
                   obstacles.push_back(new Obstacle(vertices_input,height));
                   if(std::find(total_planes.begin(), total_planes.end(), height) != total_planes.end()) {
                      //vector of all planes already contains this height
                   } else {
                      total_planes.push_back(height);
                   }
                   flag_planes = 1;
               }
               else{
                   unsigned int height_ = obstacles[obstacles.size()-1]->add_vertices(vertices_input, height);
                   if(std::find(total_planes.begin(), total_planes.end(), height) != total_planes.end()) {
                       //vector of all planes already contains this height
                   } else {
                       total_planes.push_back(height_);
                   }
               }
               planesInserted--;
               height = 0;
           }
           
           //cout << "Plane is " << obstacles[0]->find_plane(5) << endl;
           //obstacles[0]->print_num_vertices();
           break;
         }
         
         case 2:{
           vector<Point*> vertices_input;
           //First obstacle
           vertices_input.push_back(new Point(0,0));
           vertices_input.push_back(new Point(0,0));
           vertices_input.push_back(new Point(15,9));
           vertices_input.push_back(new Point(15,0));
           obstacles.push_back(new Obstacle(vertices_input,8));
           vertices_input.clear();
           
           vertices_input.push_back(new Point(3.2,2.2));
           vertices_input.push_back(new Point(3.2,6.7));
           vertices_input.push_back(new Point(11.2,6.7));
           vertices_input.push_back(new Point(11.2,2.2));
           obstacles[obstacles.size()-1]->add_vertices(vertices_input, 11);
           vertices_input.clear();
           
           //Second obstacle
           vertices_input.push_back(new Point(10,20));
           vertices_input.push_back(new Point(10,32));
           vertices_input.push_back(new Point(30,32));
           vertices_input.push_back(new Point(30,20));
           obstacles.push_back(new Obstacle(vertices_input,15));
           vertices_input.clear();
           
           vertices_input.push_back(new Point(10,24));
           vertices_input.push_back(new Point(10,32));
           vertices_input.push_back(new Point(24,32));
           vertices_input.push_back(new Point(24,24));
           obstacles[obstacles.size()-1]->add_vertices(vertices_input, 3);
           vertices_input.clear();
           
           total_planes.push_back(0);
           total_planes.push_back(8);
           total_planes.push_back(15);
           total_planes.push_back(18);
           total_planes.push_back(19);
           
           //---------DEBUG----REMOVE---------
           cout << endl << "Obstacle 1...";
           obstacles[0]->print_num_vertices();
           cout << endl << "Obstacle 2...";
           obstacles[1]->print_num_vertices();
           //---------------------------------
           break;
         }
      }
      
    }while(option != 0 && option != 2);
    
    option = 0;
    do{ //Start menu
        //test
        cout << endl;
        cout << "Select an option:" << endl;
        cout << "1 - Number of obstacles" << endl;
        cout << "2 - Find shortest path" << endl;
        cout << "0 - Quit" << endl;
        cin >> option;
        
        switch(option){
                // =================== CASE 0 ===================
            case 0:{
                break;
            }
                // =================== CASE 1 ===================
            case 1:{
                cout << obstacles.size() << " object(s)." << endl << endl;
                break;
            }
                // =================== CASE 2 ===================
            case 2:{
                unsigned int x, y, z, x_, y_, z_;
                cout << " What is the source point of the search? (x, y and z)" << endl;
                cin >> x;
                cin >> y;
                cin >> z;
                cout << " What is the target point of the search? (x, y and z)" << endl;
                cin >> x_;
                cin >> y_;
                cin >> z_;
                
                source = new Point(x, y, z);
                target = new Point(x_, y_, z_);
                
                //TO DO FIND SHORTEST PATH;
                break;
            }
                // ================== DEFAULT ===================
            default:{
                break;
            }
        }//End switch(option)
        
    }while(option != 0);//End menu
    
    
    
    //------ Free memory ----------
    Obstacle *deleting;
    while(obstacles.size() != 0){ //Delete items
        deleting = obstacles[obstacles.size()-1];
        delete deleting;
        obstacles.pop_back();
    }
    //-----------------------------
    
    
    
    return 0;
}
