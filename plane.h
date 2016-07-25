/*
 * plane.h
 *
 *  Created on: Jul 5, 2016
 *      Author: feisabel
 */

#ifndef PLANE_H_
#define PLANE_H_

#include "boost/config.hpp"
#include "boost/graph/graph_traits.hpp"
#include "boost/graph/adjacency_list.hpp"
#include "boost/graph/dijkstra_shortest_paths.hpp"
#include "boost/property_map/property_map.hpp"
#include "boost/property_map/transform_value_property_map.hpp"
#include "boost/bind.hpp"

#include <queue>
#include <climits>

#include <fstream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <iostream>
#include "point.h"
#include "segment.h"
#include "obstacle.h"

class Obstacle;
class Point;

using namespace std;

//Plane is a 2D plane
class Plane {
public:
    Plane(unsigned int z); //constructor with the z coordinate
     ~Plane(); //destructor
    void addObstacle(vector<Point*>); //adds the vertices and edges of an obstacle that are in this plane
    void lineSweep(Point*, Point*); //the 2D path planning algo; creates a graph for the plane
    void findObstaclesInPlane(vector<Obstacle*> Map); //finds the obstacles that are found in this plane
    void createGraph();
    vector<Segment*> getEdges();
    void projectPoints(Point*, Point*);
    Point* getPointFromId(vector<Point*> nodes, int id);
    vector<Point*> getNodes();
    bool nodeExistsInPlane(Point* p);
    Point* getPointByCoordinates(double x, double y, double z);
    
private:
    vector<Point*> endpoints; //all the obstacle vertices in this plane
    vector<Segment*> obstacleSegments;
    unsigned int z; //the z coordinate of this plane
    vector<Point*> nodes; //nodes of the graph created for this plane
    vector<Segment*> medianLines;
    vector<Segment*> edges_; //edges of the graph created for this plane
    set<double> Xs;
    set<double> Ys;

    //auxiliary functions
    void LineSweepLTR(vector<Point*>);
    void LineSweepRTL(vector<Point*>);
    void LineSweepBTT(vector<Point*>);
    void LineSweepTTB(vector<Point*>);
    vector<Segment*> checkProjections(Segment*, Segment*, set<Segment*>, bool); //checks if there are any intersections between projections and objects, in order to create Steiner points
    Point* createSteinerPoint(Segment*, Segment*); //creates a Steiner point and an edge associated to it
    void createVerticalMedianLines(vector<Point*>, int, Point*, Point*); //creates lines that will be used to make type 1 Steiner points
    void createHorizontalMedianLines(vector<Point*>, int, Point*, Point*);
    double findDistance(Point* p0, Point* p1); //function to find the real distance between two points in the plane
    double findAngle(double a, double b, double c); //function to find the angle between three points
    Segment* projectLTR(Point*); //checks if a projection is possible and creates that projection if so for the left to right line sweep
    Segment* projectRTL(Point*); //checks if a projection is possible and creates that projection if so for the right to left line sweep
    Segment* projectBTT(Point*); //checks if a projection is possible and creates that projection if so for the down to up line sweep
    Segment* projectTTB(Point*); //checks if a projection is possible and creates that projection if so for the up to down line sweep
    pair<double, double> findIntersection(Segment*, Segment*);
    
};

#endif