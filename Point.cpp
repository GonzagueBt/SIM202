#include "Point.hpp"

Point operator+(const Point & P,const Point &Q)
{Point R(P); return R+=Q;}
Point operator-(const Point & P,const Point &Q)
{Point R(P); return R-=Q;}
Point operator*(const Point & P,double a)
{Point R(P); return R*=a;}
Point operator* (double a,const Point & P)
{Point R(P); return R*=a;}
Point operator/ (const Point & P,double a)
{Point R(P); return R/=a;}
bool operator ==(const Point & P,const Point &Q)
{return (P.x==Q.x) && (P.y==Q.y);}
bool operator !=(const Point & P,const Point &Q)
{return !(P==Q);}

bool operator <(const Point & P,const Point &Q)
{if(P.x<Q.x) return true;
 if(P.x>Q.x) return false;
 if(P.y<Q.y) return true;
 return false;}

ostream & operator <<(ostream & os, const Point &P)
{os<<"("<<P.x<<","<<P.y<<")"; return os;}

Point operator|(const Point &u, const Point &v)
{
    Point res;
    res.x = v.x - u.x;
    res.y = v.y - u.y;
    return res;
}

vector<Point> concateVectorPoints(vector<Point> a, vector<Point> b){
    vector<Point> pts;
    pts.reserve(a.size()+b.size());
    for(int i=0; i< (int) a.size(); i++){
        pts.push_back(a[i]);
    }
    for(int i=0; i< (int) b.size(); i++){
        if(!isIn(b[i], pts)) pts.push_back(b[i]);
    }
    return pts;
}

int isIn(Point a, Point * memory, int nb){
    for(int i=0; i<nb; i++){
        if(a==memory[i]) return i;
    }
    return -1;
}

bool isIn(Point a, vector<Point> pts){
    for(int i=0; i< (int) pts.size(); i++){
        if(a==pts[i])return true; 
    }
    return false;
}

void printPoints(list<Point> chemin){
    list<Point>::iterator its = chemin.begin();
    for(; its!= chemin.end(); its++){
        cout<<"("<<its->x<<","<<its->y<<") ";
    }
    cout<<endl;
}

void printSommet(vector<Point> sommet){
    cout<<"Liste des sommets du graphe : "<<endl;
    for(int i=0; i< (int)sommet.size(); i++){
        cout<<"("<<sommet[i].x<<","<<sommet[i].y<<")  ";
    }
    cout<<endl;
}
