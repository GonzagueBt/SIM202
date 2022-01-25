#include "Point.hpp"
#include <cmath>

#define square(a)  (a)*(a)

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