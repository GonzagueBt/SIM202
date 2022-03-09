#include "Obstacle.hpp"
#include <list>
#include <vector>
using namespace std;
#define max INT_MAX

#ifndef Graphe
#define Graphe_H

class Graphe{
    public :
        Point depart;
        Point fin; 
        list<Segment> graphe_Obst;
        list<Segment> graphe_Autre;
        list<Segment> graphe_All;
        int nb_sommets;
        Graphe(list<Obstacle> obstacles, Point x, Point y);
        void concateListe(); //concatenation de graphe_Obst et graphe_Autre dans graphe_All
};


Obstacle sumObstacles(Obstacle ob1, Obstacle ob2);
list<Segment> deleteIntersectionSeg(list<Segment>& toDelete, Segment A, Segment B, Obstacle& ob1, Obstacle& ob2, Obstacle& ob);
list<Segment> gestion1cas(list<Segment>& toDelete, Point x, Point inter, Segment A, Segment B, Obstacle& ob1, Obstacle& ob2, Obstacle& ob);

#endif