/*
 * plane.cpp
 *
 *  Created on: Jul 5, 2016
 *      Author: feisabel
 */

#include <vector>
#include <iterator>
#include "plane.h"
#include <cmath>
#define PI 3.14159265

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
	for (it = points.begin() ; it != (points.end())-1; ++it) {
		p1 = *it;
		p2 = *((it)+1);
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
    list<Segment*> segments;
    Segment* s1 = p->getSeg1();
    Segment* s2 = p->getSeg2();
    if (s2 == 0) {
        for(list<Segment*>::iterator it = segments.begin(); it != segments.end(); it++) {
            if ((*it)->getWeight() > s1->getWeight()) {
                Plane::createSteinerPoint(s1, *it);
                Point aux(p->getX(), (*it)->getRight()->getY());
                (*it)->setLeft(&aux);
                (*it)->setWeight(s1->getWeight());
            }
        }
    }
    else if (s1->getLeft() == p && s2->getLeft() == p) {
        segments.push_back(s1);
        segments.push_back(s2);
        for(list<Segment*>::iterator it = segments.begin(); it != segments.end(); it++) {
            if ((*it)->getWeight() != 0) {
                int ly1, ry1, ly2, ry2, ly, ry;
                ly = (*it)->getLeft()->getY();
                ry = (*it)->getRight()->getY();
                ly1 = s1->getLeft()->getY();
                ry1 = s1->getRight()->getY();
                ly2 = s2->getLeft()->getY();
                ry2 = s2->getRight()->getY();
                if ((ly > ly1 && ry < ry1) || (ly < ly1 && ry > ry1)) {
                    Plane::createSteinerPoint(s1, *it);
                    segments.erase(it);
                }
                else if ((ly > ly2 && ry < ry2) || (ly < ly2 && ry > ry2)) {
                    Plane::createSteinerPoint(s2, *it);
                    segments.erase(it);
                }
            }
        }
       // if(canProject){
            //project;
        //}
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
    
    m1 = (left1 -> getY() - right1 -> getY())/(left1 -> getX() - right1 -> getX());
    m2 = (left2 -> getY() - right2 -> getY())/(left2 -> getX() - right2 -> getX());
    c1 = right1 -> getY() - (m1 * right1 -> getX());
    c2 = right2 -> getY() - (m2 * right2 -> getX());
    x = (c2 - c1)/(m1 - m2);
    y = (m1 * x) + c1;
    
    Point steiner(x, y, right1 -> getZ());
    segment1->addSteinerPoint(&steiner);
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

//auxiliary function to the Line Sweep, it checks if point is inside or outside an obstacle so it can create a projection to the next obstacle and create Steiner Points
bool Plane::canProject(Point* p0, Point* p1, Point* p2) {
    double highestX = 0;
    double c0, b0, a0, angle0;
    double c2, b2, a2, angle2;
    Point* p_;
    //finding the highest X
    if(p0 -> getX() >= p1 -> getX() && p0 -> getX() >= p2 -> getX()){
        highestX = p0 -> getX();
    }
    if(p1 -> getX() >= p0 -> getX() && p1 -> getX() >= p2 -> getX()){
        highestX = p1 -> getX();
    }
    if(p2 -> getX() >= p0 -> getX() && p2 -> getX() >= p1 -> getX()){
        highestX = p2 -> getX();
    }
    p_ = new Point(highestX, p1->getY(), z);
    if(p1 -> getX() == p_ -> getX()){
        p_ -> setX(p_ -> getX()+1);
    }
    
    //finding P0 angle
    c0 = findDistance(p0, p_);
    b0 = findDistance(p1, p_);
    a0 = findDistance(p0, p1);
    angle0 = findAngle(a0, b0, c0);
    
    if(p0 -> getY() > p1 -> getY()){
        angle0 = 2 * PI - angle0;
    }
    
    //finding P2 angle
    c2 = findDistance(p2, p_);
    b2 = findDistance(p1, p_);
    a2 = findDistance(p2, p1);
    angle2 = findAngle(a2, b2, c2);

    if(p2 -> getY() > p1 -> getY()){
        angle2 = 2 * PI - angle2;
    }
    
    //comparing angles
    if(angle2 == 0 || angle2 > angle0){
        return false;
    }
    else{
        return true;
    }
}

//auxiliary function to the function canProject, it finds the euclidean distance between two points (so the angle between euclidean lines can be calculated)
double Plane::findDistance(Point* p0, Point* p1){
    return sqrt(pow(p0 -> getX() - p1 -> getX(), 2) + pow(p0 -> getY() - p1 -> getY(), 2));
}

//auxiliary function to the function canProject, it finds the angle between euclidean points distance. This way, it can be checked if the angle is inside or outside an obstacle.
double Plane::findAngle(double a, double b, double c){
    return acos((pow(a, 2) + pow(b, 2) - pow(c, 2))/(2 * a * b));
}

//Function that runs through all the obstacles to check if they are obstacles in that plane
//For each one found, add that obstacle to the 2D Plane 
void Plane::findObstaclesInPlane(vector<Obstacle*> obstacles){
    vector<Obstacle*>::iterator it;
    Obstacle* obstacle;
    for (it = obstacles.begin() ; it != obstacles.end(); ++it) {
        obstacle = *it;
        if(obstacle-> get_height() > z){
            addObstacle(obstacle -> get_vertices(z));
        }
        else{
            return;
        }
    }
}

