/*
 * segment.h
 *
 *  Created on: Jul 6, 2016
 *      Author: feisabel
 */

#ifndef SEGMENT_H_
#define SEGMENT_H_

#include "point.h"

//Segment is a line between two points
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

private:
	Point* left; //left endpoint
	Point* right; //right endpoint
	int weight;
};



#endif
