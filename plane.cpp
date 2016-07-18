/*
 * plane.cpp
 *
 *  Created on: Jul 5, 2016
 *      Author: feisabel
 */

#include <vector>
#include <iterator>
#include "plane.h"
#include "segment.h"
#include <cmath>
#include <typeinfo>
#define PI 3.14159265

Plane::Plane(unsigned int z_){
    z = z_;
}

Plane::~Plane(){
}

struct function1 {
    bool operator() (Point* a, Point* b) { return (a->getX() < b->getX() || (a->getX() == b->getX() && a->getY() > b->getY())); }
} sortLTR;

struct function2 {
    bool operator() (Point* a, Point* b) { return (a->getY() > b->getY() || (a->getY() == b->getY() && a->getX() > b->getX())); }
} sortTTB;

struct function3 {
    bool operator() (Point* a, Point* b) { return (a->getX() > b->getX() || (a->getX() == b->getX() && a->getY() > b->getY())); }
} sortRTL;

struct function4 {
    bool operator() (Point* a, Point* b) { return (a->getY() < b->getY() || (a->getY() == b->getY() && a->getX() > b->getX())); }
} sortBTT;

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

//Given a vector of points, adds those points (and the edges between them) to the plane
void Plane::addObstacle(vector<Point*> points) {
    vector<Point*>::iterator it;
    Point* p1;
    Point* p2;
    for (it = points.begin() ; it != points.end() - 1; ++it) {
        p1 = *it;
        p2 = *(it + 1);
        Segment* seg;
        if (p1->getX() < p2->getX() || (p1->getX() == p2->getX() && p1->getY() > p2->getY()))
            seg = new Segment(p1, p2);
        else
            seg = new Segment(p2, p1);
        p1->setSeg2(seg);
        p2->setSeg1(seg);
        endpoints.push_back(*it);
        nodes.push_back(*it);
        obstacleSegments.push_back(seg);
    }
    p1 = *it;
    p2 = points.front();
    Segment* seg;
    if (p1->getX() < p2->getX() || (p1->getX() == p2->getX() && p1->getY() > p2->getY()))
        seg = new Segment(p1, p2);
    else
        seg = new Segment(p2, p1);
    p1->setSeg2(seg);
    p2->setSeg1(seg);
    endpoints.push_back(*it);
    nodes.push_back(*it);
    obstacleSegments.push_back(seg);
}

void Plane::lineSweep() {
    vector<Point*> points1 = endpoints, points2 = endpoints;
    sort(points1.begin(), points1.end(), sortLTR);
    Plane::createVerticalMedianLines(points1, 1);
    sort(points2.begin(), points2.end(), sortTTB);
    Plane::createHorizontalMedianLines(points2, 1);
    for(vector<Segment*>::iterator it = medianLines.begin(); it != medianLines.end(); it++) {
        if((*it)->getRight()->getY() == -2147483648)
            points1.push_back((*it)->getRight());
        else
            points2.push_back((*it)->getRight());
    }
    Plane::LineSweepLTR(points1);
    cout << "edges after LTR: " << edges_.size() << endl;
    Plane::LineSweepRTL(points1);
    cout << "edges after RTL: " << edges_.size() << endl;
    Plane::LineSweepTTB(points2);
    cout << "edges after TTB: " << edges_.size() << endl;
    cout << edges_[0]->getLeft()->getX() << " " << edges_[0]->getLeft()->getY() << " " << edges_[0]->getRight()->getX() << " " << edges_[0]->getRight()->getY() << endl;
    cout << edges_[1]->getLeft()->getX() << " " << edges_[1]->getLeft()->getY() << " " << edges_[1]->getRight()->getX() << " " << edges_[1]->getRight()->getY() << endl;
    Plane::LineSweepBTT(points2);
    cout << "edges after BTT: " << edges_.size() << endl;
    for(vector<Segment*>::iterator l = medianLines.begin(); l != medianLines.end(); l++) {
        vector<Point*> steiners = (*l)->getSteinerPoints();
        sort(steiners.begin(), steiners.end(), sortLTR);
        Point* prev = 0;
        for(vector<Point*>::iterator p = steiners.begin(); p != steiners.end(); p++) {
            if((*p)->getZ() < 0) {
                if ((*p)->getZ() == -2) {
                    if (prev != 0) {
                        Segment* s = new Segment(prev, *p);
                        edges_.push_back(s);
                    }
                    prev = *p;
                }
                else
                    prev = 0;
            }
            else {
                if (prev != 0) {
                    Segment* s = new Segment(prev, *p);
                    edges_.push_back(s);
                }
                prev = *p;
            }
        }
    }
    for(vector<Segment*>::iterator l = obstacleSegments.begin(); l != obstacleSegments.end(); l++) {
        vector<Point*> steiners = (*l)->getSteinerPoints();
        sort(steiners.begin(), steiners.end(), sortLTR);
        Point *prev = (*l)->getLeft();
        for(vector<Point*>::iterator p = steiners.begin(); p != steiners.end(); p++) {
            Segment* s = new Segment(prev, *p);
            edges_.push_back(s);
            prev = *p;
        }
        Segment* s = new Segment(prev, (*l)->getRight());
        edges_.push_back(s);
    }
}

