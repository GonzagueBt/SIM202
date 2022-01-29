#include <iostream>
#include <vector>
#include <limits>
#include <list>
#include <cmath>
using namespace std;

#define square(a)  (a)*(a)


class Point
{public:
  double x;   //abcisse
  double y;   //ordonnée
  Point(double x0=0,double y0=0):x(x0),y(y0){} //constructeur commun
};

class Arc{
    public:
        Point a,b;
        double poid;
        Arc(Point x=0, Point y=0, double z=0): a(x), b(y), poid(z){}
};


class Segment : public Arc{
    public:
        Segment(Point x, Point y);
};

Segment::Segment(Point x, Point y){
    a=x;
    b=y;
    poid = sqrt(square(a.x - b.x) + square(a.y - b.y));
}

vector<double> matrice_couts(list<Segment> l)
{
    int n = l.size();
    vector<double> c(n*n,INT_MAX);

    list<Segment>::iterator itl = l.begin();;
    int a = 1;
    int b = 0;

    while(b<(n*n)+1){
        c[b] = 0; //sur la diagonale, coefficients nuls
        b = b +n+1;
    }

    while((itl!=l.end()) && (a<(n-1)*(n+1)+2)){
        c[a] = itl->poid;
        itl++;
        a = a + n+1;;
    }
    itl--;
    c[n*(n-1)]=itl->poid;
    return c;
}


int main()
{
    list<Segment> l;

    Point P0(0,0);
    Point P1(-2,0);
    Point P2(-4,1);
    Point P3(-1,5);
    Point P4(2,1);
    Point P5(3,0);

    Segment S0(P0,P1);
    Segment S1(P1,P2);
    Segment S2(P2 ,P3);
    Segment S3(P3 ,P4);
    Segment S4(P4 ,P5);
    Segment S5(P5 ,P0);

    // Les sommets doivent être rentrés dans le sens trigonométrique + pas de poids infinis

    l.push_back(S0);
    l.push_back(S1);
    l.push_back(S2);
    l.push_back(S3);
    l.push_back(S4);
    l.push_back(S5);
    vector<double> c = matrice_couts(l);

    for(int i=0;i<6;i++){
        for(int j=0; j<6; j++){
            cout<<c[i*6+j]<<"  ";
        }
        cout<<"\n"<<endl;
    }

    return 0;
}
