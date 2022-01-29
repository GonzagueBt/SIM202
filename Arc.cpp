#include "Arc.hpp"


Arc::ostream & operator <<(ostream& os, const Arc &A)
{
os<<"Distance entre "<<A.a<<" et "<<A.b<<" : "<<A.poid;
return os;
}


Segment::Segment(Point x, Point y){
    a=x;
    b=y;
    poid = sqrt(square(x.x - y.x) + square(x.y - y.y));
}
