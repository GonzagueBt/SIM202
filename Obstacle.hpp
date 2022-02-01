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
    Obstacle(Point *x = nullptr, double n=0): Sommets(x), nbr_sommets(n){} // Constructeur par défaut                       
    ~Obstacle(); // Destructeur                     
    Obstacle(const Obstacle &Obs); // Constructeur par copie           
    bool &concave_convexe(const Obstacle &Obs);  
           
};

#endif Project_H