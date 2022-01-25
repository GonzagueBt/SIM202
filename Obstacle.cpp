#include "Obstacle.hpp"


//////// Intersection entre 2 segments AB et CD /////////
// https://bryceboe.com/2006/10/23/line-segment-intersection-algorithm/
double ccw(Point A, Point B, Point C){
    return (C.y-A.y) * (B.x-A.x) > (B.y-A.y) * (C.x-A.x);
}

double intersect(Point A, Point B, Point C, Point D){
    return ccw(A,C,D) != ccw(B,C,D) and ccw(A,B,C) != ccw(A,B,D);
}

////////////////////////////////////////////////////////////