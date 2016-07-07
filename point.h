/*-----------------------------------------------*/
/*  point.h                                      */
/*  Vertices with x and y coordinates            */
/*  Leonardo Castilho                            */
/*  Start: June 15th                             */
/*-----------------------------------------------*/

#ifndef POINT_H
#define POINT_H

class Segment;

class Point
{
 public:
 Point(){
   x = 0; y = 0; seg1 = 0; seg2 = 0;
 }
 
 Point(int my_x, int my_y){ 
   x = my_x; y = my_y; seg1 = 0; seg2 = 0;
 } 
 
 int getX() {return x;}
 int getY() {return y;}
 Segment* getSeg1() {return seg1;}
 Segment* getSeg2() {return seg2;}

 private:
 int x;
 int y;
 Segment* seg1;
 Segment* seg2;
 
};

#endif
