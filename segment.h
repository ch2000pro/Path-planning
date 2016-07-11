/*
 * segment.h
 *
 *  Created on: Jul 6, 2016
 *      Author: feisabel
 */

#ifndef SEGMENT_H_
#define SEGMENT_H_

#include "point.h"

//Segment is a line segment between two points
class Segment {
public:
	Segment() {
		left = 0;
		right = 0;
		weight = 0;
	}
	Segment(Point* a, Point* b) {
		left = a;
		right = b;
		weight = 0;
	}
	Segment(Point* a, Point* b, int w) {
		left = a;
		right = b;
		weight = w;
	}

	Point* getLeft() {return left;}
	Point* getRight() {return right;}
    void setLeft(Point* a) {left = a;}
    void setRight(Point* a) {right = a;}
    int getWeight() {return weight;}
    void setWeight(int w) {weight = w;}

private:
	Point* left; //left endpoint
	Point* right; //right endpoint
	int weight;
};



#endif
