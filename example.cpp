//examples require gnuplot-iostream lib
//compile:
//g++ -std=c++11 example.cpp TwoDTree.cpp TwoDTree.h Types.h Types.cpp -lboost_iostreams -lboost_system -lboost_filesystem

#include"TwoDTree.h"
#include<iostream>
#include <random>
#include "gnuplot-iostream.h"

using namespace std;

int main(){
  vector<pair<double,double>> A;
  TwoDTree t;
  int N = 500;

  std::random_device rd; 
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(0, 1);

  for (int i = 0; i < N; ++i) {
    Point p = {dis(gen),dis(gen)};
    A.push_back(make_pair(p.x,p.y));
    t.insert(p);
  }
    
  Rect r = {0.1,0.2,0.3,0.3};
  std::vector<Point> v = t.InRect(r);
  vector<pair<double,double>> B;
  for(auto i : v){
    B.push_back(make_pair(i.x,i.y));
  }
  
  Point p = {dis(gen),dis(gen)};
  Point nst = t.nearest(p);
  
  vector<pair<double,double>> pos,nstp;
  pos.push_back(make_pair(p.x,p.y));
  nstp.push_back(make_pair(nst.x,nst.y));

  Gnuplot gp;

  gp << "set xrange [0:1]\nset yrange [0:1]\n";
  gp << "plot '-' with points title 'All points' pointtype 5  ps 0.5 lc rgb \"grey\", " <<
    " '-' with points title 'Selected',"<<
    " '-' with points title 'point'," <<
    " '-' with points title 'nearest'"<< std::endl;
  gp.send1d(A);
  gp.send1d(B);
  gp.send1d(pos);
  gp.send1d(nstp);
  
}
