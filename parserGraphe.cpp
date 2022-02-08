#include "parserGraphe.hpp"

void parserGraphe(Graphe g, list<Point> chemin){
    out.open("Graphe.txt");  
    out<< g.graphe_.size()<<endl;
    out<<g.nb_sommets<<endl;
    list<Segment>::iterator its = g.graphe_.begin();
    for(; its!= g.graphe_.end(); its++){
        out<< its->a.x<<" "<<its->a.y<<" "<<its->b.x<<" "<<its->b.y<<endl;
    }
    out<< chemin.size()<<endl;
    list<Point>::iterator it = chemin.begin();
    for(;it !=chemin.end(); its++){
        out<<it->x<<" "<<it->y<<endl;
    }
    out.close();
}