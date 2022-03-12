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
    void deleteSegFromList(Segment seg);
};

/**
 * @brief Construit un obstacle est tous ses segments 
 * Construit également les segments valides entre les points non consécutifs (à la différence du constructeur Obstacle) 
 * @param V une liste de Point 
 */
Obstacle ConstructObstacle(vector<Point> V);

// Calcul des coordonnées (2 points) des deux extrémités de la normale d'un segment
vector<Point> Coor_Sommets_Normale(const Point & S_1, const Point & S_2);

// Calcul des coordonnées du vecteur normale (1 point)
Point Coor_Vecteur_Normale(const Point & S_1, const Point & S_2);



// Renvoie l'angle algébrique entre les segments (a,b) et (b,c)
bool transfo(const Point & a, const Point & b, const Point & c);


/**
 * @brief Check si un point se trouve dans un obstacle
 * @param x : le point à regarder
 * @param ob : l'obstacle
 * @return true si le point est à l'extérieur OU sur un coté de l'obstacle
 * @return false si le point x se trouve dans l'obstacle.
 */
bool isOutside(Point x, Obstacle ob);


//////////////////////////////// INTERSECTION DE 2 POINTS ////////////////////////////////// 
bool ccw(const Point & A,const Point &B,const Point &C);
/**
 * @brief Check si le segment formé des points AB et le segment formé des points CD se croisent
 * @return true si les segments AB et CD se croisent
 * @return false sion
 */
bool intersect(const Point &A, const Point &B, const Point &C, const Point &D); 

/**
 * @return renvoie true si A intersecte B
 */
bool intersect(const Segment A, const Segment B);





#endif

