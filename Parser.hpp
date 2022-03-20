#include "Graphe.hpp"
#include <list>

/**
 * @brief Création d'un fichier .txt contenant les informations du graphe et sa résolution
 * @param g : le graphe 
 * @param chemin : le parcourt solution du graphe 
 */
void parserGraphe(Graphe g, list<Point> chemin);

void parserObstacle(Graphe g, list<Point> chemin);

/**
 * @brief Cr�ation d'un fichier .txt contenant les informations des diff�rents obstacles avant chevauchement
 * @param l_obs : la liste d'obstacles � afficher
 */
void parserObstacles(list<Obstacle> l_obs);

/**
 * @brief Cr�ation d'un fichier .txt contenant les informations d'un obstacle concave
 * @param obs : un obstacle � afficher, aisni que les segments reliant les sommets formant des parties concaves
 */
void parserConcave(Obstacle obs);


/**
 * @brief renvoie un vecteur de points qui constitue les coordonn�es des normales. Les points sont rang�s dans l'ordre
 * @param ob : un obstacle � traiter pour renvoyer un vecteur de points qui constituent les normales de l'obstacle
 */
vector<Point> affichage_normale(Obstacle Ob);

/**
 * @brief cr�ation d'un fichier .txt qui contient les informations pour afficher dans matlab un obstacle et ses normales
 * @param ob : un obstacle � afficher avec ses normales
 */
void parserNormales(Obstacle obs);