//lineSweep will create a graph representing the plane, in order to find the shortest path on it
void Plane::LineSweepLTR(vector<Point*> points) {
    sort(points.rbegin(), points.rend(), sortLTR);
    Point* p;
    set<Segment*> segments;
    vector<Segment*> needErase;
    while(points.size() > 0) {
        p = points.back();
        points.pop_back();
        Segment* s1 = p->getSeg1();
        Segment* s2 = p->getSeg2();
        if (s2 == 0) {
            for(set<Segment*>::iterator it = segments.begin(); it != segments.end(); it++) {
                if ((*it)->getWeight() > s1->getWeight()) {
                    if ((*it)->getLeft()->getX() != p->getX()) {
                        Point* steiner = Plane::createSteinerPoint(s1, *it);
                        Segment* s = new Segment((*it)->getLeft(), steiner);
                        edges_.push_back(s);
                        (*it)->setLeft(steiner);
                    }
                    (*it)->setWeight(s1->getWeight());
                }
                else if((*it)->getWeight() == 0) {
                    pair<double, double> point = Plane::findIntersection(s1, *it);
                    int k;
                    if ((*it)->getLeft()->getX() == point.first && (*it)->getLeft()->getY() == point.second && (*it)->getLeft()->getOther(*it)->getOther((*it)->getLeft())->getX() != (*it)->getLeft()->getX())
                        k = -2;
                    else
                        k = -1;
                    Point* aux = new Point(point.first, point.second, k);
                    s1->addSteinerPoint(aux);
                }
            }
        }
        else if (s1->getLeft() == p && s2->getLeft() == p) {
            segments.insert(s1);
            segments.insert(s2);
            needErase = Plane::checkProjections(s1, s2, segments, true);
            for (vector<Segment*>::iterator it = needErase.begin(); it != needErase.end(); it++)
                segments.erase(*it);
            Segment* aux = Plane::projectLTR(p);
            if (aux->getLeft() != 0)
                segments.insert(aux);
        }
        else if (s1->getRight() == p && s2->getRight() == p) {
            needErase = Plane::checkProjections(s1, s2, segments, true);
            for (vector<Segment*>::iterator it = needErase.begin(); it != needErase.end(); it++)
                segments.erase(*it);
            Segment* aux = Plane::projectLTR(p);
            if (aux->getLeft() != 0)
                segments.insert(aux);
            segments.erase(s1);
            segments.erase(s2);
        }
        else {
            bool b;
            if(segments.find(s1) == segments.end()) {
                segments.insert(s1);
                b = true;
            }
            else {
                segments.insert(s2);
                b = false;
            }
            needErase = Plane::checkProjections(s1, s2, segments, true);
            for (vector<Segment*>::iterator it = needErase.begin(); it != needErase.end(); it++)
                segments.erase(*it);
            Segment* aux = Plane::projectLTR(p);
            if (aux->getLeft() != 0)
                segments.insert(aux);
            if (b)
                segments.erase(s2);
            else
                segments.erase(s1);
        }
    }
}

