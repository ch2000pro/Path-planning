/*
 * plane.h
 *
 *  Created on: Jul 5, 2016
 *      Author: feisabel
 */

#ifndef PLANE_H_
#define PLANE_H_

#include <list>
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
    void lineSweep(); //the 2D path planning algo; creates a graph for the plane
    void findObstaclesInPlane(vector<Obstacle*> Map); //finds the obstacles that are found in this plane
    
private:
    vector<Point*> endpoints; //all the obstacle vertices in this plane
    unsigned int z; //the z coordinate of this plane
    
    void createSteinerPoint(Segment*, Segment*); //creates a Steiner point and an edge associated to it
    void createMedianLines(vector<Point*>, int); //creates lines that will be used to make type 1 Steiner points
};

#endif

