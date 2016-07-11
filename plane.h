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
#include "point.h"
#include "segment.h"

using namespace std;

//Plane is a 2D plane
class Plane {
public:
	Plane() {}

	void addObstacle(vector<Point*>); //adds the vertices and edges of an obstacle that are in this plane
	void lineSweep(); //the 2D path planning algo; creates a graph for the plane
	vector<Segment*> createMedianLines(vector<Point*>, int); //creates lines that will be used to make type 1 Steiner points
    
private:
    vector<Point*> endpoints; //all the obstacle vertices in this plane
	vector<Segment*> segments; //all the obstacle edges in this plane
};

#endif

