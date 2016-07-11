/*
 * plane.cpp
 *
 *  Created on: Jul 5, 2016
 *      Author: feisabel
 */

#include <vector>
#include "plane.h"

Plane::Plane(unsigned int z_){
    z = z_;
}

Plane::~Plane(){
    
}

//Given a vector of points, adds those points (and the edges between them) to the plane
void Plane::addObstacle(vector<Point*> points) {
	vector<Point*>::iterator it;
	Point* p1;
	Point* p2;
	for (it = points.begin() ; it != prev(points.end()); ++it) {
		p1 = *it;
		p2 = *(next(it));
		Segment* seg;
		if (p1->getX() < p2->getX() || (p1->getX() == p2->getX() && p1->getY() > p2->getY()))
			seg = new Segment(p1, p2);
		else
			seg = new Segment(p2, p1);
		p1->setSeg2(seg);
		p2->setSeg1(seg);
		segments.push_back(seg);
	    endpoints.push_back(*it);
	}
	p1 = *it;
	p2 = *(points.begin());
	Segment* seg;
	if (p1->getX() < p2->getX() || (p1->getX() == p2->getX() && p1->getY() > p2->getY()))
		seg = new Segment(p1, p2);
	else
		seg = new Segment(p2, p1);
	p1->setSeg2(seg);
	p2->setSeg1(seg);
	segments.push_back(seg);
	endpoints.push_back(*it);
	delete seg;
}

//Recursive function that creates median lines (that will be used to make type 1 Steiner points)
vector<Segment*> Plane::createMedianLines(vector<Point*> points, int w) {
	vector<Segment*> lines;
	if (points.size() == 1)
		return lines;
	else {
		vector<Point*>::iterator middle = points.begin() + points.size()/2;
		int x = (*middle)->getX();
		Point* p1 = new Point(x, 2147483647);
		Point* p2 = new Point(x, -2147483648);
		Segment* l = new Segment(p1, p2, w);
		vector<Point*> aux1(points.begin(), middle - 1), aux2(middle + 1, points.end());
		vector<Segment*> lines2;
		vector<Segment*> lines3;
		lines2 = Plane::createMedianLines(aux1, w+1);
		lines3 = Plane::createMedianLines(aux2, w+1);
		lines.push_back(l);
		lines.insert(next(lines.end()), lines2.begin(), lines2.end());
		lines.insert(next(lines.end()), lines3.begin(), lines3.end());
		delete p1, p2, l;
		return lines;
	}
}

void Plane::findObstaclesInPlane(vector<Obstacle*> Map){
    
}