void Plane::LineSweepRTL(vector<Point*> points) {
    sort(points.rbegin(), points.rend(), sortRTL);
    Point* p;
    set<Segment*> segments;
    vector<Segment*> needErase;
    while(points.size() > 0) {
        p = points.back();
        points.pop_back();
        Segment* s1 = p->getSeg1();
        Segment* s2 = p->getSeg2();
        if (s2 == 0) {
            for(set<Segment*>::iterator it = segments.begin(); it != segments.end(); it++) {
                if ((*it)->getWeight() > s1->getWeight()) {
                    if ((*it)->getRight()->getX() != p->getX()) {
                        Point* steiner = Plane::createSteinerPoint(s1, *it);
                        Segment* s = new Segment(steiner, (*it)->getRight());
                        edges_.push_back(s);
                        (*it)->setRight(steiner);
                    }
                    (*it)->setWeight(s1->getWeight());
                }
            }
        }
        else if (s1->getRight() == p && s2->getRight() == p) {
            segments.insert(s1);
            segments.insert(s2);
            needErase = Plane::checkProjections(s1, s2, segments, false);
            for (vector<Segment*>::iterator it = needErase.begin(); it != needErase.end(); it++)
                segments.erase(*it);
            Segment* aux = Plane::projectRTL(p);
            if (aux->getLeft() != 0)
                segments.insert(aux);
        }
        else if (s1->getLeft() == p && s2->getLeft() == p) {
            needErase = Plane::checkProjections(s1, s2, segments, false);
            for (vector<Segment*>::iterator it = needErase.begin(); it != needErase.end(); it++)
                segments.erase(*it);
            Segment* aux = Plane::projectRTL(p);
            if (aux->getLeft() != 0)
                segments.insert(aux);
            segments.erase(s1);
            segments.erase(s2);
        }
        else {
            bool b;
            if(segments.find(s1) == segments.end()) {
                segments.insert(s1);
                b = true;
            }
            else {
                segments.insert(s2);
                b = false;
            }
            needErase = Plane::checkProjections(s1, s2, segments, false);
            for (vector<Segment*>::iterator it = needErase.begin(); it != needErase.end(); it++)
                segments.erase(*it);
            Segment* aux = Plane::projectRTL(p);
            if (aux->getLeft() != 0)
                segments.insert(aux);
            if (b)
                segments.erase(s2);
            else
                segments.erase(s1);
        }
    }
}

void Plane::LineSweepTTB(vector<Point*> points) {
    sort(points.rbegin(), points.rend(), sortTTB);
    Point* p;
    set<Segment*> segments;
    vector<Segment*> needErase;
    while(points.size() > 0) {
        p = points.back();
        points.pop_back();
        Segment* s1 = p->getSeg1();
        Segment* s2 = p->getSeg2();
        bool b1 = false, b2 = false;
        if (s1->case1()) {
            Point* aux = s1->getLeft();
            s1->setLeft(s1->getRight());
            s1->setRight(aux);
            b1 = true;
        }
        if (s2 != 0 && s2->case1()) {
            Point* aux = s2->getLeft();
            s2->setLeft(s2->getRight());
            s2->setRight(aux);
            b2 = true;
        }
        if (s2 == 0) {
            for(set<Segment*>::iterator it = segments.begin(); it != segments.end(); it++) {
                if ((*it)->getWeight() > s1->getWeight()) {
                    if ((*it)->getLeft()->getY() != p->getY()) {
                        Point* steiner = Plane::createSteinerPoint(s1, *it);
                        Segment* s = new Segment((*it)->getLeft(), steiner);
                        edges_.push_back(s);
                        (*it)->setLeft(steiner);
                    }
                    (*it)->setWeight(s1->getWeight());
                }
                else if((*it)->getWeight() == 0) {
                    pair<double, double> point = Plane::findIntersection(s1, *it);
                    int k;
                    if (((*it)->getLeft()->getX() == point.first && (*it)->getLeft()->getY() == point.second && (*it)->getLeft()->getOther(*it)->getOther((*it)->getLeft())->getY() != (*it)->getLeft()->getY()) || ((*it)->getRight()->getX() == point.first && (*it)->getRight()->getY() == point.second && (*it)->getRight()->getOther(*it)->getOther((*it)->getRight())->getY() != (*it)->getLeft()->getY()))
                        k = -2;
                    else
                        k = -1;
                    Point* aux = new Point(point.first, point.second, k);
                    s1->addSteinerPoint(aux);
                }
            }
        }
        else if (s1->getLeft() == p && s2->getLeft() == p) {
            segments.insert(s1);
            segments.insert(s2);
            needErase = Plane::checkProjections(s1, s2, segments, true);
            for (vector<Segment*>::iterator it = needErase.begin(); it != needErase.end(); it++)
                segments.erase(*it);
            Segment* aux = Plane::projectTTB(p);
            if (aux->getLeft() != 0)
                segments.insert(aux);
        }
        else if (s1->getRight() == p && s2->getRight() == p) {
            needErase = Plane::checkProjections(s1, s2, segments, true);
            for (vector<Segment*>::iterator it = needErase.begin(); it != needErase.end(); it++)
                segments.erase(*it);
            Segment* aux = Plane::projectTTB(p);
            if (aux->getLeft() != 0)
                segments.insert(aux);
            segments.erase(s1);
            segments.erase(s2);
        }
        else {
            bool b;
            if(segments.find(s1) == segments.end()) {
                segments.insert(s1);
                b = true;
            }
            else {
                segments.insert(s2);
                b = false;
            }
            needErase = Plane::checkProjections(s1, s2, segments, true);
            for (vector<Segment*>::iterator it = needErase.begin(); it != needErase.end(); it++)
                segments.erase(*it);
            Segment* aux = Plane::projectTTB(p);
            if (aux->getLeft() != 0)
                segments.insert(aux);
            if (b)
                segments.erase(s2);
            else
                segments.erase(s1);
        }
        if (b1) {
            Point* aux = s1->getLeft();
            s1->setLeft(s1->getRight());
            s1->setRight(aux);
        }
        if (b2) {
            Point* aux = s2->getLeft();
            s2->setLeft(s2->getRight());
            s2->setRight(aux);
        }
    }
}

