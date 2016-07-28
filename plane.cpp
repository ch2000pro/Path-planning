/*----------------------------------------------------------------------*/
/*  plane.cpp                                                           */
/*  Plane representing a given Z coordinate                             */
/*  Fernanda Isabel, Gianluca Cagliari, Laura Vieira, Leonardo Castilho */
/*  Start: July 5, 2016                                                 */
/*----------------------------------------------------------------------*/

#include <vector>
#include <iterator>
#include "plane.h"
#include "segment.h"
#include <cmath>
#include <typeinfo>
#define PI 3.14159265

//constructor, it receives a Z coordinate
Plane::Plane(double z_){
    z = z_;
}

//destructor
Plane::~Plane(){
}

//returns the private vector of segments 'edges_'
vector<Segment*> Plane::getEdges(){
    return edges_;
}

//returns the private vector of nodes of the plane
vector<Point*> Plane::getNodes(){
    return nodes;
}

struct sortLTR {
    bool operator() (Point* a, Point* b) { return (((abs(a->getX() - b->getX()) > abs(min(a->getX(), b->getX())) * numeric_limits<double>::epsilon()) && (a->getX() < b->getX())) || ((abs(a->getX() - b->getX()) < abs(min(a->getX(), b->getX())) * numeric_limits<double>::epsilon()) && (a->getY() > b->getY()))); }
};

struct sortRTL {
    bool operator() (Point* a, Point* b) { return (a->getX() > b->getX() || (a->getX() == b->getX() && a->getY() > b->getY())); }
};

struct sortTTB {
    bool operator() (Point* a, Point* b) { return (a->getY() > b->getY() || (a->getY() == b->getY() && a->getX() > b->getX())); }
};

struct sortBTT {
    bool operator() (Point* a, Point* b) { return (a->getY() < b->getY() || (a->getY() == b->getY() && a->getX() > b->getX())); }
};

