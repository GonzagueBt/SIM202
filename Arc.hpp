#include "Point.hpp"
#include <cmath>
#include <iostream>
#ifndef Arc_H
#define Arc_H

#define square(a)  (a)*(a)

class Arc{
    public: 
        Point a,b;
        double poid;
        Arc(Point x=0, Point y=0, double z=0): a(x), b(y), poid(z){} 
};

// Fonctions externes 
ostream & operator <<(ostream& os, const Arc &A);

class Segment : public Arc{
    public:
        Segment(Point x, Point y);
}; 


#endif