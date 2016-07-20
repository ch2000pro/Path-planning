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

#include <fstream>
#include <string>
#include <map>
#include "obstacle.h"
#include "point.h"
#include "plane.h"

using namespace std;

int main (){
    unsigned int option = 0, vertices_ = 0, planesInserted = 0, flag_planes = 0;
    double height;
    vector<double> total_planes;
    vector<Obstacle*> obstacles;
    map<double, Plane*> planes;
    
    typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, Point > Graph;
    typedef boost::graph_traits<Graph>::vertex_descriptor vertex_t;
    typedef boost::graph_traits<Graph>::edge_descriptor edge_t;
    //vector<double> graphsZs;
    //map<double, Graph> graphsMap;
    
    do{
        cout << endl;
        cout << "Select an option:" << endl;
        cout << "1 - Create a new obstacle" << endl;
        cout << "2 - Use default map" << endl; //Default map is drawn
        cout << "3 - Use paper's map" << endl; //Professor's map
        cout << "0 - Proceed" << endl;
        cin >> option;
        
        
        switch(option){
            case 0:{
                int z;
                for (vector<double>::iterator it = total_planes.begin() ; it != total_planes.end(); ++it) {
                    z = *it;
                    Plane* plane = new Plane(z);
                    planes[z] = plane;
                    plane -> findObstaclesInPlane(obstacles);
                    plane -> lineSweep();
                }
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
                        cin >> vertices_;
                        if(vertices_<3) cout << "An object of are non-zero must "
                            << "have at least 3 vertices." << endl;
                    }while(vertices_ < 3);
                    cout << "What is the height of these segments? ";
                    cin >> height;
                    while(vertices_ > 0){
                        double x, y;
                        cout << "Enter x y: ";
                        cin >> x;
                        cin >> y;
                        vertices_input.push_back(new Point(x,y));
                        vertices_ --;
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
                vertices_input.push_back(new Point(0,9));
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
                
                Plane* plane = new Plane(0);
                plane -> findObstaclesInPlane(obstacles);
                plane -> lineSweep();
                cout << "testing" << endl;
                plane -> createGraph();
                
                break;
            }
            case 3:{
                vector<Point*> vertices_input;
                //First obstacle
                vertices_input.push_back(new Point(26.5,1.8));
                vertices_input.push_back(new Point(21.6,13));
                vertices_input.push_back(new Point(30.5,17));
                vertices_input.push_back(new Point(35.5,5.8));
                obstacles.push_back(new Obstacle(vertices_input,12));
                vertices_input.clear();
                
                //Second obstacle
                vertices_input.push_back(new Point(11.3,18.9));
                vertices_input.push_back(new Point(13.7,32.7));
                vertices_input.push_back(new Point(24.4,23.8));
                obstacles.push_back(new Obstacle(vertices_input,12));
                vertices_input.clear();
                
                //First obstacle
                //vertices_input.push_back(new Point(34.1,22));
                //vertices_input.push_back(new Point(39.2,27.9));
                //vertices_input.push_back(new Point(41.8,20.5));
                //obstacles.push_back(new Obstacle(vertices_input,12));
                //vertices_input.clear();
                
                total_planes.push_back(0);
                total_planes.push_back(12);
                
                //---------DEBUG----REMOVE---------
                cout << endl << "Obstacle 1...";
                obstacles[0]->print_num_vertices();
                cout << endl << "Obstacle 2...";
                obstacles[1]->print_num_vertices();
                //cout << endl << "Obstacle 3...";
                //obstacles[2]->print_num_vertices();
                //---------------------------------
                
                break;
            }
        }
        
    }while(option != 0 && option != 2 && option !=3);
    
    option = 0;
    do{ //Start menu
        //test
        cout << endl;
        cout << "Select an option:" << endl;
        cout << "1 - Number of obstacles" << endl;
        cout << "2 - Find shortest path" << endl;
        cout << "3 - Create edges" << endl;
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
                double sourceX, sourceY, sourceZ, targetX, targetY, targetZ;
                double highestZ = 0;
                Graph myGraph;
                
                cout << " What is the source point of the search? (x, y and z)" << endl;
                cin >> sourceX;
                cin >> sourceY;
                cin >> sourceZ;
                cout << " What is the target point of the search? (x, y and z)" << endl;
                cin >> targetX;
                cin >> targetY;
                cin >> targetZ;
                
                Point* source_ = new Point(sourceX, sourceY, sourceZ);
                Point* target_ = new Point(targetX, targetY, targetZ);
                Point* sourceBelow = source_;
                Point* targetBelow = target_;
                
                //case 1
                if(sourceZ == targetZ){
                    highestZ = sourceZ;
                    Plane* plane;
                    //check if there is a plane in that z already
                    if(std::find(total_planes.begin(), total_planes.end(), sourceZ) != total_planes.end()) {
                        //if it is, just adds the point to the plane
                        plane = planes[sourceZ];
                        plane -> addSourceAndTarget(source_, target_); //function to insert S and T to nodes and project the edges
                    } else {
                        //if it is not, a plane in that Z coordinate must be created
                        plane = new Plane(sourceZ);
                        plane -> findObstaclesInPlane(obstacles);
                        plane -> lineSweep();
                        plane -> addSourceAndTarget(source_, target_);
                    }
                    
                    sourceBelow = source_;
                    targetBelow = target_;
                    
                    vector<Segment*> edges_ = plane -> getEdges();
                    for(vector<Segment*>::iterator it = edges_.begin(); it != edges_.end(); it++) {
                        Point right = *(*it)->getRight();
                        Point left = *(*it)->getLeft();
                        vertex_t u = boost::add_vertex(right, myGraph);
                        vertex_t v = boost::add_vertex(left, myGraph);
                        boost::add_edge(u, v, myGraph);
                    }
                }
                else{
                    Plane* plane;
                    //case 2
                    if(sourceZ > targetZ){
                        highestZ = sourceZ;
                        
                        Point* targetProjection = new Point(targetX, targetY, sourceZ);
                        //check if there is a plane in that z already
                        if(std::find(total_planes.begin(), total_planes.end(), sourceZ) != total_planes.end()) {
                            //if it is, just adds the point to the plane
                            plane = planes[sourceZ];
                            plane -> addSourceAndTarget(source_, targetProjection);
                        }//case 3
                        else {
                            //if it is not, a plane in that Z coordinate must be created
                            plane = new Plane(sourceZ);
                            plane -> findObstaclesInPlane(obstacles);
                            plane -> lineSweep();
                            plane -> addSourceAndTarget(source_, targetProjection);
                        }
                        
                        //add edge connecting target and target projection to the graph
                        vertex_t u = boost::add_vertex(*target_, myGraph);
                        vertex_t v = boost::add_vertex(*targetProjection, myGraph);
                        boost::add_edge(u, v, myGraph);
                        
                        sourceBelow = source_;
                        targetBelow = targetProjection;
                    }
                    //case 4
                    else if(targetZ > sourceZ){
                        highestZ = targetZ;
                        Point* sourceProjection = new Point(sourceX, sourceY, targetZ);
                        //check if there is a plane in that z already
                        if(std::find(total_planes.begin(), total_planes.end(), targetZ) != total_planes.end()) {
                            //if it is, just adds the point to the plane
                            plane = planes[sourceZ];
                            plane -> addSourceAndTarget(sourceProjection, target_);
                        }//case 5
                        else {
                            //if it is not, a plane in that Z coordinate must be created
                            plane = new Plane(targetZ);
                            plane -> findObstaclesInPlane(obstacles);
                            plane -> lineSweep();
                            plane -> addSourceAndTarget(sourceProjection, target_);
                        }
                        
                        //add edge connecting source and source projection to the graph
                        vertex_t u = boost::add_vertex(*source_, myGraph);
                        vertex_t v = boost::add_vertex(*sourceProjection, myGraph);
                        boost::add_edge(u, v, myGraph);
                        
                        sourceBelow = sourceProjection;
                        targetBelow = target_;
                        
                    }
                    
                    vector<Segment*> edges_ = plane -> getEdges();
                    for(vector<Segment*>::iterator it = edges_.begin(); it != edges_.end(); it++) {
                        Point right = *(*it)->getRight();
                        Point left = *(*it)->getLeft();
                        vertex_t u = boost::add_vertex(right, myGraph);
                        vertex_t v = boost::add_vertex(left, myGraph);
                        boost::add_edge(u, v, myGraph);
                    }
                }
                
                sort(total_planes.begin(), total_planes.end());
                for(vector<double>::iterator it = total_planes.begin(); it != total_planes.end(); it++) {
                    double z = *it;
                    if(z>highestZ){
                        Plane* plane = planes[z];
                        Point* targetProjection = new Point(targetX, targetY, z);
                        Point* sourceProjection = new Point(sourceX, sourceY, z);
                        plane -> addSourceAndTarget(sourceProjection, targetProjection);
                        
                        //add edge connecting the source in the plane below with the projection of the source in the plane above
                        vertex_t u = boost::add_vertex(*sourceBelow, myGraph);
                        vertex_t v = boost::add_vertex(*sourceProjection, myGraph);
                        boost::add_edge(u, v, myGraph);
                        
                        //add edge connecting the target in the plane below with the projection of the target in the plane above
                        vertex_t r = boost::add_vertex(*targetBelow, myGraph);
                        vertex_t s = boost::add_vertex(*targetProjection, myGraph);
                        boost::add_edge(r, s, myGraph);
                        
                        vector<Segment*> edges_ = plane -> getEdges();
                        for(vector<Segment*>::iterator it = edges_.begin(); it != edges_.end(); it++) {
                            Point right = *(*it)->getRight();
                            Point left = *(*it)->getLeft();
                            vertex_t u = boost::add_vertex(right, myGraph);
                            vertex_t v = boost::add_vertex(left, myGraph);
                            boost::add_edge(u, v, myGraph);
                        }
                    }
                }
                //TO DO FIND SHORTEST PATH;
                break;
            }
            case 3: {
                Plane* plane = new Plane(0);
                plane -> findObstaclesInPlane(obstacles);
                plane -> lineSweep();
                //cout << "testing" << endl;
                //plane -> createGraph();
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
