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
    
    //vector<double> graphsZs;
    //map<double, Graph> graphsMap;
    
    do{
        cout << endl;
        cout << "Select an option:" << endl;
        cout << "1 - Create a new obstacle" << endl;
        cout << "2 - Use default map" << endl; //Default map is drawn
        cout << "3 - Use map1" << endl; //Professor's map
        cout << "4 - Use map2" << endl; //Big map
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
                
                //Plane* plane = new Plane(0);
                //plane -> findObstaclesInPlane(obstacles);
                //plane -> lineSweep();
                //plane -> createGraph();
                
                int z;
                for (vector<double>::iterator it = total_planes.begin() ; it != total_planes.end(); ++it) {
                    z = *it;
                    Plane* plane = new Plane(z);
                    planes[z] = plane;
                    plane -> findObstaclesInPlane(obstacles);
                    plane -> lineSweep();
                }
                
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
                
                //Third obstacle
                /*vertices_input.push_back(new Point(34.1,22));
                vertices_input.push_back(new Point(39.2,27.9));
                vertices_input.push_back(new Point(41.8,20.5));
                obstacles.push_back(new Obstacle(vertices_input,12));
                vertices_input.clear();*/
                
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
              vertices_input.push_back(new Point(76,110));
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
              
              total_planes.push_back(38);
              total_planes.push_back(40);
              total_planes.push_back(50);
              total_planes.push_back(63);
              total_planes.push_back(75);
              total_planes.push_back(82);
              total_planes.push_back(85);
              total_planes.push_back(90);
              
              //---------DEBUG----REMOVE---------
              cout << endl << "Obstacle 1...";
              obstacles[0]->print_num_vertices();
              cout << endl << "Obstacle 2...";
              obstacles[1]->print_num_vertices();
              cout << endl << "Obstacle 3...";
              obstacles[2]->print_num_vertices();
              cout << endl << "Obstacle 4...";
              obstacles[3]->print_num_vertices();
              cout << endl << "Obstacle 5...";
              obstacles[4]->print_num_vertices();
              cout << endl << "Obstacle 6...";
              obstacles[5]->print_num_vertices();
              cout << endl << "Obstacle 7...";
              obstacles[6]->print_num_vertices();
              //---------------------------------
              break;
            }
        }
        
    }while(option == 1);
    
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
                typedef boost::property<boost::edge_weight_t, double> EdgeWeightProperty;
                typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, Point*, EdgeWeightProperty> Graph;
                typedef boost::graph_traits<Graph>::vertex_descriptor vertex_t;
                typedef boost::graph_traits<Graph>::edge_descriptor edge_t;
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
                vertex_t s_;
                vertex_t t_;
                unsigned int id=0;
                vector<vertex_t> nodes_;
                map<unsigned int, Point*> totalNodes;
                vector<Point*> finalPath;
                vector<double> distances;
                
           
                
                //case 1
                if(sourceZ == targetZ){
                    cout << "soure == target"<<endl;
                    highestZ = sourceZ;
                    Plane* plane;
                    map <unsigned int, vertex_t> verts;
                    //check if there is a plane in that z already
                    if(std::find(total_planes.begin(), total_planes.end(), sourceZ) != total_planes.end()) {
                        //if it is, just adds the point to the plane
                        plane = planes[sourceZ];
                        plane -> projectPoints(source_, target_);
                        /*if(!plane->nodeExistsInPlane(source_)){
                            plane -> projectPoint(source_);
                        }
                        if(!plane->nodeExistsInPlane(target_)){
                            plane -> projectPoint(target_);
                        }*/
                    } else {
                        //if it is not, a plane in that Z coordinate must be created
                        plane = new Plane(sourceZ);
                        planes[sourceZ] = plane;
                        plane -> findObstaclesInPlane(obstacles);
                        plane -> lineSweep();
                        plane -> projectPoints(source_, target_);
                        /*if(!plane->nodeExistsInPlane(source_)){
                            plane -> projectPoint(source_);
                        }
                        if(!plane->nodeExistsInPlane(target_)){
                            plane -> projectPoint(target_);
                        }*/
                    }
                    
                    vector<Point*> nodes = plane->getNodes();
                    vector<Segment*> edges_ = plane -> getEdges();
                    //adding nodes to graph
                    for(vector<Point*>::iterator it = nodes.begin(); it != nodes.end(); it++) {
                        Point* v = *it;
                        cout << "vertice of plane " << v-> getX() << " " <<  v->getY() << " "<< v->getZ()<<endl;
                        if(v-> getX() >= 0 && v->getY() >=0 && v->getZ()>= 0){
                            v->setId(id);
                            vertex_t u = boost::add_vertex(v, myGraph);
                            verts[id] = u;
                            totalNodes[id] = v;
                            id++;
                            if(v->getX() == source_->getX() && v->getY() == source_->getY() && v->getZ() == source_->getZ()){
                                s_ = u;
                            }
                            if(v->getX() == target_->getX() && v->getY() == target_->getY() && v->getZ() == target_->getZ()){
                                t_ = u;
                            }
                        }
                    }
                    
                    //adding edges between nodes
                    for(vector<Segment*>::iterator it = edges_.begin(); it != edges_.end(); it++) {
                        Segment* edge = *it;
                        Point* right = edge->getRight();
                        Point* left =  edge->getLeft();
                        if(right->getX() >= 0 && right->getY() >=0 && right->getZ()>= 0 && left->getX() >= 0 && left->getY() >= 0 && left->getZ() >= 0){
                            vertex_t u = verts[right->getId()];
                            vertex_t v = verts[left->getId()];
                            boost::add_edge(u,v , EdgeWeightProperty(edge->getWeight()), myGraph);
                        }
                    }
                }
                else{
                    //If Source and Target Zs are different
                    Plane* plane;
                    map <unsigned int, vertex_t> verts;
                    //case 2
                    if(sourceZ > targetZ){
                        highestZ = sourceZ;
                        vertex_t targetProjectionVertex;
                        bool projectionExists = false;
                        Point* targetProjection = new Point(target_->getX(), target_->getY(), source_->getZ());
                        //check if there is a plane in that z already
                        if(std::find(total_planes.begin(), total_planes.end(), sourceZ) != total_planes.end()) {
                            //if it is, just adds the point to the plane
                            plane = planes[sourceZ];
                            if(plane->nodeExistsInPlane(targetProjection)){
                                projectionExists = true;
                            }
                            plane -> projectPoints(source_, targetProjection);
                            /*else{
                                plane -> projectPoint(targetProjection);
                            }
                            if(!plane->nodeExistsInPlane(source_)){
                                plane -> projectPoint(source_);
                            }*/
                        }
                        //case 3
                        else {
                            //if it is not, a plane in that Z coordinate must be created
                            plane = new Plane(source_->getZ());
                            planes[source_->getZ()] = plane;
                            plane -> findObstaclesInPlane(obstacles);
                            plane -> lineSweep();
                            if(plane->nodeExistsInPlane(targetProjection)){
                                projectionExists = true;
                            }
                            plane -> projectPoints(source_, targetProjection);
                            /*else{
                                plane -> projectPoint(targetProjection);
                            }
                            if(!plane->nodeExistsInPlane(source_)){
                                plane -> projectPoint(source_);
                            }*/
                        }
                        
                        vector<Point*> nodes = plane->getNodes();
                        vector<Segment*> edges_ = plane -> getEdges();
                        
                        //adding nodes to graph
                        for(vector<Point*>::iterator it = nodes.begin(); it != nodes.end(); it++) {
                            Point* v = *it;
                            if(v-> getX() >= 0 && v->getY() >=0 && v->getZ()>= 0){
                                v->setId(id);
                                vertex_t u = boost::add_vertex(v, myGraph);
                                verts[id] = u;
                                totalNodes[id] = v;
                                id++;
                                if(projectionExists){
                                    if(v->getX() == targetProjection->getX() && v->getY() == targetProjection->getY() && v->getZ() == targetProjection->getZ()){
                                        targetProjectionVertex = u;
                                    }
                                }
                                if(v->getX() == source_->getX() && v->getY() == source_->getY() && v->getZ() == source_->getZ()){
                                    s_ = u;
                                }
                                if(v->getX() == target_->getX() && v->getY() == target_->getY() && v->getZ() == target_->getZ()){
                                    t_ = u;
                                }
                            }
                        }
                        
                        //adding edges between nodes
                        for(vector<Segment*>::iterator it = edges_.begin(); it != edges_.end(); it++) {
                            Segment* edge = *it;
                            Point* right = edge->getRight();
                            Point* left =  edge->getLeft();
                            if(right->getX() >= 0 && right->getY() >=0 && right->getZ()>= 0 && left->getX() >= 0 && left->getY() >= 0 && left->getZ() >= 0){
                                vertex_t u = verts[right->getId()];
                                vertex_t v = verts[left->getId()];
                                boost::add_edge(u,v , EdgeWeightProperty(edge->getWeight()), myGraph);
                            }
                        }
                        
                        //add edge connecting target and target projection to the graph
                        double edgeDistance = targetProjection->getZ() - target_->getZ();
                        vertex_t u = boost::add_vertex(target_, myGraph);

                        if(projectionExists){
                            boost::add_edge(u, targetProjectionVertex, EdgeWeightProperty(edgeDistance), myGraph);
                        }
                        else{
                            vertex_t v = boost::add_vertex(targetProjection, myGraph);
                            boost::add_edge(u, v,EdgeWeightProperty(edgeDistance), myGraph);
                        }
                        
                        sourceBelow = source_;
                        targetBelow = targetProjection;
                    }
                    //case 4
                    else if(targetZ > sourceZ){
                        highestZ = targetZ;
                        vertex_t sourceProjectionVertex;
                        bool projectionExists = false;
                        Point* sourceProjection = new Point(source_->getX(), source_->getY(), target_->getZ());
                        //check if there is a plane in that z already
                        if(std::find(total_planes.begin(), total_planes.end(), targetZ) != total_planes.end()) {
                            //if it is, just adds the point to the plane
                            plane = planes[targetZ];
                            if(plane->nodeExistsInPlane(sourceProjection)){
                                projectionExists = true;
                            }
                            plane -> projectPoints(sourceProjection, target_);
                            /*else{
                                plane -> projectPoint(sourceProjection);
                            }
                            if(!plane->nodeExistsInPlane(target_)){
                                plane -> projectPoint(target_);
                            }*/
                        }//case 5
                        else {
                            //if it is not, a plane in that Z coordinate must be created
                            plane = new Plane(target_->getZ());
                            planes[target_->getZ()] = plane;
                            plane -> findObstaclesInPlane(obstacles);
                            plane -> lineSweep();
                            if(plane->nodeExistsInPlane(sourceProjection)){
                                projectionExists = true;
                            }
                            plane -> projectPoints(sourceProjection, target_);
                            /*else{
                                plane -> projectPoint(sourceProjection);
                            }
                            if(!plane->nodeExistsInPlane(target_)){
                                plane -> projectPoint(target_);
                            }*/
                        }
                        vector<Point*> nodes = plane->getNodes();
                        vector<Segment*> edges_ = plane -> getEdges();
                        
                        //adding nodes to graph
                        for(vector<Point*>::iterator it = nodes.begin(); it != nodes.end(); it++) {
                            Point* v = *it;
                            if(v-> getX() >= 0 && v->getY() >=0 && v->getZ()>= 0){
                                v->setId(id);
                                vertex_t u = boost::add_vertex(v, myGraph);
                                verts[id] = u;
                                totalNodes[id] = v;
                                id++;
                                if(projectionExists){
                                    if(v->getX() == sourceProjection->getX() && v->getY() == sourceProjection->getY() && v->getZ() == sourceProjection->getZ()){
                                        sourceProjectionVertex = u;
                                    }
                                }
                                if(v->getX() == source_->getX() && v->getY() == source_->getY() && v->getZ() == source_->getZ()){
                                    s_ = u;
                                }
                                if(v->getX() == target_->getX() && v->getY() == target_->getY() && v->getZ() == target_->getZ()){
                                    t_ = u;
                                }
                            }
                        }
                        
                        //adding edges between nodes
                        for(vector<Segment*>::iterator it = edges_.begin(); it != edges_.end(); it++) {
                            Segment* edge = *it;
                            Point* right = edge->getRight();
                            Point* left =  edge->getLeft();
                            if(right->getX() >= 0 && right->getY() >=0 && right->getZ()>= 0 && left->getX() >= 0 && left->getY() >= 0 && left->getZ() >= 0){
                                vertex_t u = verts[right->getId()];
                                vertex_t v = verts[left->getId()];
                                boost::add_edge(u,v , EdgeWeightProperty(edge->getWeight()), myGraph);
                            }
                        }
                        
                        //add edge connecting source and source projection to the graph
                        double edgeDistance = sourceProjection->getZ() - source_->getZ();
                        vertex_t u = boost::add_vertex(source_, myGraph);
                        
                        if(projectionExists){
                            boost::add_edge(u, sourceProjectionVertex, EdgeWeightProperty(edgeDistance), myGraph);
                        }
                        else{
                            vertex_t v = boost::add_vertex(sourceProjection, myGraph);
                            boost::add_edge(u, v,EdgeWeightProperty(edgeDistance), myGraph);
                        }
   
                        sourceBelow = sourceProjection;
                        targetBelow = target_;
                    }
                }

                sort(total_planes.begin(), total_planes.end());
                
                //after the plane of the highest is created and added to the graph, it creates the projection in all planes above and adds that planes to the graph
                for(vector<double>::iterator it = total_planes.begin(); it != total_planes.end(); it++) {
                    double z = *it;
                    if(z>highestZ){
                        map <unsigned int, vertex_t> verts;
                        bool projectionExistsT = false;
                        bool projectionExistsS = false;
                        vertex_t targetProjectionVertex;
                        vertex_t sourceProjectionVertex;
                        Plane* plane = planes[z];
                        Point* targetProjection = new Point(target_->getX(), target_->getY(), z);
                        Point* sourceProjection = new Point(source_->getX(), source_->getY(), z);
                        if(plane->nodeExistsInPlane(targetProjection)){
                            projectionExistsT = true;
                        }
                        if(plane->nodeExistsInPlane(sourceProjection)){
                            projectionExistsS = true;
                        }
                        plane -> projectPoints(sourceProjection, targetProjection);
                        /*else{
                            plane -> projectPoint(targetProjection);
                        }
                        else{
                            plane -> projectPoint(sourceProjection);
                        }*/
                        
                        vector<Point*> nodes = plane->getNodes();
                        vector<Segment*> edges_ = plane -> getEdges();
                        
                        //adding nodes to graph
                        for(vector<Point*>::iterator it = nodes.begin(); it != nodes.end(); it++) {
                            Point* v = *it;
                            if(v-> getX() >= 0 && v->getY() >=0 && v->getZ()>= 0){
                                v->setId(id);
                                vertex_t u = boost::add_vertex(v, myGraph);
                                verts[id] = u;
                                totalNodes[id] = v;
                                id++;
                                if(projectionExistsT){
                                    if(v->getX() == targetProjection->getX() && v->getY() == targetProjection->getY() && v->getZ() == targetProjection->getZ()){
                                        targetProjectionVertex = u;
                                    }
                                }
                                if(projectionExistsS){
                                    if(v->getX() == sourceProjection->getX() && v->getY() == sourceProjection->getY() && v->getZ() == sourceProjection->getZ()){
                                        sourceProjectionVertex = u;
                                    }
                                }
                                if(v->getX() == source_->getX() && v->getY() == source_->getY() && v->getZ() == source_->getZ()){
                                    s_ = u;
                                }
                                if(v->getX() == target_->getX() && v->getY() == target_->getY() && v->getZ() == target_->getZ()){
                                    t_ = u;
                                }
                            }
                        }

                        //adding edges between nodes
                        for(vector<Segment*>::iterator it = edges_.begin(); it != edges_.end(); it++) {
                            Segment* edge = *it;
                            Point* right = edge->getRight();
                            Point* left =  edge->getLeft();
                            if(right->getX() >= 0 && right->getY() >=0 && right->getZ()>= 0 && left->getX() >= 0 && left->getY() >= 0 && left->getZ() >= 0){
                                vertex_t u = verts[right->getId()];
                                vertex_t v = verts[left->getId()];
                                boost::add_edge(u,v , EdgeWeightProperty(edge->getWeight()), myGraph);
                            }
                        }
                        
                        //add edge connecting the source in the plane below with the projection of the source in the plane above
                        double edgeDistance = sourceProjection->getZ() - sourceBelow->getZ();
                        vertex_t u = boost::add_vertex(sourceBelow, myGraph);
                        
                        if(projectionExistsS){
                            boost::add_edge(u, sourceProjectionVertex, EdgeWeightProperty(edgeDistance), myGraph);
                        }
                        else{
                            vertex_t v = boost::add_vertex(sourceProjection, myGraph);
                            boost::add_edge(u, v,EdgeWeightProperty(edgeDistance), myGraph);
                        }

                        //add edge connecting target and target projection to the graph
                        double edgeDistance2 = targetProjection->getZ() - targetBelow->getZ();
                        vertex_t r = boost::add_vertex(targetBelow, myGraph);
                        
                        if(projectionExistsT){
                            boost::add_edge(u, targetProjectionVertex, EdgeWeightProperty(edgeDistance), myGraph);
                        }
                        else{
                            vertex_t s = boost::add_vertex(targetProjection, myGraph);
                            boost::add_edge(r, s, EdgeWeightProperty(edgeDistance2), myGraph);
                        }

                        sourceBelow = sourceProjection;
                        targetBelow = targetProjection;
                        
                        }
                }
                
                
                // The property map associated with the weights.
                boost::property_map < Graph,
                boost::edge_weight_t >::type EdgeWeightMap = get(boost::edge_weight, myGraph);
                std::vector<vertex_t> p(num_vertices(myGraph));
                std::vector<int> d(num_vertices(myGraph));
                
                //running dijkstra
                dijkstra_shortest_paths(myGraph,s_,
                                        boost::predecessor_map(boost::make_iterator_property_map(p.begin(), get(boost::vertex_index, myGraph))).
                                        distance_map(boost::make_iterator_property_map(d.begin(), get(boost::vertex_index, myGraph))).
                                        weight_map(EdgeWeightMap));
                
                
                cout << "distances and parents: (distance of that point to the point (0, 0, 0)" << endl;
                boost::graph_traits <Graph>::vertex_iterator vi, vend;
                for (boost::tie(vi, vend) = vertices(myGraph); vi != vend; ++vi) {
                    vertex_t v = *vi;
                    vertex_t parent = p[*vi];
                    cout << "vertice: " << myGraph[v]->getX() << " " << myGraph[v]->getY() << " " << myGraph[v]->getZ()<< endl;
                    cout << "distance(" << myGraph[v]->getX() << " " << myGraph[v]->getY() << " " << myGraph[v]->getZ() << ") = " << d[*vi] << ", ";
                    cout << "parent(" << myGraph[v]->getX() << " " << myGraph[v]->getY() << " " << myGraph[v]->getZ() <<  ") = " << myGraph[parent]->getX() << " " << myGraph[parent]->getY() << " " << myGraph[parent]->getZ()<<endl;
                }
                cout << endl;
                
                
//                //backtracking path from target to source
//                do{
//                    nodes_.push_back(t_);
//                    finalPath.push_back(totalNodes[myGraph[t_]->getId()]);
//                    distances.push_back(d[t_]);
//                    t_ = p[t_];
//                }while(t_ != s_);
//                
//                finalPath.push_back(totalNodes[myGraph[s_]->getId()]);
//                distances.push_back(d[s_]);
//                
//
//                //printing results
//                for(int i = 0; i<finalPath.size(); i++){
//                    Point* p = finalPath[i];
//                    cout << "distance(" << p->getX() << " " << p->getY() << " " << p->getZ() << ") = " << distances[i] << endl;
//                }
//                
//                fstream dot_file("path.scr", fstream::out);
//                dot_file << "_-COLOR" << endl;
//                dot_file << "green" << endl;
//                dot_file << "3DPOLY" << endl;
//                for(int i = 0; i<finalPath.size(); i++){
//                    Point* p = finalPath[i];
//                    dot_file << p->getX() << "," << p->getY() << "," << p->getZ()<< endl;
//                }
//                dot_file << "CLOSE" << endl;
//                dot_file.close();

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
