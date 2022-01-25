#include "Arc.hpp"

Segment::Segment(Point x, Point y){
    a=x;
    b=y;
    poid = sqrt(square(x.x - y.x) + square(x.y - y.y));
}