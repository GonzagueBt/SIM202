#ifndef PARSERCONCAVE_H_INCLUDED
#define PARSERCONCAVE_H_INCLUDED

#include "Arc.hpp"
# include <list>
#include "Obstacle.h"
/**
 * @brief Création d'un fichier .txt contenant les informations d'un obstacle concave
 * @param obs : un obstacle à afficher, aisni que les egments reliant les sommets formant des parties concaves
 */

void parserConcave(Obstacle obs);

#endif // PARSERCONCAVE_H_INCLUDED
