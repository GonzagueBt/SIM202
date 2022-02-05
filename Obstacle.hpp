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
    Obstacle(Point *x = nullptr, int n=0): Sommets(x), nbr_sommets(n) {} // Constructeur par défaut                       
    ~Obstacle(); // Destructeur                     
    Obstacle(const Obstacle &Obs); // Constructeur par copie  
    Point operator[](int i) const; // opérateur d'accès aux sommets de l'obstacle       
    bool concave_convexe(const Obstacle &Obs); // true = obstacle convexe, false = obstacle concave
    bool inte_exte(const Point & P, const Obstacle &Obs); // true = point P à l'extérieur de l'obstacle, false = point P à l'intérieur de l'obstacle
    list<Segment> constructionSeg(const Obstacle &Obs);
           
};

// structure utilisée dans les fonctions ci-dessous
struct Point_et_Indice
{
    int i; 
    Point point; 
};

// Calcul des coordonnées (2 points) des deux extrélités de la normale d'un segment
Point * Coor_Sommets_Normale(const Point & S_1, const Point & S_2);

// Calcul des coordonnées du vecteur normale (1 point)
Point Coor_Vecteur_normale(const Point & S_1, const Point & S_2);

// Retorune le sommet de l'obstacle le plus proche du point A ainsi que le numéro du sommet en question
Point_et_Indice Trouver_Sommet_le_plus_proche(const Point &A, const Obstacle &Obs);

// Produit scalaire classique entre 2 segments
double Produit_Scalaire(const Point & a, const Point & b);





#endif
