
#include "main.hpp"

int main(){
    cout<<"=========== Initialisation Graphe ==========="<<endl;
    Obstacle ob1 = ConstructObstacle(exemple());
    list<Obstacle> Obstacles;
    Obstacles.push_back(ob1);
    Obstacle ob2 = ConstructObstacle(exemple2());
    Obstacles.push_back(ob2);
    Obstacle ob3 = ConstructObstacle(exemple3());
    //Obstacles.push_back(ob3);
    cout<<"liste obstacle construite"<<endl;
    Point depart(0,0);
    Point fin(2,3);
    cout<<"Point depart et fin construit"<<endl;
    cout<<endl;
    cout<<"=========== Construction Graphe ==========="<<endl;
    Graphe g(Obstacles, depart, fin);
    cout<<"graphe g contruit"<<endl;
    printSegments(g.graphe_All);
    Point memory[g.nb_sommets];
    cout<<endl;
    cout<<"=========== Construction Matrice c ==========="<<endl;
    vector<vector<double> > c = buildMatrixC(memory, g);
    printMatricC(c, memory, g.nb_sommets);
    cout<<endl;
    cout<<"=========== Algorithme Dijsktra ==========="<<endl;
    double l[g.nb_sommets];
    double p[g.nb_sommets];
    Dijsktra(g.nb_sommets, c, l, p);
    list<Point> chemin = cheminFinale(memory, p, g.nb_sommets);
    printPoints(chemin);
    cout<<endl;
    cout<<"=========== Construction fichier graphe.txt ==========="<<endl;
    parserGraphe(g,chemin);
    return 0;
}




vector<Point> exemple(){
    vector<Point> exemple;
    exemple.push_back(Point(2,1));
    exemple.push_back(Point(2,4));
    exemple.push_back(Point(1,4));
    exemple.push_back(Point(1,2));
    exemple.push_back(Point(-1,2));
    exemple.push_back(Point(-1,4));
    exemple.push_back(Point(-2,4));
    exemple.push_back(Point(-2,1));
    return exemple;
}

vector<Point> exemple2(){
    vector<Point> exemple;
    exemple.push_back(Point(1.5,0));
    exemple.push_back(Point(4,0));
    exemple.push_back(Point(4,3));
    exemple.push_back(Point(1.5,3));
    return exemple;
}

vector<Point> exemple3(){
    vector<Point> exemple;
    exemple.push_back(Point(-2,2));
    exemple.push_back(Point(2,2));
    //exemple.push_back(Point(2,4));
    //exemple.push_back(Point(-2,4));
    return exemple;
}
