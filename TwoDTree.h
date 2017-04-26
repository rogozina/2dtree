#ifndef TWODTREE_H
#define TWODTREE_H

#include"Types.h"
#include<vector>

class TwoDTree{
  class Node{
  public:
    Point p;
    Rect rect;
    Node* lb;
    Node* rt;
  Node():p(*(new Point(0,0))),rect(*(new Rect(0,0,1,1))),lb(nullptr),rt(nullptr) {};
  Node(Point p_, Rect rect_, Node* lb_, Node* rt_):p(p_),rect(rect_),lb(lb_),rt(rt_) {};
  };
  
  Node* _root;
  int _size;
  double _xmin,_ymin,_xmax,_ymax;

  void _fillrect(Node* cur, bool ver, Rect rect, std::vector<Point>& v);
  void _nst(Node* cur, bool ver, Point p, Point& pmin);
  
 public:
  TwoDTree(double xmin = 0,double ymin = 0, double xmax = 1,double ymax = 1);
  int size();
  bool contains(Point p);
  int insert(Point p);
  std::vector<Point> InRect(Rect rect);
  Point nearest(Point p);
};

#endif  
