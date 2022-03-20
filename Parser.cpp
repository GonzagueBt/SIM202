#include "Parser.hpp"
ofstream out;

void parserGraphe(Graphe g, list<Point> chemin){
    out.open("Graphe.txt");  
    out<< g.graphe_Autre.size()<<endl;
    out<< g.graphe_Obst.size()<<endl;
    out<<g.nb_sommets<<endl;
    list<Segment>::iterator  its = g.graphe_Autre.begin();
    for(; its!= g.graphe_Autre.end(); its++){
        out<< its->a.x<<" "<<its->a.y<<" "<<its->b.x<<" "<<its->b.y<<endl;
    }
    its = g.graphe_Obst.begin();
    for(; its!= g.graphe_Obst.end(); its++){
        out<< its->a.x<<" "<<its->a.y<<" "<<its->b.x<<" "<<its->b.y<<endl;
    }
    out<< chemin.size()<<endl;
    list<Point>::iterator it = chemin.begin();
    for(;it !=chemin.end(); it++){
        out<<it->x<<" "<<it->y<<endl;
    }
    out.close();
}

void parserObstacle(Graphe g, list<Point> chemin)
{
    out.open("Graphe&trajectoire.txt");
    out<< g.graphe_Obst.size()<<endl;
    out<<g.nb_sommets<<endl;
    auto its = g.graphe_Obst.begin();
    for(; its!= g.graphe_Obst.end(); its++){
        out<< its->a.x<<" "<<its->a.y<<" "<<its->b.x<<" "<<its->b.y<<endl;
    }
    out<< chemin.size()<<endl;
    list<Point>::iterator it = chemin.begin();
    for(;it !=chemin.end(); it++){
        out<<it->x<<" "<<it->y<<endl;
    }
    out.close();
}