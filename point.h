/*-----------------------------------------------*/
/*  point.h                                      */
/*  Vertices with x and y coordinates            */
/*  Leonardo Castilho                            */
/*  Start: June 15th                             */
/*-----------------------------------------------*/

#ifndef POINT_H
#define POINT_H

class Segment;

//Point is a 3D point
class Point
{
 public:
 Point(){
     x = 0; y = 0; z = 0; seg1 = 0; seg2 = 0;
 }
 
 Point(int my_x, int my_y){ 
     x = my_x; y = my_y; z = 0; seg1 = 0; seg2 = 0;
 }
    
 Point(int my_x, int my_y, int my_z){
     x = my_x; y = my_y; z = my_z; seg1 = 0; seg2 = 0;
 }
    
 int getX() {return x;}
 int getY() {return y;}
 int getZ() {return z;}
 Segment* getSeg1() {return seg1;}
 Segment* getSeg2() {return seg2;}
 void setSeg1(Segment* s) {seg1 = s;}
 void setSeg2(Segment* s) {seg2 = s;}

 private:
 int x, y, z; //the points coordinates
 Segment* seg1; //a segment that has this point as one of its endpoints
 Segment* seg2; //a segment that has this point as one of its endpoints
 
};

#endif
