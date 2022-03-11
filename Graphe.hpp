#include "Obstacle.hpp"
#include <list>
#include <vector>
using namespace std;
#define max INT_MAX

#ifndef Graphe
#define Graphe_H

class Graphe{
    public :
        Point depart;
        Point fin; 
        list<Segment> graphe_Obst;
        list<Segment> graphe_Autre;
        list<Segment> graphe_All;
        int nb_sommets;
        Graphe(list<Obstacle> obstacles, Point x, Point y);
};

/**
 * @brief Prend une liste d'obstacle et les assemble sous la forme d'un seul gros obstacle
 * Fait appel à toutes les autres fonctions de cette classe pour gérer différents cas d'attention
 * @param obst : la liste d'obstacle
 * @param x : le point de départ
 * @param y : le point de fin
 * @return un Obstacle contenant tous les obstacles concaténés en un seul.
 */
Obstacle constructionGraphe(list<Obstacle> obst, Point x, Point y);
/**
 * @brief Ajoute un point seul à un obstacle
 * Utile pour les points d'arrivé et de fin
 * @return Obstacle 
 */
Obstacle addPointObstacle(Obstacle final, Point x);

/**
 * @brief Fait l'assemblage de 2 obstacles
 * appelle différentes fonctions pour gérer tous les potentiels cas d'erreurs
 * @return Un Obstacle contenant la concaténation de ob1 et ob2 
 */
Obstacle assemblage2Obstsacles(Obstacle ob1, Obstacle ob2);

//////////////////////////////// Gestion Chevauchement d'Obstacles ////////////////////////////////// 

/**
 * @brief Parcours les obstacles ob1 et ob2 pour check si 2 de leur segments se chevauchent, et donc si les obstacles se chevauchent 
 * La fonction appellent d'autres fonction pour régler les problèmes
 * @return l'obstacle ob avec les modifications nécessaires apportées.
 */
Obstacle overLapObstacles(Obstacle& ob, Obstacle& ob1, Obstacle& ob2);

/**
 * @brief focntion appelé dans overLapObstacles, à partir des segments A et B qui se croisent, la fonction détermine la situation exact
 * c'est à dire quel point de quel segment se situe à l'intérieur de quel Obstacle, quels segments il faut supprimer, quels segments ils
 * faut crée
 * @return la liste toDelete complété
 */
list<Segment> checkIntersectionSeg(list<Segment>& toDelete, Segment A, Segment B, Obstacle& ob1, Obstacle& ob2, Obstacle& ob);
/**
 * @brief fonction appelé dans checkIntersectionSeg, effectue toute les modifications necéssaires pour gérer un chevauchement d'obstacles
 * @param toDelete une liste de segment à supprimer auquelle va être ajouté des élements dans la fonction
 * @param x le point du segment A a supprimé, que l'on conserve pour créer un autre segment avec le point d'intersection de l'autre obstacle
 * @param inter le point d'intersection entre le segment A appartenant à l'obstacle ob1 et B appartenant à ob2
 * @return list<Segment> la liste toDelete complété
 */
list<Segment> monitorInstersctSeg(list<Segment>& toDelete, Point x, Point inter, Segment A, Segment B, Obstacle& ob1, Obstacle& ob2, Obstacle& ob);

#endif