void Plane::LineSweepBTT(vector<Point*> points) {
    sort(points.rbegin(), points.rend(), sortBTT);
    Point* p;
    set<Segment*> segments;
    vector<Segment*> needErase;
    while(points.size() > 0) {
        p = points.back();
        points.pop_back();
        Segment* s1 = p->getSeg1();
        Segment* s2 = p->getSeg2();
        bool b1 = false, b2 = false;
        if (s1->case1()) {
            Point* aux = s1->getLeft();
            s1->setLeft(s1->getRight());
            s1->setRight(aux);
            b1 = true;
        }
        if (s2 != 0 && s2->case1()) {
            Point* aux = s2->getLeft();
            s2->setLeft(s2->getRight());
            s2->setRight(aux);
            b2 = true;
        }
        if (s2 == 0) {
            for(set<Segment*>::iterator it = segments.begin(); it != segments.end(); it++) {
                if ((*it)->getWeight() > s1->getWeight()) {
                    if ((*it)->getRight()->getY() != p->getY()) {
                        Point* steiner = Plane::createSteinerPoint(s1, *it);
                        Segment* s = new Segment(steiner, (*it)->getRight());
                        edges_.push_back(s);
                        (*it)->setRight(steiner);
                    }
                    (*it)->setWeight(s1->getWeight());
                }
            }
        }
        else if (s1->getRight() == p && s2->getRight() == p) {
            segments.insert(s1);
            segments.insert(s2);
            needErase = Plane::checkProjections(s1, s2, segments, false);
            for (vector<Segment*>::iterator it = needErase.begin(); it != needErase.end(); it++)
                segments.erase(*it);
            Segment* aux = Plane::projectBTT(p);
            if (aux->getLeft() != 0)
                segments.insert(aux);
        }
        else if (s1->getLeft() == p && s2->getLeft() == p) {
            needErase = Plane::checkProjections(s1, s2, segments, false);
            for (vector<Segment*>::iterator it = needErase.begin(); it != needErase.end(); it++)
                segments.erase(*it);
            Segment* aux = Plane::projectBTT(p);
            if (aux->getLeft() != 0)
                segments.insert(aux);
            segments.erase(s1);
            segments.erase(s2);
        }
        else {
            bool b;
            if(segments.find(s1) == segments.end()) {
                segments.insert(s1);
                b = true;
            }
            else {
                segments.insert(s2);
                b = false;
            }
            needErase = Plane::checkProjections(s1, s2, segments, false);
            for (vector<Segment*>::iterator it = needErase.begin(); it != needErase.end(); it++)
                segments.erase(*it);
            Segment* aux = Plane::projectBTT(p);
            if (aux->getLeft() != 0)
                segments.insert(aux);
            if (b)
                segments.erase(s2);
            else
                segments.erase(s1);
        }
        if (b1) {
            Point* aux = s1->getLeft();
            s1->setLeft(s1->getRight());
            s1->setRight(aux);
        }
        if (b2) {
            Point* aux = s2->getLeft();
            s2->setLeft(s2->getRight());
            s2->setRight(aux);
        }
    }
}

