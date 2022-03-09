#include "Arc.hpp"


ostream&operator<<(ostream& os, const Arc &A)
{
os<<"("<<A.a<<";"<<A.b<<")"<<endl;;
return os;
}

Segment::Segment(Point x, Point y){
    a=x;
    b=y;
    poid = sqrt(square(x.x - y.x) + square(x.y - y.y));
}

bool Segment::operator==(const Segment A){
    if((a==A.a && b==A.b) || (a==A.b && b==A.a)) return true;
    return false;
}


Point Intersction2Arcs(Arc A, Arc B){
    // segment A(x,y) a1x + b1y = c1
    double a1 = A.b.y - A.a.y;
    double b1 = A.a.x - A.b.x;
    double c1 = a1*(A.a.x) + b1*(A.a.y);
    // segment B(x,y) a1x + b1y = c1
    double a2 = B.b.y - B.a.y;
    double b2 = B.a.x - B.b.x;
    double c2 = a2*(B.a.x) + b2*(B.a.y);
  
    double determinant = a1*b2 - a2*b1;
  
    if (determinant == 0)  exit(-1);
    double x = (b2*c1 - b1*c2)/determinant;
    double y = (a1*c2 - a2*c1)/determinant;
    return Point(x,y);
}


bool isIn(Segment A, list<Segment> segs){
    auto it = segs.begin();
    for(; it!=segs.end(); it++){
        if(A ==(*it))return true; 
    }
    return false;
}

list<Segment> deleteSegCommun(list<Segment> liste){
    if(liste.size()==2) return liste;
    list<Segment>::iterator its = liste.begin();
    list<Segment>::iterator its2 = liste.begin();
    its2++;
    list<Segment>::iterator memory;
    while(its!= liste.end()){
        bool isInvalide = false;
        while(its2!= liste.end()){
            if((its->a==its2->a || its->a==its2->b) && (its->b== its2->a || its->b==its2->b)){
                list<Segment>::iterator mem = its2;
                its2++;
                liste.erase(mem);
                isInvalide = true;
                memory = its;
                continue;
            }
            else its2++;
        }
        if(isInvalide){ 
            its++;
            liste.erase(memory);
        }
        else its++;
    }
    return liste;
}

int sommetsNonUsed(vector<Point> pts, list<Segment> segs){
    int cpt=0;
    for(int i=0; i< (int) pts.size(); i++){
        auto it= segs.begin();
        bool isUsed = false;
        for(; it!= segs.end(); it++){
            if(it->a==pts[i] || it->b==pts[i]){
                isUsed=true;
                break;
            }
        }
        if(!isUsed) cpt++;
    }
    return cpt;
}

void printSegments(list<Segment> liste){
    list<Segment>::iterator its = liste.begin();
    for(; its!= liste.end(); its++){
        cout<<"("<<its->a<<","<<its->b<<")  ";
    }
    cout<<endl;
}