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

//lineSweep will create a graph representing the plane, in order to find the shortest path on it
void Plane::lineSweep() {
    Plane::createMedianLines(endpoints, 1);
    sort(endpoints.rbegin(), endpoints.rend());
    Point* p = endpoints.back();
    endpoints.pop_back();
    vector<Segment*> segments;
    Segment* s1 = p->getSeg1();
    Segment* s2 = p->getSeg2();
    if (s2 == 0) {
        for(vector<Segment*>::iterator it = segments.begin(); it != segments.end(); it++) {
            if ((*it)->getWeight() > s1->getWeight()) {
                Plane::createSteinerPoint(*it, s1);
                Point aux(p->getX(), (*it)->getRight()->getY());
                (*it)->setLeft(&aux);
                (*it)->setWeight(s1->getWeight());
            }
        }
    }
    else if (s1->getLeft() == p && s2->getLeft() == p) {
        segments.push_back(s1);
        segments.push_back(s2);
    }
    else if (s1->getRight() == p && s2->getRight() == p) {
        
    }
    else {
        return;
    }
    
}

//Given two segments, an obstacle edge and a projection, creates a steiner point from their intersection and the corresponding edge to it
void Plane::createSteinerPoint(Segment* segment1, Segment* segment2) {
    //find intersection
    float m1, m2, c1, c2, x, y;
    Point* right1 = segment1 -> getRight();
    Point* left1 = segment1 -> getLeft();
    Point* right2 = segment2 -> getRight();
    Point* left2 = segment2 -> getLeft();
    Point* steiner;
    
    m1 = (left1 -> getY() - right1 -> getY())/(left1 -> getX() - right1 -> getX());
    m2 = (left2 -> getY() - right2 -> getY())/(left2 -> getX() - right2 -> getX());
    c1 = right1 -> getY() - (m1 * right1 -> getX());
    c2 = right2 -> getY() - (m2 * right2 -> getX());
    x = (c2 - c1)/(m1 - m2);
    y = (m1 * x) + c1;
    
    steiner = new Point(x, y, right1 -> getZ());
    
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

