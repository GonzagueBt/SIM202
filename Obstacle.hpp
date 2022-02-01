#include "Point.hpp"
#include "Arc.hpp"
#include <iostream> 
using namespace std;
#ifndef Project_H
#define Project_H


class Obstacle
{
public:
    int nbr_sommets;                            
    Point *Sommets; 
    Obstacle(Point *x = nullptr, double n=0): Sommets(x), nbr_sommets(n){} // Constructeur par défaut                       
    ~Obstacle(); // Destructeur                     
    Obstacle(const Obstacle &Obs); // Constructeur par copie           
    bool &concave_convexe(const Obstacle &Obs);  
           
};
