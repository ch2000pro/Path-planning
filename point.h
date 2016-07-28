/*----------------------------------------------------------------------*/
/*  point.h                                                             */
/*  3D point with x, y and z coordinates                                */
/*  Fernanda Isabel, Gianluca Cagliari, Laura Vieira, Leonardo Castilho */
/*  Start: July 5, 2016                                                 */
/*----------------------------------------------------------------------*/

#ifndef POINT_H
#define POINT_H

class Segment;

//Point is a 3D point
class Point
{
public:
    //default constructor
    Point(){
        x = 0; y = 0; z = 0; seg1 = 0; seg2 = 0;
    }
    
    //constructor that receives x and y coordinates
    Point(double my_x, double my_y){
        x = my_x; y = my_y; z = 0; seg1 = 0; seg2 = 0;
    }
    
    //constructor that receives x, y and z coordinates
    Point(double my_x, double my_y, double my_z){
        x = my_x; y = my_y; z = my_z; seg1 = 0; seg2 = 0;
    }
    
    void setX(double x_){ x = x_; } //given a value, sets the x coordinate to that value
    void setY(double y_){ y = y_; } //given a value, sets the y coordinate to that value
    void setZ(double z_){ z = z_; } //given a value, sets the z coordinate to that value
    int getId(){ return id_; } //returns the id
    void setId(int k){ id_ = k; } //given a value, sets the id to that value
    double getX() {return x;} //returns the x coordinate
    double getY() {return y;} //returns the y coordinate
    double getZ() {return z;} //returns the z coordinate
    Segment* getSeg1() {return seg1;} //returns the first segment
    Segment* getSeg2() {return seg2;} //returns the second segment
    void setSeg1(Segment* s) {seg1 = s;} //given a segment, sets the first segment to that segment
    void setSeg2(Segment* s) {seg2 = s;} //given a segment, sets the second segment to that segment
    Segment* getOther(Segment* s) {if (s == seg1) return seg2; else return seg1;} //given a segment, returns the other segment
    Point* clone() const { return new Point(*this); } //returns a copy of this point
    
private:
    int id_; //point id
    double x, y, z; //the points x, y and z coordinates
    Segment* seg1; //a segment that has this point as one of its endpoints
    Segment* seg2; //a segment that has this point as one of its endpoints
    
};

#endif
