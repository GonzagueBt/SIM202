#include "Point.hpp"
#include "Arc.hpp"
#include <iostream> 
#include <list>
using namespace std;
#ifndef Project_H
#define Project_H



class Obstacle
{
public:
    int nbr_sommets;                            
    Point *Sommets; 
    list<Segment> segValides;
    Obstacle(Point *x = nullptr, int n=0): Sommets(x), nbr_sommets(n){} // Constructeur par défaut                       
    ~Obstacle(); // Destructeur                     
    Obstacle(const Obstacle &Obs); // Constructeur par copie  
    Point operator[](int i) const;           
    bool concave_convexe(const Obstacle &Obs);  
    bool inte_exte(const Point & P, const Obstacle &Obs); 
           
};


// Fonction qui étant donné les coordonnées de deux points renvoie les coordonnées du vecteur normale
Point Calcul_coor_Normale (const Point & S_1, const Point & S_2);
// Produit scalaire entre deux vecteurs (un vecteur est tjrs représenté par un point)
double Produit_Scalaire(const Point & a, const Point & b);




#endif
