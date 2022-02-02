#include "Point.hpp"
#include "Arc.hpp"
#include "Obstacle.hpp"
#include <list>
extern ostream out;


Point Obstacle::operator[](int i) const
{
  return Sommets[i];
}



Obstacle::Obstacle(Point *x, int n){
    nbr_sommets = n;
    Sommets = x;
    segValides = constructionSeg(nbr_sommets, Sommets);
}

list<Segment> constructionSeg(int nb, Point * pts){
    Point premier = pts[0];
}



Point Calcul_coor_Normale(const Point & S_1, const Point & S_2)
{
    Point S_milieu;
    S_milieu = (S_1 + S_2) / 2;
    Point P;
    P = S_1 | S_2;
    Point res;
    res.x = - P.y;
    res.y = P.x;
    return res;
}


double Produit_Scalaire(const Point & a, const Point & b)
{
    double res;
    res = (a.x * b.x) + (a.y * b.y);
    return res;
}

double transfo(const Point & a, const Point & b, const Point & c)
{
    Point P;
    P = Calcul_coor_Normale(a,b);
    Point Q;
    Q = Calcul_coor_Normale(b,c);
    return Produit_Scalaire(P,Q);
}


bool Obstacle::concave_convexe(const Obstacle &Obs)
{   
    if(Obs.nbr_sommets==1) return true; /// ajout pour gestion facile point de départ et d'arrivée dans Graphe
    int k = 0;
    for (int i = 0; i < (Obs.nbr_sommets - 2); i++)
    {
        if (transfo(Obs[i], Obs[i+1], Obs[i+2]) < 0)
            k += 1;
    }
    if (transfo(Obs[Obs.nbr_sommets - 2], Obs[Obs.nbr_sommets - 1], Obs[0]) < 0)
        k+=1;
    if (transfo(Obs[Obs.nbr_sommets - 1], Obs[0], Obs[1]) < 0)
        k+=1;
    if (k == nbr_sommets)
        return true;
    else if (k != nbr_sommets)
        return false;
}


bool inte_exte(const Point & P, const Obstacle &Obs)
{   
    if(Obs.nbr_sommets==1) return true; /// ajout pour gestion facile point de départ et d'arrivée dans Graphe
    
}

