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
Obstacle constructionGraphe(list<Obstacle> obst, Point x, Point y, list<Segment>& toDelete);
/**
 * @brief Ajoute un point seul à un obstacle
 * Utile pour les points d'arrivé et de fin
 * @return Obstacle 
 */
Obstacle addPointObstacle(Obstacle final, Point x, list<Segment>& toDelete);

/**
 * @brief Fait l'assemblage de 2 obstacles
 * appelle différentes fonctions pour gérer tous les potentiels cas d'erreurs
 * @return Un Obstacle contenant la concaténation de ob1 et ob2 
 */
Obstacle assemblage2Obstsacles(Obstacle& ob1, Obstacle ob2, list<Segment>& toDelete);

/**
 * @brief Gére les morceaux de segments commun entre 2 obstacles : c'est à dire quand un sommet est commun et que 2 segments 
 * sont colinéaires. Dans ce cas, si les 2 segments ont bien une distance en commun, le plus petit segment ajouté à la liste de segment 
 * à supprimer toDelete
 * @param ob1 
 * @param ob2 
 * @param x 
 * @param toDelete 
 */
void deleteSegConfused(Obstacle& ob, Obstacle& ob1, Obstacle& ob2, Point x, list<Segment>& toDelete);

/**
 * @brief Utiliser pour la gestion des segments commun entre 2 obstacles
 */
bool isASide(Segment A, Segment B, Point x);

/**
 * @brief Ultime vérification, pour supprimer d'éventuels segments non valide qui aurai réussi à passer
 */
Obstacle lastCheck(Obstacle final);

//////////////////////////////// Gestion Chevauchement d'Obstacles ////////////////////////////////// 

/**
 * @brief Gère les chevauchements de 2 obstacles, détecte les segments de contour d'obstacle et les ajoute à la liste de segments à supprimer
 * toDelete, supprimer les points qui sont à l'intérieur de l'autre obstacle. 
 */
void checkIntersectionObsts(list<Segment>& toDelete, Obstacle& ob1, Obstacle& ob2);

/**
 * @brief Trie un vecteur de points dans l'ordre du plus proche du points à l'index 0 au plus loin
 * COULD BE BETTER : idéalement il faudrait utiliser la fonction sort() de std, à faire si reste du temps 
 * @return vector<Point> 
 */
vector<Point> sortByDist(vector<Point> pts);
#endif