//Given two object edges and a map of segments, that includes projections, checks if there are any intersections between those projections and the edges, in order to create Steiner points
vector<Segment*> Plane::checkProjections(Segment* s1, Segment* s2, set<Segment*> segments, bool b) {
    vector<Segment*> needErase;
    for(set<Segment*>::iterator it = segments.begin(); it != segments.end(); it++) {
        if ((*it)->getWeight() != 0) {
            int ly1, ry1, ly2, ry2, ly, ry;
            ly = (*it)->getLeft()->getY();
            ry = (*it)->getRight()->getY();
            ly1 = s1->getLeft()->getY();
            ry1 = s1->getRight()->getY();
            ly2 = s2->getLeft()->getY();
            ry2 = s2->getRight()->getY();
            if ((ly > ly1 && ry < ry1) || (ly < ly1 && ry > ry1)) {
                Point* steiner = Plane::createSteinerPoint(s1, *it);
                Segment* s;
                if(b)
                    s = new Segment((*it)->getLeft(), steiner);
                else
                    s = new Segment(steiner, (*it)->getRight());
                edges_.push_back(s);
                needErase.push_back(*it);
            }
            else if ((ly > ly2 && ry < ry2) || (ly < ly2 && ry > ry2)) {
                Point* steiner = Plane::createSteinerPoint(s2, *it);
                Segment* s;
                if (b)
                    s = new Segment((*it)->getLeft(), steiner);
                else
                    s = new Segment(steiner, (*it)->getRight());
                edges_.push_back(s);
                needErase.push_back(*it);
            }
        }
    }
    return needErase;
}

pair<double, double> Plane::findIntersection(Segment* segment1, Segment* segment2) {
    double m1, m2, c1, c2, x, y, aux1, aux2;
    Point* right1 = segment1->getRight();
    Point* left1 = segment1->getLeft();
    Point* right2 = segment2->getRight();
    Point* left2 = segment2->getLeft();
    //cout << "First Segment: " << left1->getX() << " " << left1->getY() << " " << right1->getX() << " " << right1->getY() << endl;
    //cout << "Second Segment: " << left2->getX() << " " << left2->getY() << " " << right2->getX() << " " << right2->getY() << endl;
    aux1 = right1->getY() - left1->getY();
    aux2 = right1->getX() - left1->getX();
    m1 = aux1 / aux2;
    //cout << "m1: " << aux1 << " " << aux2 << " " << m2 << endl;
    aux1 = right2->getY() - left2->getY();
    aux2 = right2->getX() - left2->getX();
    m2 = aux1 / aux2;
    //cout << "m2: " << aux1 << " " << aux2 << " " << m2 << endl;
    c1 = left1->getY() - (m1 * left1->getX());
    c2 = left2->getY() - (m2 * left2->getX());
    x = (c2 - c1)/(m1 - m2);
    y = (m1 * x) + c1;
    cout << x << " " << y << endl;
    return pair<double,double>(x,y);
}

//Given two segments, an obstacle edge and a projection, creates a steiner point from their intersection and the corresponding edge to it
Point* Plane::createSteinerPoint(Segment* segment1, Segment* segment2) {
    pair<double, double> p = Plane::findIntersection(segment1, segment2);
    Point* steiner = new Point(p.first, p.second, segment1->getRight()-> getZ());
    nodes.push_back(steiner);
    segment1->addSteinerPoint(steiner);
    return steiner;
}

//Recursive function that creates median lines (that will be used to make type 1 Steiner points)
void Plane::createVerticalMedianLines(vector<Point*> points, int w) {
    if (points.size() > 1) {
        vector<Point*>::iterator middle = points.begin() + (points.size()/2);
        int x = (*middle)->getX();
        Point* p1 = new Point(x, INT_MAX);
        Point* p2 = new Point(x, INT_MIN);
        Segment* l = new Segment(p1, p2, w);
        medianLines.push_back(l);
        p2->setSeg1(l);
        vector<Point*> aux1(points.begin(), middle);
        vector<Point*> aux2(middle + 1, points.end());
        Plane::createVerticalMedianLines(aux1, w+1);
        Plane::createVerticalMedianLines(aux2, w+1);
    }
}

