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
#include "2D_point.h"
#include "segment.h"

using namespace std;

class Plane {
public:
	Plane() {}

	vector<Point*> endpoints;
	vector<Segment*> segments;

	void addObstacle(vector<Point*>);
	void lineSweep();
	vector<Segment*> createMedianLines(vector<Point*>, int);
};

#endif

