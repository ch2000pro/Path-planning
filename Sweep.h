#ifndef SWEEP
#define SWEEP

#include <list>
#include <vector>
#include "point.h"
using namespace std;

class Sweep {
public:
	Sweep() {}

	list<Point> endpoints;

	void sortEndpoints(vector<Point*>);
	void split(vector<Point*>, int, int, vector<Point*>);
	void merge(vector<Point*>, int, int, int, vector<Point*>);
};

#endif

