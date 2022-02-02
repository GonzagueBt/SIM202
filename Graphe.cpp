#include "Graphe.hpp"


Graphe::Graphe(list<Obstacle> obst, Point x, Point y){
    depart = x;
    fin = y;
    list<Obstacle>::iterator its=obst.begin();
    Obstacle final= *its;
    its++;
    while(its!= obst.end()){
        final = sommeObstacles(final, *its);
        its++;
    }
    Point dep[1] = x;
    Obstacle depart(dep, 1);
    final = sommeObstacles(final, depart);
    depart.Sommets[0] = y;
    graphe_ = sommeObstacles(final, depart).segValides;
}

Obstacle sommeObstacles(Obstacle ob1, Obstacle ob2){
    list<Segment>::iterator its = ob2.segValides.begin();
    for(; its!= ob2.segValides.end(); its++) ob1.segValides.push_back(*its);
    for(int i=0; i<ob1.nbr_sommets; i++){
        for(int  j=0; j<ob2.nbr_sommets; j++){
            its=ob1.segValides.begin();
            for(; its!= ob1.segValides.end(); its++){
                if(!intersect(ob1.Sommets[i], ob2.Sommets[j], its->a, its->b)){
                    Segment newSeg = Segment(ob1.Sommets[i], ob2.Sommets[j]);
                    ob1.segValides.push_back(newSeg);
                } 
            }
            its=ob2.segValides.begin();
            for(; its!= ob2.segValides.end(); its++){
                if(!intersect(ob1.Sommets[i], ob2.Sommets[j], its->a, its->b)){
                    Segment newSeg = Segment(ob1.Sommets[i], ob2.Sommets[j]);
                    ob1.segValides.push_back(newSeg);
                } 
            }
        }
    }
    ob1.nbr_sommets += ob2.nbr_sommets;
    ob1.Sommets = concatenateListe(ob1.nbr_sommets, ob2.nbr_sommets, ob1.Sommets, ob2.Sommets);
    return ob1;
}



// Prend 2 listes de points avec le taille en entrée, et retourne un tableau de la concatenation des deux listes.
Point * concatenateListe(int nb1, int nb2, Point * liste1, Point * liste2){
    Point res[nb1+nb2];
    for(int i=0; i<nb1; i++){
        res[i]=liste1[i];
    }
    for(int i=0; i<nb2; i++){
        res[i+nb1]=liste2[i];
    }
    return res;
}





//vector<vector<double> > init


//////// Intersection entre 2 segments AB et CD /////////
// https://bryceboe.com/2006/10/23/line-segment-intersection-algorithm/

bool ccw(Point A, Point B, Point C){
    return ((C.y-A.y) * (B.x-A.x)) > ((B.y-A.y) * (C.x-A.x));
}

bool intersect(Point A, Point B, Point C, Point D){
    return ccw(A,C,D) != ccw(B,C,D) and ccw(A,B,C) != ccw(A,B,D);
}

////////////////////////////////////////////////////////////