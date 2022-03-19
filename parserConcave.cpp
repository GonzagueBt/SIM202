#include "parserConcave.h"
#include <list>
#include "Obstacle.h"
ofstream out3;



void parserConcave(Obstacle obs)
{
    out3.open("Concave.txt");
    out3<< obs.segValides_contour.size()<<endl; // nombre de segments formant l'obstacle
    list<Segment>::iterator itl = obs.segValides_contour.begin();
    for(; itl!=obs.segValides_contour.end(); itl++){
        out3<< itl->a.x << " "<< itl->a.y<<" "<<itl->b.x<<" "<<itl->b.y<<endl;
        }
    out3<< obs.segValides_reste.size()<<endl;
    list<Segment>::iterator its = obs.segValides_reste.begin();
    for(; its!=obs.segValides_reste.end(); its++){
        out3<< its->a.x << " "<< its->a.y<<" "<<its->b.x<<" "<<its->b.y<<endl;
        }
    out3.close();
}
