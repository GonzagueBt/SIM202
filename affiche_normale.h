#ifndef AFFICHE_NORMALE_H_INCLUDED
#define AFFICHE_NORMALE_H_INCLUDED

#include "Point.h"
#include "Arc.hpp"
#include "Obstacle.h"
#include <vector>
#include<list>


/**
 * @brief renvoie un vecteur de points qui constitue les coordonnées des normales. Les points sont rangés dans l'ordre
 * @param ob : un obstacle à traiter pour renvoyer un vecteur de points qui constituent les normales de l'obstacle
 */
vector<Point> affichage_normale(Obstacle Ob);

/**
 * @brief création d'un fichier .txt qui contient les informations pour afficher dans matlab un obstacle et ses normales
 * @param ob : un obstacle à afficher avec ses normales
 */
void parserNormales(Obstacle obs);

#endif // AFFICHE_NORMALE_H_INCLUDED
