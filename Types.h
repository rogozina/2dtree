#ifndef TYPES_H
#define TYPES_H
#include<cassert>

class Point{
public:
  double x,y;
  Point(double x_, double y_):x(x_),y(y_){}
};

class Rect{
public:
  double xmin,ymin,xmax,ymax;
  Rect(double xmin_,double ymin_,double xmax_,double ymax_): xmin(xmin_),ymin(ymin_),xmax(xmax_),ymax(ymax_) {
    assert(xmin_ <= xmax_ && ymin_ <= ymax_);
  }
};

bool equals(Point p1, Point p2);

bool contain(Rect rect, Point p);

bool intersect(Rect r1, Rect r2);

double distanceSq(Point p1, Point p2);

double distanceSq(Rect r, Point p);

#endif
