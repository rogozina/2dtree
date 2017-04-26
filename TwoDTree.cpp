#include"TwoDTree.h"

TwoDTree::TwoDTree(double xmin, double ymin, double xmax, double ymax) : _size(0),_root(nullptr), _xmin(xmin), _ymin(ymin), _xmax(xmax), _ymax(ymax) {};

int TwoDTree::size() {return _size;}

bool TwoDTree::contains(Point p){
    if(_size == 0) return false;
    Node* cur = _root;
    bool ver = true;
    while(cur!=nullptr){
      if (equals(cur->p,p)) return true;
      if (ver && cur->p.x > p.x || !ver && cur->p.y > p.y){
	cur = cur->lb;
      } else {
	cur = cur->rt;
      }
      ver = !ver;
    }
    return false;
}
  
int TwoDTree::insert(Point p){
    Node* cur = _root;
    bool ver = true;
    assert(contain({_xmin,_ymin,_xmax,_ymax},p));
    if(_size == 0){
      _size = 1;
      _root = new Node();
      _root->p = p;
      _root->rect = Rect(_xmin,_ymin,_xmax,_ymax);
    } else if (!contains(p)){
      while(true){
	if (ver && cur->p.x > p.x || !ver && cur->p.y > p.y){
	  if (cur->lb != nullptr){
	    cur = cur->lb;
	  } else {
	    Node* x = new Node();
	    x->p = p;
	    if (ver){
	      x->rect = *(new Rect(cur->rect.xmin,cur->rect.ymin,cur->p.x,cur->rect.ymax));
	    } else {
	      x->rect = *(new Rect(cur->rect.xmin,cur->rect.ymin,cur->rect.xmax,cur->p.y));
	    }
	    cur->lb = x;
	    break;
	  }
	} else {
	  if (cur->rt != nullptr){
	    cur = cur->rt;
	  } else {
	    Node* x = new Node();
	    x->p = p;
	    if (ver){
	      x->rect = *(new Rect(cur->p.x,cur->rect.ymin,cur->rect.xmax,cur->rect.ymax));
	    } else {
	      x->rect = *(new Rect(cur->rect.xmin,cur->p.y,cur->rect.xmax,cur->rect.ymax));
	    }
	    cur->rt = x;
	    break;
	  }
	}
	ver = !ver;
      }
      ++_size;
    }
    return 0;
}

void TwoDTree::_fillrect(Node* cur, bool ver, Rect rect, std::vector<Point>& v){
    if (contain(rect,cur->p)) v.push_back(cur->p);
    if (cur->lb != nullptr && intersect(rect,cur->lb->rect)) _fillrect(cur->lb, !ver, rect,v);
    if (cur->rt != nullptr && intersect(rect,cur->rt->rect)) _fillrect(cur->rt, !ver, rect,v);
}

std::vector<Point> TwoDTree::InRect(Rect rect){
    std::vector<Point> res;
    Node* cur = _root;
    _fillrect(cur, true, rect, res);
    return res;
}

void TwoDTree::_nst(Node* cur, bool ver, Point p, Point& pmin){
  if (equals(cur->p,p)) {
           pmin = cur->p;
           return;
  }
  double dmin = distanceSq(p,pmin);
  double d = distanceSq(p,cur->p);
  if (d<dmin){
    dmin = d;
    pmin = cur->p;
  }
  if (cur->lb == nullptr && cur->rt == nullptr) return; 
  if (cur->rt != nullptr && dmin > distanceSq(cur->rt->rect,p))
      _nst(cur->rt,!ver,p,pmin);
  if (cur->lb != nullptr && dmin > distanceSq(cur->lb->rect,p))
      _nst(cur->lb,!ver,p,pmin);
}
  
Point TwoDTree::nearest(Point p){
  assert(_size != 0);
  Point pmin = {_root->p.x,_root->p.y};
  _nst(_root, true, p, pmin);
  return pmin;
}
  
