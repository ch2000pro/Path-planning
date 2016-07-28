/*----------------------------------------------------------------------*/
/*  segment.h                                                           */
/*  Line segment between two points                                     */
/*  Fernanda Isabel, Gianluca Cagliari, Laura Vieira, Leonardo Castilho */
/*  Start: July 5, 2016                                                 */
/*----------------------------------------------------------------------*/

#ifndef SEGMENT_H_
#define SEGMENT_H_

#include "point.h"
using namespace std;

//Segment is a line segment between two points
class Segment {
public:
    //default constructor
	Segment() {
		left = 0;
		right = 0;
		weight = 0;
        aux1 = 0;
        aux2 = 0;
	}
    //constructor that receives endpoints
	Segment(Point* a, Point* b) {
		left = a;
		right = b;
		weight = 0;
        aux1 = 0;
        aux2 = 0;
	}
    //constructor that receives endpoints and a weight
	Segment(Point* a, Point* b, int w) {
		left = a;
		right = b;
		weight = w;
        aux1 = 0;
        aux2 = 0;
	}

	Point* getLeft() {return left;} //returns the left endpoint
	Point* getRight() {return right;} //returns the right endpoint
    Point* getOther(Point* p){ //given one endpoint, returns the other
        if(p == left){
            return right;
        }
        else{
            return left;
        }
    }
    double weight; //the weight of the segment
    void setLeft(Point* a) {left = a;} //given a point, sets the left endpoint to that point
    void setRight(Point* a) {right = a;} //given a point, sets the right endpoint to that point
    double getWeight() {return weight;} // returns the weight
    void setWeight(double w) {weight = w;} //given a value, sets the weight to that value
    void addSteinerPoint(Point* p) {steinerPoints.push_back(p);} //given a point, adds that point to the list of steiner points on this segment
    vector<Point*> getSteinerPoints() {return steinerPoints;} //returns the list of steiner points on this segment
    bool case1() {return ((left->getY() < right->getY()) || (left->getY() == right->getY() && left->getX() < right->getX()));} //checks if the endpoints need to be swapped, in order to perform the horizontal line sweeps
    void setAux1(Segment* s) {aux1 = s;} //given a segment, sets the auxiliary segment to that segment
    Segment* getAux1() {return aux1;} //returns the auxiliary segment
    void setAux2(Point* p) {aux2 = p;} //given a point, sets the auxialiary point to that point
    Point* getAux2() {return aux2;} //returns the auxiliary point
    void zeroSteinerPoints() {while (steinerPoints.size() != 0) steinerPoints.pop_back();}

private:
	Point* left; //left endpoint
	Point* right; //right endpoint

    Segment* aux1; //auxiliary segment
    Point* aux2; //auxiliary point
    vector<Point*> steinerPoints; //steiner points created in this segment
};



#endif
