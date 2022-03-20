#ifndef AFFICHE_NORMALE_H_INCLUDED
#define AFFICHE_NORMALE_H_INCLUDED

#include "Point.hpp"
#include "Arc.hpp"
#include "Obstacle.hpp"
#include <vector>
#include <list>


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

#endif // AFFICHE_NORMALE_H_INCLUDED
