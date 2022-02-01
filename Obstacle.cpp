#include "Obstacle.hpp"


Obstacle::Obstacle(Point *x = nullptr, double n=0){
    nbr_sommets = n;
    Sommets = x;
    segValides = constructionSeg(nbr_sommets, Sommets);
}

list<Segment> constructionSeg(int nb, Point * pts){
    Point premier = pts[0];
}