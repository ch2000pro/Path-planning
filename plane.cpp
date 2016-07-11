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
		Segment seg;
		if (p1->getX() < p2->getX() || (p1->getX() == p2->getX() && p1->getY() > p2->getY())) {
			seg.setLeft(p1);
            seg.setRight(p2);
        }
		else {
			seg.setLeft(p2);
            seg.setRight(p1);
        }
		p1->setSeg2(&seg);
		p2->setSeg1(&seg);
	    endpoints.push_back(*it);
	}
	p1 = *it;
	p2 = points.front();
	Segment seg;
	if (p1->getX() < p2->getX() || (p1->getX() == p2->getX() && p1->getY() > p2->getY())) {
		seg.setLeft(p1);
        seg.setRight(p2);
    }
	else {
		seg.setLeft(p2);
        seg.setRight(p1);
    }
	p1->setSeg2(&seg);
	p2->setSeg1(&seg);
	endpoints.push_back(*it);
}

void Plane::lineSweep() {
    Plane::createMedianLines(endpoints, 1);
    sort(endpoints.rbegin(), endpoints.rend());
    Point* p = endpoints.back();
    endpoints.pop_back();
    vector<Segment*> segments;
    Segment* seg1 = p->getSeg1();
    Segment* seg2 = p->getSeg2();
    if (seg2 == 0) {
        for(vector<Segment*>::iterator it = segments.begin(); it != segments.end(); it++) {
            if ((*it)->getWeight() > seg1->getWeight()) {
                Plane::createSteinerPoint(*it, seg1);
                Point aux(p->getX(), (*it)->getRight()->getY());
                (*it)->setLeft(&aux);
                (*it)->setWeight(seg1->getWeight());
            }
        }
    }
    else if (seg1->getLeft() == p && seg2->getLeft() == p) {
        
    }
    else if (seg1->getRight() == p && seg2->getRight() == p) {
        
    }
    else {
        return;
    }
    
}

//Recursive function that creates median lines (that will be used to make type 1 Steiner points)
void Plane::createMedianLines(vector<Point*> points, int w) {
	if (points.size() > 1) {
		vector<Point*>::iterator middle = points.begin() + points.size()/2;
		int x = (*middle)->getX();
		Point p1(x, 2147483647);
		Point p2(x, -2147483648);
		Segment l(&p1, &p2, w);
        p1.setSeg1(&l);
        endpoints.push_back(&p1);
		vector<Point*> aux1(points.begin(), middle - 1), aux2(middle + 1, points.end());
		Plane::createMedianLines(aux1, w+1);
		Plane::createMedianLines(aux2, w+1);
    }
}

//Function that runs through all the obstacles to check if they are obstacles in that plane
//For each one found, add that obstacle to the 2D Plane 
void Plane::findObstaclesInPlane(vector<Obstacle*> obstacles){
    for(int i = 0; i < obstacles.size(); i++){
        Obstacle* obstacle = obstacles[i];
        if(obstacle-> get_height() > z){
            addObstacle(obstacle -> get_vertices(z));
        }
        else{
            return;
        }
    }
}

