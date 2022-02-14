
#include "main.hpp"




int main(){
    cout<<"=========== Initialisation Graphe ==========="<<endl;
    Obstacle ob1(exemple(),4);
    ob1 = buildSegValideEx(ob1);
    cout<<"segment 1"<<ob1.segValides.begin()->a<<" "<<ob1.segValides.begin()->b<<endl;
    cout<<"obstacle exemple construit"<<endl;
    list<Obstacle> Obstacle;
    Obstacle.push_back(ob1);
    cout<<"liste obstacle construite"<<endl;
    Point depart(0,0);
    Point fin(4,6);
    cout<<"Point depart et fin construit"<<endl;
    cout<<endl;
    cout<<"=========== Construction Graphe ==========="<<endl;
    Graphe g(Obstacle, depart, fin);
    cout<<"graphe f contruit"<<endl;
    Point memory[g.nb_sommets];
    cout<<endl;
    cout<<"=========== Construction Matrice c ==========="<<endl;
    vector<vector<double> > c = buildMatrixC(memory, g);
    cout<<endl;
    cout<<"=========== Algorithme Dijsktra ==========="<<endl;
    double l[g.nb_sommets];
    double p[g.nb_sommets];
    Dijsktra(g.nb_sommets, c, l, p);
    cout<<endl;
    cout<<"=========== Construction fichier graphe.txt ==========="<<endl;
    //parserGraphe(g,cheminFinale(memory, p));
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

Obstacle buildSegValideEx(Obstacle exemple){
    exemple.segValides.push_back(Segment(exemple.Sommets[0],exemple.Sommets[1]));
    exemple.segValides.push_back(Segment(exemple.Sommets[1], exemple.Sommets[2]));
    exemple.segValides.push_back(Segment(exemple.Sommets[2], exemple.Sommets[3]));
    exemple.segValides.push_back(Segment(exemple.Sommets[3], exemple.Sommets[0]));
    return exemple;
}