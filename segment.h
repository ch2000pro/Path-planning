/*
 * segment.h
 *
 *  Created on: Jul 6, 2016
 *      Author: feisabel
 */

#ifndef SEGMENT_H_
#define SEGMENT_H_

#include "point.h"
using namespace std;

//Segment is a line segment between two points
class Segment {
public:
	Segment() {
		left = 0;
		right = 0;
		weight = 0;
        aux1 = 0;
        aux2 = 0;
	}
	Segment(Point* a, Point* b) {
		left = a;
		right = b;
		weight = 0;
        aux1 = 0;
        aux2 = 0;
	}
	Segment(Point* a, Point* b, int w) {
		left = a;
		right = b;
		weight = w;
        aux1 = 0;
        aux2 = 0;
	}

	Point* getLeft() {return left;}
	Point* getRight() {return right;}
    Point* getOther(Point* p){
        if(p == left){
            return right;
        }
        else{
            return left;
        }
    }
    double weight;
    void setLeft(Point* a) {left = a;}
    void setRight(Point* a) {right = a;}
    double getWeight() {return weight;}
    void setWeight(double w) {weight = w;}
    void addSteinerPoint(Point* p) {steinerPoints.push_back(p);}
    vector<Point*> getSteinerPoints() {return steinerPoints;}
    bool case1() {return ((left->getY() < right->getY()) || (left->getY() == right->getY() && left->getX() < right->getX()));}
    void setAux1(Segment* s) {aux1 = s;}
    Segment* getAux1() {return aux1;}
    void setAux2(Point* p) {aux2 = p;}
    Point* getAux2() {return aux2;}

private:
	Point* left; //left endpoint
	Point* right; //right endpoint

    Segment* aux1;
    Point* aux2;
    vector<Point*> steinerPoints; //steiner points created in this segment
};



#endif
