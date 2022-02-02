#include "Obstacle.hpp"
#include "Arc.hpp"
#include <list>
#include <vector>

#define max INT_MAX

class Graphe{
    public :
        Point depart;
        Point fin; 
        list<Segment> graphe_;
        int nb_sommets;
        Graphe(list<Obstacle> obstacles, Point x, Point y);

};


Obstacle sumObstacles(Obstacle ob1, Obstacle ob2);
Point * concatenateListe(Point * liste1, Point * liste2);
bool ccw(Point A, Point B, Point C);
bool intersect(Point A, Point B, Point C, Point D);
vector<vector<double> > buildMatrixC(Graphe g);