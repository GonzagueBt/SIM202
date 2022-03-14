#include "parserObstacle.h"
ofstream out1;

void parserObstacle(list<Obstacle> l_obs)
{
    out1.open("Chevauchement.txt");
    out1<< l_obs.size()<<endl; // nombre d'obstacles
    list<Obstacle>::iterator itl = l_obs.begin();
    for(; itl!=l_obs.end(); itl++){ // on parcours les obstacles
        out1<<itl->nbr_sommets<<endl;
        list<Segment>::iterator its = itl->segValides_contour.begin();
        for(; its!=itl->segValides_contour.end(); its++){ // on parcours les sommets de l'obstacle
            out1<< its->a.x << " "<< its->a.y<<" "<<its->b.x<<" "<<its->b.y<<endl;
        }
    }
    out1.close();
}
