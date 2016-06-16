/*-----------------------------------------------*/
/*  point.h                                      */
/*  Vertices with x and y coordinates            */
/*  Leonardo Castilho                            */
/*  Start: June 15th                             */
/*-----------------------------------------------*/

#ifndef POINT_H
#define POINT_H

class Point
{
 public:
 Point(){
   x = 0; y = 0;
 }
 
 Point(int my_x, int my_y){ 
   x = my_x; y = my_y;
 } 
 
 int x;
 int y;
 
};

#endif
