/*
 * segment.h
 *
 *  Created on: Jul 6, 2016
 *      Author: feisabel
 */

#ifndef SEGMENT_H_
#define SEGMENT_H_

#include "point.h"

class Segment {
public:
	Segment() {}
	Segment(Point a, Point b) {
		left = a;
		right = b;
	}

	Point getLeft() {return left;}
	Point getRight() {return right;}

private:
	Point left, right;
};



#endif