//Function that runs through all the obstacles to check if they are obstacles in that plane
//For each one found, add that obstacle to the 2D Plane
void Plane::findObstaclesInPlane(vector<Obstacle*> obstacles){
    vector<Obstacle*>::iterator it;
    Obstacle* obstacle;
    for (it = obstacles.begin() ; it != obstacles.end(); ++it) {
        obstacle = *it;
        if(obstacle-> get_height() > z){
            cout << obstacle-> get_height() << endl;
            addObstacle(obstacle -> get_vertices(z));
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

void Plane::lineSweep(Point* source, Point* sink) {
    vector<Point*> points1 = endpoints, points2 = endpoints;
    if (source != 0) {
        points1.push_back(source);
        points2.push_back(source);
        nodes.push_back(source);
    }
    if (sink != 0) {
        points1.push_back(sink);
        points2.push_back(sink);
        nodes.push_back(sink);
    }
    for(vector<Point*>::iterator it = points2.begin(); it != points2.end(); ++it)
        cout << (*it)->getX() << " " << (*it)->getY() << endl;
    sort(points1.begin(), points1.end(), sortLTR());
    Plane::createVerticalMedianLines(points1, 1, source, sink);
    sort(points2.begin(), points2.end(), sortTTB());
    Plane::createHorizontalMedianLines(points2, 1, source, sink);
    for(vector<Segment*>::iterator it = medianLines.begin(); it != medianLines.end(); it++) {
        if((*it)->getRight()->getY() == -2147483648) {
            //cout << (*it)->getRight()->getX() << endl;
            points1.push_back((*it)->getRight());
        }
        else {
            points2.push_back((*it)->getRight());
            //cout << (*it)->getRight()->getY() << endl;
        }
    }
    vector<Point*>::iterator prev = points1.begin();
    for(vector<Point*>::iterator it = points1.begin()+1; it != points1.end(); ++it) {
        if ((*prev)->getX() == (*it)->getX() && (*prev)->getSeg1() != 0 && (*it)->getSeg1() != 0) {
            map<double,Segment*>::iterator s = verticalMedianLines.find((*it)->getX());
            if (s != verticalMedianLines.end()) {
                (*prev)->setZ(-3);
                (*it)->setZ(-3);
                s->second->addSteinerPoint(*prev);
                s->second->addSteinerPoint(*it);
                ++it;
                if (it == points1.end())
                    --it;
            }
        }
        prev = it;
    }
    prev = points2.begin();
    for(vector<Point*>::iterator it = points2.begin()+1; it != points2.end(); ++it) {
        if ((*prev)->getY() == (*it)->getY() && (*prev)->getSeg1() != 0 && (*it)->getSeg1() != 0) {
            map<double,Segment*>::iterator s = horizontalMedianLines.find((*it)->getY());
            if (s != horizontalMedianLines.end()) {
                (*prev)->setZ(-3);
                (*it)->setZ(-3);
                s->second->addSteinerPoint(*prev);
                s->second->addSteinerPoint(*it);
                ++it;
                if (it == points2.end())
                    --it;
            }
        }
        prev = it;
    }
    for (vector<Segment*>::iterator it = obstacleSegments.begin(); it != obstacleSegments.end(); ++it)
        (*it)->zeroSteinerPoints();
        
    Plane::LineSweepLTR(points1);
    Plane::LineSweepRTL(points1);
    Plane::LineSweepTTB(points2);
    Plane::LineSweepBTT(points2);
    for(vector<Segment*>::iterator l = medianLines.begin(); l != medianLines.end(); ++l) {
        vector<Point*> steiners = (*l)->getSteinerPoints();
        sort(steiners.begin(), steiners.end(), sortLTR());
        Point* prev = 0;
        for(vector<Point*>::iterator p = steiners.begin(); p != steiners.end(); ++p) {
            //if ((*l)->getLeft()->getX() == 76)
                //cout << (*p)->getX() << " " << (*p)->getY() << " " << (*p)->getZ() << endl;
            if((*p)->getZ() < 0) {
                if ((*p)->getZ() == -2 || (*p)->getZ() == -3) {
                    if (prev != 0) {
                        if (prev->getX() != (*p)->getX() || prev->getY() != (*p)->getY()) {
                            Segment* s = new Segment(prev, *p);
                            edges_.push_back(s);
                        }
                    }
                    if ((*p)->getZ() == -2)
                        prev = *p;
                    else {
                        p++;
                        if (p != steiners.end())
                            prev = *p;
                        else
                            p--;
                    }
                }
                else
                    prev = 0;
            }
            else {
                if (prev != 0) {
                    if (prev->getX() != (*p)->getX() || prev->getY() != (*p)->getY()) {
                        Segment* s = new Segment(prev, *p);
                        edges_.push_back(s);
                    }
                }
                prev = *p;
            }
        }
    }
    for(vector<Segment*>::iterator l = obstacleSegments.begin(); l != obstacleSegments.end(); l++) {
        vector<Point*> steiners = (*l)->getSteinerPoints();
        sort(steiners.begin(), steiners.end(), sortLTR());
        Point *prev = (*l)->getLeft();
        for(vector<Point*>::iterator p = steiners.begin(); p != steiners.end(); p++) {
            Segment* s = new Segment(prev, *p);
            edges_.push_back(s);
            prev = *p;
        }
        Segment* s = new Segment(prev, (*l)->getRight());
        edges_.push_back(s);
    }
    for (vector<Segment*>::iterator it = edges_.begin(); it != edges_.end(); ++it) {
        double x1 = (*it)->getLeft()->getX(), y1 = (*it)->getLeft()->getY(), x2 = (*it)->getRight()->getX(), y2 = (*it)->getRight()->getY(), w;
        w = y2 - y1;
        if (abs(w - 0) > 0.000000001 && w < 0)
            w *= -1;
        w += (x2 - x1);
        if (abs(w - 0) < 0.000000001)
            w = 0;
        (*it)->setWeight(w);
        if (w < 0)
            cout << w << endl;
    }
    for (vector<Point*>::iterator it = nodes.begin(); it != nodes.end(); ++it)
        (*it)->setZ(z);
    /*for (vector<Segment*>::iterator it = edges_.begin(); it!= edges_.end(); ++it) {
        if((*it)->getLeft()->getZ() != (*it)->getRight()->getZ())
            cout << "aqui " << z << " / " << (*it)->getLeft()->getX() << " " << (*it)->getLeft()->getY() << " " << (*it)->getRight()->getX() << " " << (*it)->getRight()->getY() << endl;
        
    }*/
    //cout << "total edges: " << edges_.size() << endl;
    if (z == 5) {
        for (vector<Segment*>::iterator it = edges_.begin(); it!= edges_.end(); ++it)
            cout << "from: " << (*it)->getLeft()->getX() << " " << (*it)->getLeft()->getY() << " " << (*it)->getLeft()->getZ() << " to: " << (*it)->getRight()->getX() << " " << (*it)->getRight()->getY() << " " << (*it)->getRight()->getZ() << endl;
    }
}

//lineSweep will create a graph representing the plane, in order to find the shortest path on it
void Plane::LineSweepLTR(vector<Point*> points) {
    sort(points.rbegin(), points.rend(), sortLTR());
    Point* p;
    set<Segment*> segments;
    vector<Segment*> needErase;
    while(points.size() > 0) {
        p = points.back();
        points.pop_back();
        Segment* s1 = p->getSeg1();
        Segment* s2 = p->getSeg2();
        if (s1 == 0 && s2 == 0) {
            Point* aux = new Point(INT_MAX, p->getY());
            Segment* s = new Segment(p, aux, INT_MAX);
            segments.insert(s);
        }
        else if (s2 == 0) {
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
                    if (abs((*it)->getLeft()->getX() - point.first) < 0.000000001 && abs((*it)->getLeft()->getY() - point.second) < 0.0000000001) {
                        if ((*it)->getLeft()->getOther(*it)->getOther((*it)->getLeft())->getX() != (*it)->getLeft()->getX()) {
                            k = -2;
                            (*it)->getLeft()->setZ(k);
                            s1->addSteinerPoint((*it)->getLeft());
                        }
                        else
                            k = 0;
                    }
                    else {
                        k = -1;
                        Point* aux = new Point(point.first, point.second, k);
                        s1->addSteinerPoint(aux);
                    }
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
    sort(points.rbegin(), points.rend(), sortRTL());
    Point* p;
    set<Segment*> segments;
    vector<Segment*> needErase;
    while(points.size() > 0) {
        p = points.back();
        points.pop_back();
        Segment* s1 = p->getSeg1();
        Segment* s2 = p->getSeg2();
        if (s1 == 0 && s2 == 0) {
            Point* aux = new Point(INT_MIN, p->getY());
            Segment* s = new Segment(aux, p, INT_MAX);
            segments.insert(s);
        }
        else if (s2 == 0) {
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
    sort(points.rbegin(), points.rend(), sortTTB());
    Point* p;
    set<Segment*> segments;
    vector<Segment*> needErase;
    while(points.size() > 0) {
        p = points.back();
        points.pop_back();
        Segment* s1 = p->getSeg1();
        Segment* s2 = p->getSeg2();
        bool b1 = false, b2 = false;
        if (s1 != 0 && s1->case1()) {
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
        if (s1 == 0 && s2 == 0) {
            Point* aux = new Point(p->getX(), INT_MIN);
            Segment* s = new Segment(p, aux, INT_MAX);
            segments.insert(s);
        }
        else if (s2 == 0) {
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
                    if (abs((*it)->getLeft()->getX() - point.first) < 0.0000001 && abs((*it)->getLeft()->getY() - point.second) < 0.00000001) {
                        if ((*it)->getLeft()->getOther(*it)->getOther((*it)->getLeft())->getY() != (*it)->getLeft()->getY()) {
                            k = -2;
                            (*it)->getLeft()->setZ(k);
                            s1->addSteinerPoint((*it)->getLeft());
                        }
                        else
                            k = 0;
                    }
                    else if (abs((*it)->getRight()->getX() - point.first) < 0.0000001 && abs((*it)->getRight()->getY() - point.second) < 0.00000001) {
                        if ((*it)->getRight()->getOther(*it)->getOther((*it)->getRight())->getY() != (*it)->getLeft()->getY()) {
                            k = -2;
                            (*it)->getRight()->setZ(k);
                            s1->addSteinerPoint((*it)->getRight());
                        }
                        else
                            k = 0;
                    }
                    else {
                        k = -1;
                        Point* aux = new Point(point.first, point.second, k);
                        s1->addSteinerPoint(aux);
                    }
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
    sort(points.rbegin(), points.rend(), sortBTT());
    Point* p;
    set<Segment*> segments;
    vector<Segment*> needErase;
    while(points.size() > 0) {
        p = points.back();
        points.pop_back();
        Segment* s1 = p->getSeg1();
        Segment* s2 = p->getSeg2();
        bool b1 = false, b2 = false;
        if (s1 != 0 && s1->case1()) {
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
        if (s1 == 0 && s2 == 0) {
            Point* aux = new Point(p->getX(), INT_MAX);
            Segment* s = new Segment(aux, p, INT_MAX);
            segments.insert(s);
        }
        else if (s2 == 0) {
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
            double lx1, ly1, rx1, ry1, lx2, ly2, rx2, ry2, lx, ly, rx, ry;
            lx = (*it)->getLeft()->getX();
            ly = (*it)->getLeft()->getY();
            rx = (*it)->getRight()->getX();
            ry = (*it)->getRight()->getY();
            lx1 = s1->getLeft()->getX();
            ly1 = s1->getLeft()->getY();
            rx1 = s1->getRight()->getX();
            ry1 = s1->getRight()->getY();
            lx2 = s2->getLeft()->getX();
            ly2 = s2->getLeft()->getY();
            rx2 = s2->getRight()->getX();
            ry2 = s2->getRight()->getY();
            if (((lx1-lx)*(ry-ly) - (ly1-ly)*(rx-lx)) * ((rx1-lx)*(ry-ly) - (ry1-ly)*(rx-lx)) < 0 && ((lx-lx1)*(ry1-ly1) - (ly-ly1)*(rx1-lx1)) * ((rx-lx1)*(ry1-ly1) - (ry-ly1)*(rx1-lx1)) < 0) {
                Point* steiner = Plane::createSteinerPoint(s1, *it);
                Segment* s;
                if(b)
                    s = new Segment((*it)->getLeft(), steiner);
                else
                    s = new Segment(steiner, (*it)->getRight());
                edges_.push_back(s);
                needErase.push_back(*it);
            }
            else if (((lx2-lx)*(ry-ly) - (ly2-ly)*(rx-lx)) * ((rx2-lx)*(ry-ly) - (ry2-ly)*(rx-lx)) < 0 && ((lx-lx2)*(ry2-ly2) - (ly-ly2)*(rx2-lx2)) * ((rx-lx2)*(ry2-ly2) - (ry-ly2)*(rx2-lx2)) < 0) {
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
    double x, y, aux1, aux2, x1, y1, x2, y2, x3, y3, x4, y4;
    x1 = segment1->getLeft()->getX();
    y1 = segment1->getLeft()->getY();
    x2 = segment1->getRight()->getX();
    y2 = segment1->getRight()->getY();
    x3 = segment2->getLeft()->getX();
    y3 = segment2->getLeft()->getY();
    x4 = segment2->getRight()->getX();
    y4 = segment2->getRight()->getY();
    aux1 = ((x1*y2 - y1*x2) * (x3 - x4)) - ((x1 - x2) * (x3*y4 - y3*x4));
    aux2 = ((x1 - x2) * (y3 - y4)) - ((y1 - y2) * (x3 - x4));
    x = aux1 / aux2;
    aux1 = ((x1*y2 - y1*x2) * (y3 - y4)) - ((y1 - y2) * (x3*y4 - y3*x4));
    y = aux1 / aux2;
    if (x == -0)
        x = 0;
    if (y == -0)
        y = 0;
    return pair<double,double>(x,y);
}

//Given two segments, an obstacle edge and a projection, creates a steiner point from their intersection and the corresponding edge to it
Point* Plane::createSteinerPoint(Segment* segment1, Segment* segment2) {
    pair<double, double> p = Plane::findIntersection(segment1, segment2);
    Point* steiner = new Point(p.first, p.second);
    nodes.push_back(steiner);
    segment1->addSteinerPoint(steiner);
    return steiner;
}

//Recursive function that creates median lines (that will be used to make type 1 Steiner points)
void Plane::createVerticalMedianLines(vector<Point*> points, int w, Point* source, Point* sink) {
    if (points.size() > 1) {
        vector<Point*>::iterator middle = points.begin() + (points.size()/2);
        double x = (*middle)->getX();
        if (verticalMedianLines.count(x) == 0) {
            if ((*middle)->getSeg1() != 0 && (*middle)->getSeg2() != 0) {
                if ((*middle)->getSeg1()->getOther(*middle)->getX() < x && (*middle)->getSeg2()->getOther(*middle)->getX() < x)
                    x += 0.1;
                else if ((*middle)->getSeg1()->getOther(*middle)->getX() > x && (*middle)->getSeg2()->getOther(*middle)->getX() > x)
                    x -= 0.1;
            }
            Point* p1 = new Point(x, INT_MAX);
            Point* p2 = new Point(x, INT_MIN);
            Segment* l = new Segment(p1, p2, w);
            verticalMedianLines.insert(pair<double, Segment*>(x, l));
            if ((*middle)->getSeg1() == 0 && (*middle)->getSeg2() == 0 ) {
                if(source != 0 && (*middle)->getX() == source->getX() && (*middle)->getY() == source->getY())
                    l->addSteinerPoint(source);
                else
                    l->addSteinerPoint(sink);
            }
            medianLines.push_back(l);
            p2->setSeg1(l);
            vector<Point*> aux1(points.begin(), middle);
            vector<Point*> aux2(middle + 1, points.end());
            Plane::createVerticalMedianLines(aux1, w+1, source, sink);
            Plane::createVerticalMedianLines(aux2, w+1, source, sink);
        }
    }
}

void Plane::createHorizontalMedianLines(vector<Point*> points, int w, Point* source, Point* sink) {
    if (points.size() > 1) {
        vector<Point*>::iterator middle = points.begin() + points.size()/2;
        double y = (*middle)->getY();
        if (horizontalMedianLines.count(y) == 0) {
            if ((*middle)->getSeg1() != 0 && (*middle)->getSeg2() != 0) {
                if ((*middle)->getSeg1()->getOther(*middle)->getY() > y && (*middle)->getSeg2()->getOther(*middle)->getY() > y)
                    y -= 0.1;
                else if ((*middle)->getSeg1()->getOther(*middle)->getY() < y && (*middle)->getSeg2()->getOther(*middle)->getY() < y)
                    y += 0.1;
            }
            Point* p1 = new Point(INT_MAX, y);
            Point* p2 = new Point(INT_MIN, y);
            Segment* l = new Segment(p1, p2, w);
            horizontalMedianLines.insert(pair<double,Segment*>(y, l));
            if ((*middle)->getSeg1() == 0 && (*middle)->getSeg2() == 0) {
                if(source != 0 && (*middle)->getX() == source->getX() && (*middle)->getY() == source->getY())
                    l->addSteinerPoint(source);
                else
                    l->addSteinerPoint(sink);
            }
            medianLines.push_back(l);
            p2->setSeg1(l);
            vector<Point*> aux1(points.begin(), middle);
            vector<Point*> aux2(middle + 1, points.end());
            Plane::createHorizontalMedianLines(aux1, w+1, source, sink);
            Plane::createHorizontalMedianLines(aux2, w+1, source, sink);
        }
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

//auxiliary function to the DOWN TO UP Line ], it checks if point is inside or outside an obstacle so it can create a projection to the next obstacle and create Steiner Points, then creates that projection if possible
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
        Segment* aux2 = new Segment(aux1, p1, INT_MAX);
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

//returns if a given point is in that plane or not
//it is an auxiliary function to be used in the program Main() during the source and target projections to the graph
bool Plane::nodeExistsInPlane(Point* p){
     for(vector<Point*>::iterator it = nodes.begin(); it != nodes.end(); it++) {
         Point* v = *it;
         if(abs(p->getX() - v->getX()) < 0.0000000001 && abs(p->getY() - v->getY()) < 0.0000000001){
             return true;
         }
     }
    return false;
}
