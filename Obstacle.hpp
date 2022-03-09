#ifndef Obstacle_H
#define Obstacle_H
#include "Arc.hpp" 



class Obstacle
{
public:
    int nbr_sommets;                            
    vector<Point> Sommets;
    list<Segment> segValides_contour;
    list<Segment> segValides_reste;
    Obstacle(vector<Point> P, int n = 0): nbr_sommets(n), Sommets(P) {}                                            
    bool concave_convexe(); // true = obstacle convexe, false = obstacle concave
    void constructionSeg(); // rempli une liste de segments valides
    Obstacle Padding(const int &r);
    void deleteSegContour(Segment seg);
};

// Fonction de construction globale 
Obstacle ConstructObstacle(vector<Point> V);

// Calcul des coordonnées (2 points) des deux extrémités de la normale d'un segment
vector<Point> Coor_Sommets_Normale(const Point & S_1, const Point & S_2);

// Calcul des coordonnées du vecteur normale (1 point)
Point Coor_Vecteur_Normale(const Point & S_1, const Point & S_2);



// Renvoie l'angle algébrique entre les segments (a,b) et (b,c)
bool transfo(const Point & a, const Point & b, const Point & c);


bool isOutside(Point x, Obstacle ob);


//////////////////////////////// INTERSECTION DE 2 POINTS //////////////////////////////////
// intersect renvoie true si AB intersecte CD
bool ccw(const Point & A,const Point &B,const Point &C);
bool intersect(const Point &A, const Point &B, const Point &C, const Point &D); 
bool intersect(const Segment A, const Segment B);





#endif

