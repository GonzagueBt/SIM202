#include "Graphe.hpp"
#include "Dijsktra.hpp"
using namespace std;
#include <iostream> 
#include <list>




int main(){
    cout<<"=========== Initialisation Graphe ==========="<<endl;
    Obstacle ob1(exemple(),4);
    list<Obstacle> Obstacle;
    Obstacle.push_back(ob1);
    Point depart;
    Point fin;
    cout<<endl;
    cout<<"=========== Construction Graphe ==========="<<endl;
    Graphe g(Obstacle, depart, fin);
    Point memory[g.nb_sommets];
    cout<<endl;
    cout<<"=========== Construction Matrice c ==========="<<endl;
    vector<vector<double> > c = buildMatrixC(memory, g);
    cout<<endl;
    cout<<"=========== Algorithme Dijsktra ==========="<<endl;
    double l[g.nb_sommets];
    double p[g.nb_sommets];
    Dijsktra(g.nb_sommets, c, l, p);


    return 0;
}




vector<Point> exemple(){
    vector<Point> exemple;
    exemple.push_back(Point(0,3));
    exemple.push_back(Point(3,3));
    exemple.push_back(Point(0,5));
    exemple.push_back(Point(5,5));
    return exemple;
}