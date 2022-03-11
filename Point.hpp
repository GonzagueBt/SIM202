#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#ifndef Point_H
#define Point_H
using namespace std;

class Point{
  public:
    double x;   //abcisse
    double y;   //ordonnée
    Point(double x0=0,double y0=0):x(x0),y(y0){} //constructeur commun
    Point& operator +=( const Point & P) {x+=P.x;y+=P.y;return *this;}
    Point& operator -= (const Point & P) {x-=P.x;y-=P.y;return *this;}
    Point& operator *= (double a){x*=a;y*=a;return *this;}
    Point& operator /= (double a){x/=a;y/=a;return *this;}           //pas de test de division par 0!
};

//Surcharges d'opérateurs //
Point operator + (const Point& ,const Point&);
Point operator - (const Point& ,const Point&);
Point operator * (const Point& ,double a);
Point operator * (double a,const Point & );
Point operator / (const Point& ,double a);
bool operator == (const Point& ,const Point& );
bool operator != (const Point& ,const Point& );
bool operator<(const Point&, const Point&);
ostream & operator <<(ostream &, const Point &);
Point operator | (const Point &u, const Point &v); 


/**
 * @brief Fait la concatenation de 2 vector de points en supprimant les doublons
 * @return vector<Point> 
 */
vector<Point> concateVectorPoints(vector<Point> a, vector<Point> b);

/**
 * @brief Vérifie si un point appartient à un tableau de points
 * @param a : le point que l'on vérifie
 * @param memory : le tableau de poitns
 * @param nb : nombre de point dans le tableau memory
 * @return retourne l'index du point a dans le tableau memory
 * @return -1 si le point a n'appartient pas au tableau memory
 */
int isIn(Point a, Point *memory, int nb);

/**
 * @brief Vérifie si le  point a appartient au vecteur de points pts
 */
bool isIn(Point a, vector<Point> pts);

/**
 * @brief Print une liste de points
 */
void printPoints(list<Point> point);

/**
 * @brief Print un vector de Point 
 */
void printSommet(vector<Point> sommet);

#endif