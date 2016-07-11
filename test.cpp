/*-----------------------------------------------*/
/*  test.cpp                                     */
/*  Main program to run and test partial parts   */
/*  Leonardo Castilho                            */
/*  Start: June 15th                             */
/*-----------------------------------------------*/


#include "obstacle.h"
#include "point.h"
#include "plane.h"

using namespace std;

int main (){
    unsigned int option = 0, vertices = 0, planesInserted = 0, flag_planes = 0, height;
    vector<int> total_planes;
    total_planes.push_back(0);
    vector<Obstacle*> obstacles;
    vector<Plane*> planes;
    
    do{ //Start menu
        //test
        cout << endl;
        cout << "Select an option:" << endl;
        cout << "1 - Create a new obstacle" << endl;
        cout << "2 - Number of obstacles" << endl;
        cout << "3 - I dont want to create more obstacles" << endl;
        cout << "4 - Find shortest path" << endl;
        cout << "0 - Quit" << endl;
        cin >> option;
        
        switch(option){
                // =================== CASE 0 ===================
            case 0:{
                break;
            }
                // =================== CASE 1 ===================
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
                        int x, y;
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
                
                cout << "Plane is " << obstacles[0]->find_plane(5) << endl;
                obstacles[0]->print_num_vertices();
                break;
            }
                // =================== CASE 2 ===================
            case 2:{
                cout << obstacles.size() << " object(s)." << endl << endl;
                break;
            }
                // =================== CASE 3 ===================
            case 3:{
                for(unsigned int i = 0; i < total_planes.size(); i++){
                    planes.push_back(new Plane(total_planes[i]));
                }
                for(unsigned int i = 0; i < planes.size(); i++){
                    Plane* plane = planes[i];
                    plane -> findObstaclesInPlane(obstacles);
                }
                break;
            }
                // =================== CASE 4 ===================
            case 4:{
                cout << " What is the source point of the search?" << endl;
                cout << " What is the target point of the search?" << endl;
                //TO DO;
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
