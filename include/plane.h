/*----------------------------------------------------------------------*/
/*  plane.h                                                          */
/*  Plane representing a given Z coordinate                             */
/*  Fernanda Isabel, Gianluca Cagliari, Laura Vieira, Leonardo Castilho */
/*  Start: July 5, 2016                                                 */
/*----------------------------------------------------------------------*/

#ifndef PLANE_H_
#define PLANE_H_

#include <queue>
#include <climits>
#include <fstream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <iostream>

//include other program files to be used in the Plane functions
#include "point.h"
#include "segment.h"
#include "obstacle.h"

class Obstacle;
class Point;

using namespace std;

//Plane is a 2D plane
class Plane {
public:
    Plane(double z); //constructor with the z coordinate
     ~Plane(); //destructor
    void addObstacle(vector<Point*>); //adds the vertices and edges of an obstacle that are in this plane
    void lineSweep(Point*, Point*); //the 2D path planning algo; creates a graph for the plane
    void findObstaclesInPlane(vector<Obstacle*> Map); //finds the obstacles that are found in this plane
    vector<Segment*> getEdges(); //returns the private vector of segments 'edges_'
    vector<Point*> getNodes(); //returns the private vector of nodes of the plane
    bool nodeExistsInPlane(Point* p); //returns if a given point is in that plane or not
    
private:
    vector<Point*> endpoints; //all the obstacle vertices in this plane
    vector<Segment*> obstacleSegments; //vector of all obstacles segments (or edges)
    double z; //the z coordinate of this plane
    vector<Point*> nodes; //nodes of the graph created for this plane
    vector<Segment*> medianLines; //lines created recursively to assist the line sweep
    vector<Segment*> edges_; //edges of the graph created for this plane
    map<double, Segment*> verticalMedianLines; //vertical lines created recursively to assist the line sweep
    map<double, Segment*> horizontalMedianLines; //horizontal lines created recursively to assist the line sweep

    //auxiliary functions
    void LineSweepLTR(vector<Point*>); //line sweep from left to right
    void LineSweepRTL(vector<Point*>); //line sweep from right to left
    void LineSweepBTT(vector<Point*>); //line sweep from bottom to top
    void LineSweepTTB(vector<Point*>); //line sweep from top to bottom
    vector<Segment*> checkProjections(Segment*, Segment*, set<Segment*>, bool); //checks if there are any intersections between projections and objects, in order to create Steiner points
    Point* createSteinerPoint(Segment*, Segment*); //creates a Steiner point and an edge associated to it
    void createVerticalMedianLines(vector<Point*>, int, Point*, Point*); //creates lines that will be used to make type 1 Steiner points
    void createHorizontalMedianLines(vector<Point*>, int, Point*, Point*); //creates lines that will be used to make type 1 Steiner points
    double findDistance(Point* p0, Point* p1); //function to find the real distance between two points in the plane
    double findAngle(double a, double b, double c); //function to find the angle between three points
    Segment* projectLTR(Point*); //checks if a projection is possible and creates that projection if so for the left to right line sweep
    Segment* projectRTL(Point*); //checks if a projection is possible and creates that projection if so for the right to left line sweep
    Segment* projectBTT(Point*); //checks if a projection is possible and creates that projection if so for the down to up line sweep
    Segment* projectTTB(Point*); //checks if a projection is possible and creates that projection if so for the up to down line sweep
    pair<double, double> findIntersection(Segment*, Segment*); //given two segments, finds the point where they intersect
    
};

#endif