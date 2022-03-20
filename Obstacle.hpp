#ifndef Obstacle_H
#define Obstacle_H
#include "Arc.hpp" 

// Avec la classe obstacle on cherche à retourner tous les segments valides d'un obstacle.
// Un segment est dit valide si il joint deux sommets d'un obstacle sans passer par l'intérieur de cet obstacle.
// Rmq: On a supposé dans toute cette section (et dans tout le projet) que les sommets d'un obstacle seront construits
// dans le sens trigonométrique.

////////////////////////////////// Fonction principale d'obstacle: constructionSeg() //////////////////////////////////////////
// Cette fonction remplit deux listes: 
//      - segValides_contour qui contient les segments qui sont sur les bords de l'obstacle
//      - segValides_reste qui contient les segments qui joignent deux sommets de l'obstacle 
//        et qui ne forment pas un segment sur le bord de l'obstacle


class Obstacle
{
public:
    int nbr_sommets;                            
    vector<Point> Sommets;
    list<Segment> segValides_contour;
    list<Segment> segValides_reste;
    Obstacle(vector<Point> P, int n = 0): nbr_sommets(n), Sommets(P) {}                                            
    bool concave_convexe(); // true = obstacle convexe, false = obstacle concave
    void constructionSeg(); // remplit une liste de segments valides
    Obstacle Padding(const int &r);
    
    /**
     * @brief Supprimer un segment d'une liste de l'Obstacle
     * @param seg le segment à supprimer
     * @param index la liste dans laquelle on doit supprimer le segment : ="contour" pour la liste segValides_contour, et ="reste" pour la liste segValides_reste
     */
    void deleteSegFromList(Segment seg, string index);
};


//////////////////////////////////////////|-----------------------------------|//////////////////////////////////
//////////////////////////////////////////| Concavité/Convexité de l'obstacle |//////////////////////////////////
//////////////////////////////////////////|-----------------------------------|//////////////////////////////////


/**
 * @brief Calcul des coordonnées du vecteur normale (1 point)
 * @return les coordonnées (sous forme de point) du vecteur normale sortant au segment [S_1,S_2]
 */
Point Coor_Vecteur_Normale(const Point & S_1, const Point & S_2);

/**
 * @brief Calcul des coordonnées (2 points) des deux extrémités de la normale d'un segment
 * @return deux points: le point de départ et celui d'arivée de la normale au segment [S_1,S_2]
 */
vector<Point> Coor_Sommets_Normale(const Point & S_1, const Point & S_2);

/**
 * @brief Calcul de l'angle algébrique entre les segments (a,b) et (b,c)
 * @return true si l'angle est >= 0, false sinon
 */
bool transfo(const Point & a, const Point & b, const Point & c);


//////////////////////////////|-------------------------------------------------|////////////////////////////////
//////////////////////////////| Construction des segments valides de l'obstacle |////////////////////////////////
//////////////////////////////|-------------------------------------------------|////////////////////////////////

// Un premier outil utile est de savoir si il y a une intersection entre deux segments

//////////////////////////////// Intersection de 2 segments  ////////////////////////////////// 
bool ccw(const Point & A,const Point &B,const Point &C);
/**
 * @brief Check si le segment formé des points AB et le segment formé des points CD se croisent
 * @return true si les segments AB et CD se croisent
 * @return false sinon
 */
bool intersect(const Point &A, const Point &B, const Point &C, const Point &D); 

/**
 * @return true si A intersecte B
 */
bool intersect(const Segment A, const Segment B);

// Un second outil utile est de savoir si un point est à l'extérieur d'un obstacle

//////////////////////////////////////////| Point extérieur à l'obstacle |///////////////////////////////////////////

/**
 * @brief Vérifie si un point se trouve dans un obstacle
 * @param x : le point à regarder
 * @param ob : l'obstacle
 * @return true si le point est à l'extérieur ou sur un coté de l'obstacle
 * @return false si le point x se trouve dans l'obstacle.
 */
// Le principe de cette fonction: on prend notre point x, on trace un demi-droite vertical vers l'infini.
// Si cette demi droite à un nombre d'intersection paire avec les contours de notre obstacle, alors x
// est forcément à l'extérieur de l'obstacle.
bool isOutside(Point x, Obstacle ob);

/**
 * @brief Construit un obstacle et tout ses segments 
 * Construit également les segments valides entre les points non consécutifs (à la différence du constructeur Obstacle) 
 * @param V une liste de Point 
 * @return instancier les obstacles dans le main
 */
Obstacle ConstructObstacle(vector<Point> V);

/* Fonction print pour faire des tests
void printSegValides(list<Segment> liste);
*/

#endif