void Plane::createHorizontalMedianLines(vector<Point*> points, int w) {
    if (points.size() > 1) {
        vector<Point*>::iterator middle = points.begin() + points.size()/2;
        int y = (*middle)->getY();
        Point* p1 = new Point(INT_MAX, y);
        Point* p2 = new Point(INT_MIN, y);
        Segment* l = new Segment(p1, p2, w);
        medianLines.push_back(l);
        p2->setSeg1(l);
        vector<Point*> aux1(points.begin(), middle);
        vector<Point*> aux2(middle + 1, points.end());
        Plane::createHorizontalMedianLines(aux1, w+1);
        Plane::createHorizontalMedianLines(aux2, w+1);
    }
}

//auxiliary function to the LEFT TO RIGHT Line Sweep, it checks if point is inside or outside an obstacle so it can create a projection to the next obstacle and create Steiner Points, then creates that projection if possible
Segment* Plane::projectLTR(Point* p1) {
    Segment *s1 = p1->getSeg1(), *s2 = p1->getSeg2();
    Point *p0 = s1->getOther(p1), *p2 = s2->getOther(p1);
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
        Segment* aux = new Segment(0, 0);
        return aux;
    }
    else{
        Point* aux1 = new Point(INT_MAX, p1->getY());
        Segment* aux2 = new Segment(p1, aux1, INT_MAX);
        return aux2;
    }
}

