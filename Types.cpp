#include"Types.h"

bool equals(Point p1, Point p2){
  return (p1.x == p2.x && p1.y == p2.y);
}

bool contain(Rect rect, Point p){
  return (p.x >= rect.xmin && p.x <= rect.xmax && p.y >= rect.ymin && p.y <= rect.ymax);
}

bool intersect(Rect r1, Rect r2){
  return (r1.xmin <= r2.xmax && r1.xmax >= r2.xmin && r1.ymin <= r2.ymax && r1.ymax >= r2.ymin);
}

double distanceSq(Point p1, Point p2){
  return (p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y);
}

double distanceSq(Rect r, Point p){
  //return 0 if r contains p
  double distanceX = 0;
  double distanceY = 0;
  if (p.x > r.xmax) distanceX = r.xmax-p.x;
  if (p.x < r.xmin) distanceX = p.x-r.xmin;
  if (p.y > r.ymax) distanceX = r.ymax-p.y;
  if (p.y < r.ymin) distanceX = p.y-r.ymin;  
  return distanceX*distanceX+distanceY*distanceY;
}
