#include "Arc.hpp"


ostream&operator<<(ostream& os, const Arc &A)
{
os<<"("<<A.a<<";"<<A.b<<")";
return os;
}

Segment::Segment(Point x, Point y){
    a=x;
    b=y;
    poid = sqrt(square(x.x - y.x) + square(x.y - y.y));
}

double distance(Point x, Point y){
    return sqrt(square(x.x - y.x) + square(x.y - y.y));
}

bool Segment::operator==(const Segment A){
    if((a==A.a && b==A.b) || (a==A.b && b==A.a)) return true;
    return false;
}

bool Segment::operator!=(const Segment A){
    if((a==A.a && b==A.b) || (a==A.b && b==A.a)) return false;
    return true;
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
    if(x==-0) x=0;
    if(y==-0) y=0;
    return Point(x,y);
}

list<Segment> concateListe(list<Segment> list1, list<Segment> list2, bool deleteDuplicate){
    list<Segment> all;
    list<Segment>::iterator its = list1.begin();
    for(; its!= list1.end(); its++) all.push_back(*its);
    its = list2.begin();
    for(; its!= list2.end(); its++){
        if(!isIn(*its, all) && deleteDuplicate) all.push_back(*its);
    }
    return all;
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
            cout<<"suppression segemnt "<<*memory<<endl;
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

void deleteSegWithPt(list<Segment>& toDelete, list<Segment> segs, Point pt){
    auto it = segs.begin();
    for(; it!= segs.end(); it++){
        if(it->a==pt || it->b==pt){
            if(!isIn(*it, toDelete)){ toDelete.push_back(*it); cout<<"segment : "<<*it<<" supprimé ll"<<endl; }
        }
    }
}

bool isConfused(Segment A, Segment B){
    Point u = A.a;
    Point v = A.b;
    double coeff = (v.y-u.y)/(v.x-u.x);
    double x = u.y - coeff*u.x;
    u = B.a;
    v = B.b;
    coeff = (v.y-u.y)/(v.x-u.x);
    double y = u.y - coeff*u.x;
    return x==y;
}

void printSegments(list<Segment> liste){
    list<Segment>::iterator its = liste.begin();
    for(; its!= liste.end(); its++){
        cout<<"("<<its->a<<","<<its->b<<")  ";
    }
    cout<<endl;
}