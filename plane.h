#ifndef SWEEP
#define SWEEP

#include <list>
#include <vector>
#include "point.h"
using namespace std;

class Plane {
public:
	Plane() {}

	list<Point> endpoints;

	void lineSweep();
	void split(vector<Point*>, int, int, vector<Point*>);
	void merge(vector<Point*>, int, int, int, vector<Point*>);
};

#endif

