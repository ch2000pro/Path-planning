/*----------------------------------------------------------------------*/
/*  test.cpp                                                            */
/*  Leading program containing to Main()                                */
/*  Fernanda Isabel, Gianluca Cagliari, Laura Vieira, Leonardo Castilho */
/*  Distributed under the Boost Software License, Version 1.61          */
/*
/*  Start: June 15, 2016                                                */
/*----------------------------------------------------------------------*/

//Includes the Boost open source library to be able to create Graphs and run Dijkstra to find the shortest path
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
#include "graphics.hpp"

using namespace std;

int main (int argc, char **argv){
    unsigned int option = 0, vertices_ = 0, planesInserted = 0, flag_planes = 0; //options in the input menu
    double height; //variable  input the height of an obstacle
    vector<double> total_planes; //vector storing all Z coordinates where the obstacles change
    vector<Obstacle*> obstacles; //total vector of all obstacles
    map<double, Plane*> planes; //map containing all planes: it contains a double Z coordinate and a Plane in that coordinate
    
    //first menu
    do{
        cout << endl;
        cout << "Select an option:" << endl;
        cout << "1 - Create a new obstacle" << endl; //option to create a new obstacle
        cout << "2 - Use default map 1" << endl; //default map 1
        cout << "3 - Use default map 2" << endl; //default map 2
        cout << "4 - Use default map 3" << endl; //default map 2 - Big map
        cout << "0 - Proceed" << endl; //option to stop creating obstacles and go to the second menu
        cin >> option;
        
        switch(option){
            case 0:{
                if(obstacles.size() == 0){
                    cout <<endl << "You must input at least one obstacle" << endl;
                    cout << "or try one of the default maps"<<endl;
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
                double totalheight = 0;
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
                    totalheight += height;
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
                        //if vector of all planes Z coordinates does not contain a certain Z, it adds this Z to the plane
                        if(std::find(total_planes.begin(), total_planes.end(), totalheight) != total_planes.end()) {
                            //vector of all planes already contains this height
                        } else {
                            //vector does not contain this height
                            total_planes.push_back(totalheight);
                        }
                        flag_planes = 1;
                    }
                    else{
                        obstacles[obstacles.size()-1]->add_vertices(vertices_input, height);
                        if(std::find(total_planes.begin(), total_planes.end(), totalheight) != total_planes.end()) {
                            //vector of all planes already contains this height
                        } else {
                            total_planes.push_back(totalheight);
                        }
                    }
                    planesInserted--;
                    height = 0;
                }
                break;
            }
            //default map containing rectangles
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
                
                //adding planes to the vector of Z coordinates
                total_planes.push_back(0);
                total_planes.push_back(8);
                total_planes.push_back(15);
                total_planes.push_back(18);
                total_planes.push_back(19);
                
                break;
            }
            //default map containing rectangles and triangles
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
                
                //Third obstacle
                vertices_input.push_back(new Point(34.1,22));
                vertices_input.push_back(new Point(39.2,27.9));
                vertices_input.push_back(new Point(41.8,20.5));
                obstacles.push_back(new Obstacle(vertices_input,12));
                vertices_input.clear();
                
                //adding planes to the vector of Z coordinates
                total_planes.push_back(0);
                total_planes.push_back(12);
                
                break;
            }
            //default map with more obstacles - big obstacles
            case 4:{
                vector<Point*> vertices_input;
                
                //First obstacle
                vertices_input.push_back(new Point(10,35));
                vertices_input.push_back(new Point(50,35));
                vertices_input.push_back(new Point(50,10));
                vertices_input.push_back(new Point(10,10));
                obstacles.push_back(new Obstacle(vertices_input,85));
                vertices_input.clear();
                
                //Second obstacle
                vertices_input.push_back(new Point(222,57));
                vertices_input.push_back(new Point(222,15));
                vertices_input.push_back(new Point(180,15));
                obstacles.push_back(new Obstacle(vertices_input,50));
                vertices_input.clear();
                
                //Third obstacle
                vertices_input.push_back(new Point(250,263));
                vertices_input.push_back(new Point(350,263));
                vertices_input.push_back(new Point(350,13));
                vertices_input.push_back(new Point(250,13));
                obstacles.push_back(new Obstacle(vertices_input,75));
                vertices_input.clear();
                
                //Fourth obstacle
                vertices_input.push_back(new Point(20,250));
                vertices_input.push_back(new Point(100,170));
                vertices_input.push_back(new Point(20,170));
                obstacles.push_back(new Obstacle(vertices_input,50));
                vertices_input.clear();
                
                //Fifth obstacle
                vertices_input.push_back(new Point(76,260));
                vertices_input.push_back(new Point(126,260));
                vertices_input.push_back(new Point(126,210));
                vertices_input.push_back(new Point(76,210));
                obstacles.push_back(new Obstacle(vertices_input,38));
                vertices_input.clear();
                
                //Sixth obstacle
                vertices_input.push_back(new Point(132,223));
                vertices_input.push_back(new Point(212,223));
                vertices_input.push_back(new Point(212,143));
                obstacles.push_back(new Obstacle(vertices_input,90));
                vertices_input.clear();
                
                //Seventh obstacle
                vertices_input.push_back(new Point(35,130));
                vertices_input.push_back(new Point(195,130));
                vertices_input.push_back(new Point(195,50));
                vertices_input.push_back(new Point(35,50));
                obstacles.push_back(new Obstacle(vertices_input,40));
                vertices_input.clear();
                
                vertices_input.push_back(new Point(65,115));
                vertices_input.push_back(new Point(165,115));
                vertices_input.push_back(new Point(165,65));
                vertices_input.push_back(new Point(65,65));
                obstacles[obstacles.size()-1]->add_vertices(vertices_input, 23);
                vertices_input.clear();
                
                vertices_input.push_back(new Point(102,115));
                vertices_input.push_back(new Point(165,115));
                vertices_input.push_back(new Point(165,83));
                vertices_input.push_back(new Point(102,83));
                obstacles[obstacles.size()-1]->add_vertices(vertices_input, 19);
                vertices_input.clear();
                
                //adding planes to the vector of Z coordinates
                total_planes.push_back(0);
                total_planes.push_back(38);
                total_planes.push_back(40);
                total_planes.push_back(50);
                total_planes.push_back(63);
                total_planes.push_back(75);
                total_planes.push_back(82);
                total_planes.push_back(85);
                total_planes.push_back(90);
                
                break;
            }
        }
        
    }while(option == 1 || (option == 0 && obstacles.size() == 0));
    
    option = 0;
    //second menu
    do{
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
                typedef boost::property<boost::edge_weight_t, double> EdgeWeightProperty; //boost library weight property for edges
                typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, Point*, EdgeWeightProperty> Graph; //bost definition of an adjacency list representing a graph
                typedef boost::graph_traits<Graph>::vertex_descriptor vertex_t; //vertex descriptor in the boost library
                typedef boost::graph_traits<Graph>::edge_descriptor edge_t; //edge descriptor in the boost library
                double sourceX, sourceY, sourceZ, targetX, targetY, targetZ;
                double highestZ = 0; //value representing the highest Z between the source and target
                Graph myGraph; //graph
                
                cout << " What is the source point of the search? (x, y and z)" << endl;
                cin >> sourceX;
                cin >> sourceY;
                cin >> sourceZ;
                cout << " What is the target point of the search? (x, y and z)" << endl;
                cin >> targetX;
                cin >> targetY;
                cin >> targetZ;
                
                Point* source_ = new Point(sourceX, sourceY, sourceZ); //source point according to the input coordinates
                Point* target_ = new Point(targetX, targetY, targetZ); //target point according to the input coordinates
                
                //keeps record of the source and target below, so its possible to create edges between the sources, targets and their projections in higher planes as the algorithm moves up. This information is not stored in the format of Points, but in the format vertex_t, the format in which the vertices are represented in the boost graph.
                vertex_t sourceBelowVertex;
                vertex_t targetBelowVertex;
                
                vertex_t s_; //source stored in the format vertex_t
                vertex_t t_; //target stored in the format vertex_t
                unsigned int id= 0; //variable to set the points ids
                vector<vertex_t> nodes_; //nodes of Points in the format vertex_t
                vector<double> distances; //vector storing the distances to assist in the backtraking after dijkstra
                
                //creates a plane for each Z coordinate in the total planes and find the obstacles in that plane
                int z;
                for (vector<double>::iterator it = total_planes.begin() ; it != total_planes.end(); ++it) {
                    z = *it;
                    Plane* plane = new Plane(z);
                    planes[z] = plane;
                    plane -> findObstaclesInPlane(obstacles);
                }
                
                //case 1: if the source and target are in the same Z coordinate
                if(sourceZ == targetZ){
                    highestZ = sourceZ;
                    Plane* plane;
                    map <unsigned int, vertex_t> verts;
                    source_->setId(id);
                    s_ = boost::add_vertex(source_, myGraph);
                    verts[id] = s_;
                    id++;
                    
                    target_->setId(id);
                    t_ = boost::add_vertex(target_, myGraph);
                    verts[id] = t_;
                    id++;
                    
                    //check if there is a plane in that z already
                    if(std::find(total_planes.begin(), total_planes.end(), sourceZ) != total_planes.end()) {
                        //if it is, just adds the point to the plane
                        plane = planes[sourceZ];
                        if(!plane->nodeExistsInPlane(source_) && !plane->nodeExistsInPlane(target_))
                            plane -> lineSweep(source_, target_);
                        else if (!plane->nodeExistsInPlane(source_))
                            plane -> lineSweep(source_, 0);
                        else if(!plane->nodeExistsInPlane(target_))
                            plane -> lineSweep(0, target_);
                        else
                            plane -> lineSweep(0, 0);
                    } else {
                        //if it is not, a plane in that Z coordinate must be created
                        plane = new Plane(sourceZ);
                        planes[sourceZ] = plane;
                        plane -> findObstaclesInPlane(obstacles);
                        if(!plane->nodeExistsInPlane(source_) && !plane->nodeExistsInPlane(target_))
                            plane -> lineSweep(source_, target_);
                        else if (!plane->nodeExistsInPlane(source_))
                            plane -> lineSweep(source_, 0);
                        else if(!plane->nodeExistsInPlane(target_))
                            plane -> lineSweep(0, target_);
                        else
                            plane -> lineSweep(0, 0);
                    }
                    
                    vector<Point*> nodes = plane->getNodes();
                    vector<Segment*> edges_ = plane -> getEdges();
                    
                    //adding nodes to graph
                    for(vector<Point*>::iterator it = nodes.begin(); it != nodes.end(); it++) {
                        Point* v = *it;
                        if((abs(v->getX() - target_->getX()) > 0.0000000001 || abs(v->getY() - target_->getY()) > 0.00000000001) && (abs(v->getX() - source_->getX()) > 0.0000000001 || abs(v->getY() - source_->getY()) > 0.00000000001)){
                            v->setId(id);
                            vertex_t u = boost::add_vertex(v, myGraph);
                            verts[id] = u;
                            id++;
                        }
                        else {
                            if (abs(v->getX() - target_->getX()) < 0.0000000001 && abs(v->getY() - target_->getY()) < 0.00000000001)
                                v->setId(target_->getId());
                            else
                                v->setId(source_->getId());
                        }
                    }
                    
                    //adding edges between nodes
                    for(vector<Segment*>::iterator it = edges_.begin(); it != edges_.end(); it++) {
                        Segment* edge = *it;
                        Point* right = edge->getRight();
                        Point* left =  edge->getLeft();
                        vertex_t u = verts[right->getId()];
                        vertex_t v = verts[left->getId()];
                        boost::add_edge(u,v , EdgeWeightProperty(edge->getWeight()), myGraph);
                    }
                    
                    sourceBelowVertex = s_;
                    targetBelowVertex = t_;
                    
                }
                else{
                    //If Source and Target Zs are different
                    Plane* plane;
                    map <unsigned int, vertex_t> verts;
                    //case 2
                    if(sourceZ > targetZ){
                        highestZ = sourceZ;
                        vertex_t targetProjectionVertex;
                        Point* targetProjection = new Point(target_->getX(), target_->getY(), source_->getZ());
                        
                        target_->setId(id);
                        t_ = boost::add_vertex(target_, myGraph);
                        verts[id] = t_;
                        id++;
                        
                        source_->setId(id);
                        s_ = boost::add_vertex(source_, myGraph);
                        verts[id] = s_;
                        id++;
                        
                        targetProjection->setId(id);
                        targetProjectionVertex = boost::add_vertex(targetProjection, myGraph);
                        verts[id] = targetProjectionVertex;
                        id++;
                        
                        
                        //check if there is a plane in that z already
                        if(std::find(total_planes.begin(), total_planes.end(), sourceZ) != total_planes.end()) {
                            //if it is, just adds the point to the plane
                            plane = planes[sourceZ];
                            if(!plane->nodeExistsInPlane(targetProjection) && !plane->nodeExistsInPlane(source_))
                                plane -> lineSweep(source_, targetProjection);
                            else if (!plane->nodeExistsInPlane(targetProjection))
                                plane -> lineSweep(0, targetProjection);
                            else if(!plane->nodeExistsInPlane(source_))
                                plane -> lineSweep(source_, 0);
                            else
                                plane -> lineSweep(0, 0);
                        }
                        //case 3
                        else {
                            //if it is not, a plane in that Z coordinate must be created
                            plane = new Plane(source_->getZ());
                            planes[source_->getZ()] = plane;
                            plane -> findObstaclesInPlane(obstacles);
                            if(!plane->nodeExistsInPlane(targetProjection) && !plane->nodeExistsInPlane(source_))
                                plane -> lineSweep(source_, targetProjection);
                            else if (!plane->nodeExistsInPlane(targetProjection))
                                plane -> lineSweep(0, targetProjection);
                            else if(!plane->nodeExistsInPlane(source_))
                                plane -> lineSweep(source_, 0);
                            else
                                plane -> lineSweep(0, 0);
                        }
                        
                        vector<Point*> nodes = plane->getNodes();
                        vector<Segment*> edges_ = plane -> getEdges();
                        
                        //adding nodes to graph
                        for(vector<Point*>::iterator it = nodes.begin(); it != nodes.end(); it++) {
                            Point* v = *it;
                            if((abs(v->getX() - source_->getX()) > 0.0000000001 || abs(v->getY() - source_->getY()) > 0.00000000001) && (abs(v->getX() - targetProjection->getX()) > 0.0000000001 || abs(v->getY() - targetProjection->getY()) > 0.00000000001)){
                                v->setId(id);
                                vertex_t u = boost::add_vertex(v, myGraph);
                                verts[id] = u;
                                id++;
                            }
                            else {
                                if (abs(v->getX() - targetProjection->getX()) < 0.0000000001 && abs(v->getY() - targetProjection->getY()) < 0.00000000001)
                                    v->setId(targetProjection->getId());
                                else
                                    v->setId(source_->getId());
                            }
                        }
                        
                        //adding edges between nodes
                        for(vector<Segment*>::iterator it = edges_.begin(); it != edges_.end(); it++) {
                            Segment* edge = *it;
                            Point* right = edge->getRight();
                            Point* left =  edge->getLeft();
                            vertex_t u = verts[right->getId()];
                            vertex_t v = verts[left->getId()];
                            boost::add_edge(u,v , EdgeWeightProperty(edge->getWeight()), myGraph);
                        }
                        
                        //add edge connecting target and target projection to the graph
                        double edgeDistance = targetProjection->getZ() - target_->getZ();
                        boost::add_edge(t_, targetProjectionVertex, EdgeWeightProperty(edgeDistance), myGraph);

                        sourceBelowVertex = s_;
                        targetBelowVertex = targetProjectionVertex;
                        
                    }
                    //case 4
                    else if(targetZ > sourceZ){
                        highestZ = targetZ;
                        vertex_t sourceProjectionVertex;
                        source_->setId(id);
                        s_ = boost::add_vertex(source_, myGraph);
                        verts[id] = s_;
                        id++;
                        
                        Point* sourceProjection = new Point(source_->getX(), source_->getY(), target_->getZ());
                        //check if there is a plane in that z already
                        if(std::find(total_planes.begin(), total_planes.end(), targetZ) != total_planes.end()) {
                            //if it is, just adds the point to the plane
                            plane = planes[targetZ];
                            if(!plane->nodeExistsInPlane(sourceProjection) && !plane->nodeExistsInPlane(target_))
                                plane->lineSweep(sourceProjection, target_);
                            else if (!plane->nodeExistsInPlane(sourceProjection))
                                plane ->lineSweep(sourceProjection, 0);
                            else if(!plane->nodeExistsInPlane(target_))
                                plane -> lineSweep(0, target_);
                            else
                                plane -> lineSweep(0, 0);
                        }//case 5
                        else {
                            //if it is not, a plane in that Z coordinate must be created
                            plane = new Plane(target_->getZ());
                            planes[target_->getZ()] = plane;
                            plane->findObstaclesInPlane(obstacles);
                            if(!plane->nodeExistsInPlane(sourceProjection) && !plane->nodeExistsInPlane(target_))
                                plane->lineSweep(sourceProjection, target_);
                            else if (!plane->nodeExistsInPlane(sourceProjection))
                                plane ->lineSweep(sourceProjection, 0);
                            else if(!plane->nodeExistsInPlane(target_))
                                plane -> lineSweep(0, target_);
                            else
                                plane -> lineSweep(0, 0);
                        }
                        vector<Point*> nodes = plane->getNodes();
                        vector<Segment*> edges_ = plane -> getEdges();
                        
                        //adding nodes to graph
                        for(vector<Point*>::iterator it = nodes.begin(); it != nodes.end(); it++) {
                            Point* v = *it;
                            v->setId(id);
                            vertex_t u = boost::add_vertex(v, myGraph);
                            verts[id] = u;
                            id++;
                            
                            if(abs(v->getX() - sourceProjection->getX()) < 0.0000000001 && abs(v->getY() - sourceProjection->getY()) < 0.00000000001 ){
                                sourceProjectionVertex = u;
                            }
                            
                            if(abs(v->getX() - target_->getX()) < 0.0000000001 && abs(v->getY() - target_->getY()) < 0.00000000001 ){
                                t_ = u;
                            }
                        }
                        
                        //adding edges between nodes
                        for(vector<Segment*>::iterator it = edges_.begin(); it != edges_.end(); it++) {
                            Segment* edge = *it;
                            Point* right = edge->getRight();
                            Point* left =  edge->getLeft();
                            vertex_t u = verts[right->getId()];
                            vertex_t v = verts[left->getId()];
                            boost::add_edge(u,v , EdgeWeightProperty(edge->getWeight()), myGraph);
                        }
                        
                        //add edge connecting source and source projection to the graph
                        double edgeDistance = sourceProjection->getZ() - source_->getZ();
                        boost::add_edge(s_, sourceProjectionVertex, EdgeWeightProperty(edgeDistance), myGraph);
                        
                        sourceBelowVertex = sourceProjectionVertex;
                        targetBelowVertex = t_;
                    }
                }
                
                sort(total_planes.begin(), total_planes.end());
                
                //after the plane of the highest is created and added to the graph, it creates the projection in all planes above and adds that planes to the graph
                for(vector<double>::iterator it = total_planes.begin(); it != total_planes.end(); it++) {
                    double z = *it;
                    if(z>highestZ){
                        map <unsigned int, vertex_t> verts;
                        vertex_t targetProjectionVertex;
                        vertex_t sourceProjectionVertex;
                        Plane* plane = planes[z];
                        Point* targetProjection = new Point(target_->getX(), target_->getY(), z);
                        Point* sourceProjection = new Point(source_->getX(), source_->getY(), z);
                        if(!plane->nodeExistsInPlane(targetProjection) && !plane->nodeExistsInPlane(sourceProjection))
                            plane->lineSweep(sourceProjection, targetProjection);
                        else if(!plane->nodeExistsInPlane(sourceProjection))
                            plane->lineSweep(sourceProjection, 0);
                        else if(!plane->nodeExistsInPlane(targetProjection))
                            plane->lineSweep(0, targetProjection);
                        else
                            plane -> lineSweep(0, 0);
                        vector<Point*> nodes = plane->getNodes();
                        vector<Segment*> edges_ = plane -> getEdges();
                        
                        //adding nodes to graph
                        for(vector<Point*>::iterator it = nodes.begin(); it != nodes.end(); it++) {
                            Point* v = *it;
                            v->setId(id);
                            vertex_t u = boost::add_vertex(v, myGraph);
                            verts[id] = u;
                            id++;
                            if(abs(v->getX() - targetProjection->getX()) < 0.0000000001 && abs(v->getY() - targetProjection->getY()) < 0.0000000001){
                                targetProjectionVertex = u;
                            }
                            if(abs(v->getX() - sourceProjection->getX()) < 0.000000001 && abs(v->getY() - sourceProjection->getY()) < 0.0000000001){
                                sourceProjectionVertex = u;
                            }
                        }
                        
                        //adding edges between nodes
                        for(vector<Segment*>::iterator it = edges_.begin(); it != edges_.end(); it++) {
                            Segment* edge = *it;
                            Point* right = edge->getRight();
                            Point* left =  edge->getLeft();
                            vertex_t u = verts[right->getId()];
                            vertex_t v = verts[left->getId()];
                            boost::add_edge(u,v , EdgeWeightProperty(edge->getWeight()), myGraph);
                        }
                        
                        //add edge connecting the source in the plane below with the projection of the source in the plane above
                        double edgeDistance = sourceProjection->getZ() - myGraph[sourceBelowVertex]->getZ();
                        boost::add_edge(sourceBelowVertex, sourceProjectionVertex, EdgeWeightProperty(edgeDistance), myGraph);
              
                        //add edge connecting target and target projection to the graph
                        double edgeDistance2 = targetProjection->getZ() - myGraph[targetProjectionVertex]->getZ();
                        boost::add_edge(targetBelowVertex, targetProjectionVertex, EdgeWeightProperty(edgeDistance2), myGraph);
                        
                        sourceBelowVertex = sourceProjectionVertex;
                        targetBelowVertex = targetProjectionVertex;
                        
                    }
                }
                
                // The property map associated with the weights.
                boost::property_map < Graph, boost::edge_weight_t>::type EdgeWeightMap = get(boost::edge_weight, myGraph);
                std::vector<vertex_t> p(num_vertices(myGraph));
                std::vector<int> d(num_vertices(myGraph));
                
                boost::graph_traits < Graph >::edge_iterator ei, ei_end;
                for (boost::tie(ei, ei_end) = edges(myGraph); ei != ei_end; ++ei) {
                    edge_t e = *ei;
                    EdgeWeightMap[e] *= 1000;
                }
                
                //running dijkstra according to Boost library
                dijkstra_shortest_paths(myGraph,s_,
                                        boost::predecessor_map(boost::make_iterator_property_map(p.begin(), get(boost::vertex_index, myGraph))).
                                        distance_map(boost::make_iterator_property_map(d.begin(), get(boost::vertex_index, myGraph))).
                                        weight_map(EdgeWeightMap));
                
                

                cout << "Shortest path from the source ("<< myGraph[t_]->getX() << " " << myGraph[t_]->getY() << " " << myGraph[t_]->getZ() << ") is :"<< endl;
                //backtracking path from target to source
                do{
                    nodes_.push_back(t_);
                    distances.push_back(d[t_]);
                    t_ = p[t_];
                }while(t_ != s_);
                nodes_.push_back(s_);
                distances.push_back(d[s_]);
                
                
                //printing results
                for(int i = 0; i<nodes_.size(); i++){
                    vertex_t p = nodes_[i];
                    cout << "Point(" << myGraph[p]->getX() << " " << myGraph[p]->getY() << " " << myGraph[p]->getZ() << "), with distance " << (distances[i]/ 1000) << endl;
                }
                
                fstream dot_file("path.txt", fstream::out);
                vertex_t prev = nodes_[0];
                for(int i = 1; i<nodes_.size(); i++){
                    vertex_t p = nodes_[i];
                    dot_file << myGraph[prev]->getX() << " " << myGraph[prev]->getY() << " " << myGraph[prev]->getZ() << " " << myGraph[p]->getX() << " " << myGraph[p]->getY() << " " << myGraph[p]->getZ()<< endl;
                    prev = p;
                }
                
                dot_file.close();
                
                glutInit               (&argc, argv);
                glutInitWindowSize     (900, 600);
                glutInitWindowPosition (300, 300);
                glutInitDisplayMode    (GLUT_DEPTH | GLUT_DOUBLE);
                
                glutCreateWindow ("Orbital Font Demo");
                glutDisplayFunc  (   redraw  );
                glutKeyboardFunc (  Keyboard );
                glutSpecialFunc  (Special_Keys);
                
                //glClearColor(0.8, 0.87, 0.94, 0.0);	// White Background
                glClearColor(0.88, 0.97, 1.0, 0.0);	// White Background
                
                glMatrixMode   (GL_PROJECTION);
                gluPerspective (60, 1.5, 1, 10);
                glMatrixMode   (GL_MODELVIEW);
                glutMainLoop   ();
                
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
