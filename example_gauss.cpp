//examples require gnuplot-iostream lib
//compile:
//g++ -std=c++11 example_gauss.cpp TwoDTree.cpp TwoDTree.h Types.h Types.cpp -lboost_iostreams -lboost_system -lboost_filesystem

#include"TwoDTree.h"
#include <random>
#include "gnuplot-iostream.h"

using namespace std;

int main(){
  bool gaus = false;
  vector<pair<double,double>> A;
  int N = 2000;
  double xmin = 0;
  double xmax = 1;
  double ymin = 0;
  double ymax = 2;
  TwoDTree t(xmin, ymin, xmax, ymax);

  std::random_device rd; 
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> disx(xmin, xmax);
  std::uniform_real_distribution<> disy(ymin, ymax);
  
  double xmean = 0.5;
  double xsigma = 0.2;
  double ymean = 0.5;
  double ysigma = 1;
  std::default_random_engine genG;
  std::normal_distribution<double> disxG(xmean,xsigma);
  std::normal_distribution<double> disyG(ymean,ysigma);
  double x,y;
  for (int i = 0; i < N; ++i) {
    do {
      x = disxG(genG);
    } while ( x < xmin || x > xmax);
    do {
      y = disyG(genG);
    } while ( y < ymin || y > ymax);
    A.push_back(make_pair(x,y));
    t.insert({x,y});
  }
  
  Rect r = {0.1,0.2,0.3,0.3};
  std::vector<Point> v = t.InRect(r);
  vector<pair<double,double>> B;
  for(auto i : v){
    B.push_back(make_pair(i.x,i.y));
  }
  
  Point p = {disx(gen),disy(gen)};
  Point nst = t.nearest(p);
  
  vector<pair<double,double>> pos,nstp;
  pos.push_back(make_pair(p.x,p.y));
  nstp.push_back(make_pair(nst.x,nst.y));

  Gnuplot gp;


  gp << "set xrange ["<< xmin << ":" << xmax << "]\nset yrange ["<< ymin <<":" << ymax << "]\n";
  gp << "plot '-' with points title 'All points' pointtype 5  ps 0.5 lc rgb \"grey\", " <<
    " '-' with points title 'Selected',"<<
    " '-' with points title 'point'," <<
    " '-' with points title 'nearest'"<< std::endl;
  gp.send1d(A);
  gp.send1d(B);
  gp.send1d(pos);
  gp.send1d(nstp);
  
}
