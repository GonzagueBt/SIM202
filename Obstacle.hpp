#ifndef Obstacle_H
#define Obstacle_H
#include "Arc.hpp"
#include <list>
#include <vector>


class Obstacle
{
public:
    int nbr_sommets;                            
    vector<Point> Sommets;
    list<Segment> segValides;
    Obstacle(vector<Point> P, int n=0): nbr_sommets(n), Sommets(P) {}                                            
    bool concave_convexe(); // true = obstacle convexe, false = obstacle concave
    list<Segment> constructionSeg(); // remplit une liste de segments valides        
};


// Calcul des coordonnées (2 points) des deux extrélités de la normale d'un segment
vector<Point> Coor_Sommets_Normale(const Point & S_1, const Point & S_2);

// Calcul des coordonnées du vecteur normale (1 point)
Point Coor_Vecteur_Normale(const Point & S_1, const Point & S_2);

// ccw = outils pour intersect
// intersect renvoie true si AB intersecte CD
bool ccw(const Point & A,const Point &B,const Point &C);
bool intersect(const Point &A, const Point &B, const Point &C, const Point &D); 

// Renvoie l'angle algébrique entre les segments (a,b) et (b,c)
bool transfo(const Point & a, const Point & b, const Point & c);

// Fonction de construction globale 
Obstacle ConstructObstacle(vector<Point> V);





#endif

