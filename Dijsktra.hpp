#include <vector>
#include <list>
#include <fstream>
#include "parserGraphe.hpp"
#include "parserObstacle.h"

/** 
 * @brief :  Effectue l'agorithme de Dijsktra sur un graphe 
 * @param N : le nombre de sommet
 * @param c : une matrice de taile NxN contenant les poids des aretes du graphe
 * @param l : la liste à remplir des prédecesseurs de chaque sommet
 * @param p : la liste à remplir des poids de chaque sommet
 * */
void Dijsktra(int N, vector<vector<double> > c, double *l, double *p);

/**
 * @brief Initialise la matrice c pour l'algorithme de Dijkstra
 * les points de la diagonale  sont initialisés à 0 (distance entre un sommet et lui même =0) et tous les autres à INT_MAX
 * @param nb : la dimension de la matrice c (nb*nnb)
 * @return vector<vector<double> > 
 */
vector<vector<double> > initC(int nb);

/**
 * @brief Rempli la matrice C pour l'algorithme de Dijsktra avec les poids des aretes d'un graphe
 * @param memory : tableau de points que l'on va remplir dans la fonction pour avoir les index des sommets dans la matrice c
 * @param g : le graphe contenant les aretes avec lesquels on va remplir la matrice c
 * @return vector<vector<double> > 
 */
vector<vector<double> > buildMatrixC(Point * memory, Graphe g);


/**
 * @brief Créer le chemin le plus court entre le sommet de départ et de fin, après l'algorithme de Dijsktr
 * @param memory : l'ordre des sommets dans la matrice c de Dijsktra, et donc donne l'index des sommets pour le tableau p
 * @param p : tableau contenant le prédecesseur de chaque sommet
 * @param nb : le nombre de sommet
 * @return list<Point> 
 */
list<Point> cheminFinale(Point * memory, double * p, int nb);

/**
 * @brief Print la matrice c sous forme de matrice
 * @param c : la matrice c 
 */
void printMatricC(vector<vector<double> > c, Point * memory, int nb);