//auxiliary function to the RIGHT TO LEFT Line Sweep, it checks if point is inside or outside an obstacle so it can create a projection to the next obstacle and create Steiner Points, then creates that projection if possible
Segment* Plane::projectRTL(Point* p1) {
    Segment *s1 = p1->getSeg1(), *s2 = p1->getSeg2();
    Point *p0 = s1->getOther(p1), *p2 = s2->getOther(p1);
    double lowestX = 0;
    double c0, b0, a0, angle0;
    double c2, b2, a2, angle2;
    Point* p_;
    //finding the highest X
    if(p0 -> getX() <= p1 -> getX() && p0 -> getX() <= p2 -> getX()){
        lowestX = p0 -> getX();
    }
    if(p1 -> getX() <= p0 -> getX() && p1 -> getX() <= p2 -> getX()){
        lowestX = p1 -> getX();
    }
    if(p2 -> getX() <= p0 -> getX() && p2 -> getX() <= p1 -> getX()){
        lowestX = p2 -> getX();
    }
    p_ = new Point(lowestX, p1->getY(), z);
    if(p1 -> getX() == p_ -> getX()){
        p_ -> setX(p_ -> getX()-1);
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
    if(angle0 == 0 || angle0 > angle2){
        Segment* aux = new Segment(0, 0);
        return aux;
    }
    else{
        Point* aux1 = new Point(INT_MIN, p1->getY());
        Segment* aux2 = new Segment(aux1, p1, INT_MAX);
        return aux2;
    }
}

//auxiliary function to the DOWN TO UP Line Sweep, it checks if point is inside or outside an obstacle so it can create a projection to the next obstacle and create Steiner Points, then creates that projection if possible
Segment* Plane::projectBTT(Point* p1) {
    Segment *s1 = p1->getSeg1(), *s2 = p1->getSeg2();
    Point *p0 = s1->getOther(p1), *p2 = s2->getOther(p1);
    double highestY = 0;
    double c0, b0, a0, angle0;
    double c2, b2, a2, angle2;
    Point* p_;
    //finding the highest Y
    if(p0 -> getY() >= p1 -> getY() && p0 -> getY() >= p2 -> getY()){
        highestY = p0 -> getY();
    }
    if(p1 -> getY() >= p0 -> getY() && p1 -> getY() >= p2 -> getY()){
        highestY = p1 -> getY();
    }
    if(p2 -> getY() >= p0 -> getY() && p2 -> getY() >= p1 -> getY()){
        highestY = p2 -> getY();
    }
    p_ = new Point(p1->getX(), highestY, z);
    if(p1 -> getY() == p_ -> getY()){
        p_ -> setY(p_ -> getY()+1);
    }
    
    //finding P0 angle
    c0 = findDistance(p0, p_);
    b0 = findDistance(p1, p_);
    a0 = findDistance(p0, p1);
    angle0 = findAngle(a0, b0, c0);
    
    if(p0 -> getX() < p1 -> getX()){
        angle0 = 2 * PI - angle0;
    }
    
    //finding P2 angle
    c2 = findDistance(p2, p_);
    b2 = findDistance(p1, p_);
    a2 = findDistance(p2, p1);
    angle2 = findAngle(a2, b2, c2);
    
    if(p2 -> getX() < p1 -> getX()){
        angle2 = 2 * PI - angle2;
    }
    
    //comparing angles
    if(angle2 == 0 || angle2 > angle0){
        Segment* aux = new Segment(0, 0);
        return aux;
    }
    else{
        Point* aux1 = new Point(p1->getX(), INT_MAX);
        Segment* aux2 = new Segment(p1, aux1, INT_MAX);
        return aux2;
    }
}

//auxiliary function to the UP TO DOWN Line Sweep, it checks if point is inside or outside an obstacle so it can create a projection to the next obstacle and create Steiner Points, then creates that projection if possible
Segment* Plane::projectTTB(Point* p1) {
    Segment *s1 = p1->getSeg1(), *s2 = p1->getSeg2();
    Point *p0 = s1->getOther(p1), *p2 = s2->getOther(p1);
    double lowestY = 0;
    double c0, b0, a0, angle0;
    double c2, b2, a2, angle2;
    Point* p_;
    //finding the lowest Y
    if(p0 -> getY() <= p1 -> getY() && p0 -> getY() <= p2 -> getY()){
        lowestY = p0 -> getY();
    }
    if(p1 -> getY() <= p0 -> getY() && p1 -> getY() <= p2 -> getY()){
        lowestY = p1 -> getY();
    }
    if(p2 -> getY() <= p0 -> getY() && p2 -> getY() <= p1 -> getY()){
        lowestY = p2 -> getY();
    }
    p_ = new Point(p1->getX(), lowestY, z);
    if(p1 -> getY() == p_ -> getY()){
        p_ -> setY(p_ -> getY()-1);
    }
    
    //finding P0 angle
    c0 = findDistance(p0, p_);
    b0 = findDistance(p1, p_);
    a0 = findDistance(p0, p1);
    angle0 = findAngle(a0, b0, c0);
    
    if(p0 -> getX() < p1 -> getX()){
        angle0 = 2 * PI - angle0;
    }
    
    //finding P2 angle
    c2 = findDistance(p2, p_);
    b2 = findDistance(p1, p_);
    a2 = findDistance(p2, p1);
    angle2 = findAngle(a2, b2, c2);
    
    if(p2 -> getX() < p1 -> getX()){
        angle2 = 2 * PI - angle2;
    }
    
    //comparing angles
    if(angle0 == 0 || angle0 > angle2){
        Segment* aux = new Segment(0, 0);
        return aux;
    }
    else{
        Point* aux1 = new Point(p1->getX(), INT_MIN);
        Segment* aux2 = new Segment(p1, aux1, INT_MAX);
        return aux2;
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

void Plane::createGraph(){
    
    typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, Point > Graph;
    typedef boost::graph_traits<Graph>::vertex_descriptor vertex_t;
    typedef boost::graph_traits<Graph>::edge_descriptor edge_t;
    
    Graph myGraph;
    for(vector<Segment*>::iterator it = edges_.begin(); it != edges_.end(); it++) {
        Point right = *(*it)->getRight();
        Point left = *(*it)->getLeft();
        vertex_t u = boost::add_vertex(right, myGraph);
        vertex_t v = boost::add_vertex(left, myGraph);
        boost::add_edge(u, v, myGraph);
    }
    
    fstream dot_file("graph.txt", fstream::out);
    boost::graph_traits < Graph >::edge_iterator ei, ei_end;
    for (boost::tie(ei, ei_end) = edges(myGraph); ei != ei_end; ++ei) {
        edge_t e = *ei;
        boost::graph_traits < Graph >::vertex_descriptor
        u = source(e, myGraph), v = target(e, myGraph);
        dot_file << "edge from: " << myGraph[u].getX() << " " << myGraph[u].getY() << " " << myGraph[u].getZ() << " to: " <<myGraph[v].getX() << " " << myGraph[v].getY() << " " << myGraph[v].getZ() << endl;
    }
    
    
    dot_file.close();
}
