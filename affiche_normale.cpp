#include "Point.h"
#include "Arc.hpp"
#include "Obstacle.h"
#include "affiche_normale.h"
#include <vector>
#include<list>
ofstream out2;

vector<Point> affichage_normale(Obstacle Ob)
{
    vector<Point> res;
    for(int i = 0; i< Ob.nbr_sommets-1; i++)
    {
        vector<Point> ajoute = Coor_Sommets_Normale(Ob.Sommets[i], Ob.Sommets[i+1]);
        res.push_back(ajoute[0]);
        res.push_back(ajoute[1]);
    }
    vector<Point> dernier = Coor_Sommets_Normale(Ob.Sommets[Ob.nbr_sommets - 1],Ob.Sommets[0]);
    res.push_back(dernier[0]);
    res.push_back(dernier[1]);
    return res;
}

// Crée un fichier avec les coordonnées 1 obstacle et ses normales
void parserNormales(Obstacle obs)
{
    vector<Point> normales = affichage_normale(obs);
    out2.open("Normale.txt");
    out2<< obs.nbr_sommets<<endl; // nombre de sommets
    list<Segment>::iterator itl = obs.segValides_contour.begin();
    for(; itl!=obs.segValides_contour.end(); itl++){ // on parcours les sommets
        out2<< itl->a.x << " "<< itl->a.y<<" "<<itl->b.x<<" "<<itl->b.y<<endl;
        }
    out2<< normales.size()<<endl; // nombre de normales
    vector<Point>::iterator its = normales.begin();
    for(; its!=normales.end(); its++){ // on parcours les normales
        out2<< its->x << " "<< its->y<<endl;
        }
    out2.close();
}
