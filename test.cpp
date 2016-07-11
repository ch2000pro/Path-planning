/*-----------------------------------------------*/
/*  test.cpp                                     */
/*  Main program to run and test partial parts   */
/*  Leonardo Castilho                            */
/*  Start: June 15th                             */
/*-----------------------------------------------*/


#include "obstacle.h"
#include "point.h"

using namespace std;

int main (){
    unsigned int option = 0, vertices = 0, planes = 0, flag_planes = 0, height;
    vector<int> total_planes;
    total_planes.push_back(0);
    vector<Obstacle*> Map;
    
    do{ //Start menu
        //test
        cout << endl;
        cout << "Select an option:" << endl;
        cout << "1 - Create new obstacle" << endl;
        cout << "2 - Number of obstacles" << endl;
        cout << "3 - Find shortest path" << endl;
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
                    cin >> planes;
                    if(planes<2) cout << "An object of are non-zero must "
                        << "have at least 2 plane." << endl;
                }while(planes < 2);
                
                flag_planes = 0;
                while(planes > 1){
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
                        Map.push_back(new Obstacle(vertices_input,height));
                        if(std::find(total_planes.begin(), total_planes.end(), height) != total_planes.end()) {
                            //vector of all planes already contains this height
                        } else {
                           total_planes.push_back(height);
                        }
                        flag_planes = 1;
                    }
                    else{
                        unsigned int height_ = Map[Map.size()-1]->add_vertices(vertices_input, height);
                        if(std::find(total_planes.begin(), total_planes.end(), height) != total_planes.end()) {
                            //vector of all planes already contains this height
                        } else {
                            total_planes.push_back(height_);
                        }
                        flag_planes = 1;
                    }
                    planes--;
                    height = 0;
                }
                
                cout << "Plane is " << Map[0]->find_plane(5) << endl;
                Map[0]->print_num_vertices();
                break;
            }
                // =================== CASE 2 ===================
            case 2:{
                cout << Map.size() << " object(s)." << endl << endl;
                
                break;
            }
                // =================== CASE 3 ===================
            case 3:{
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
    while(Map.size() != 0){ //Delete items
        deleting = Map[Map.size()-1];
        delete deleting;
        Map.pop_back();
    }
    //-----------------------------
    
    
    
    return 0;
}
