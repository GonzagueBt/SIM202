#include "Point.hpp"
#include <cmath>
#include <iostream>
#ifndef Arc_H
#define Arc_H

#define square(a)  (a)*(a)

class Arc{
    public: 
        Point a,b;
        double poid;
        Arc(Point x=0, Point y=0, double z=0): a(x), b(y), poid(z){} 
};

// Surcharges Opérateurs 
ostream & operator <<(ostream& os, const Arc &A);

class Segment : public Arc{
    public:
        Segment(Point x, Point y);
        bool operator==(const Segment);
        bool operator!=(const Segment);
}; 

double distance(Point x, Point y);

/**
 * @brief Calcule le point d'intersection de 2 arcs/segments
 * @attention l'Utilsation de cette fonction suppose que les 2 arcs se croisent
 * @return Point : le point d'intersection de A et B
 */
Point Intersction2Arcs(Arc A, Arc B);

/**
 * @brief Fait la concatenation de deux listes 
 * @param deleteDuplicate si true, la fonction supprime les segments en doublon, si false, elle les garde tous.
 * @return la une nouvelle liste de segments
 */
list<Segment> concateListe(list<Segment> list1, list<Segment> list2,bool deleteDuplicate);

/**
 * @brief Vérifie si un segment est présent dans une liste de segments
 * @return true si le segment A est dans la liste segs
 * @return false sinon
 */
bool isIn(Segment A, list<Segment> segs);


/**
 * @brief Supprime tous les segments présents plusieurs fois dans une liste
 * @return list<Segment> 
 */
list<Segment> deleteSegCommun(list<Segment>  liste);

/**
 * @brief Compte le nombre de points d'un vector de points non utilisés dans une liste de segments
 */
int sommetsNonUsed(vector<Point> pts, list<Segment> segs);

/**
 * @brief Ajoute à la liste de segment à supprimer, tous les segments de la liste segs contenant le point pt 
 */
void deleteSegWithPt(list<Segment>& toDelete, list<Segment> segs, Point pt);

/**
 * @brief Regarde si les segments ont une partie commune (c'est à dire qu'ils sont colinéaires)
 * @return renvoie true  si c'est le cas
 */
bool isConfused(Segment A, Segment B);

/**
 * @brief Print une liste de Segment
 */
void printSegments(list<Segment> liste);


#endif