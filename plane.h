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
#include "point.h"

using namespace std;

class Plane {
public:
	Plane() {}

	vector<Point*> endpoints;

	void addEndpoints(vector<Point*>);
	void lineSweep();
	void split(vector<Point*>, int, int, vector<Point*>);
	void merge(vector<Point*>, int, int, int, vector<Point*>);
};

#endif

