
#include "main.hpp"

int main(){
    cout<<"=========== Initialisation Graphe ==========="<<endl;
    list<Obstacle> Obstacles = exampleobsts();
    cout<<"liste obstacle construite"<<endl;
    Point depart(0,0);
    Point fin(15,15);
    cout<<"Point depart et fin construit"<<endl;
    cout<<endl;
    cout<<"=========== Construction Graphe ==========="<<endl;
    Graphe g(Obstacles, depart, fin);
    cout<<"Graphe g contruit"<<endl;
    cout<<"liste des segments du graphe"<<endl;
    printSegments(g.graphe_All);
    Point memory[g.nb_sommets];
    cout<<endl;
    cout<<"=========== Construction Matrice c ==========="<<endl;
    vector<vector<double> > c = buildMatrixC(memory, g);
    //printMatricC(c, memory, g.nb_sommets);
    cout<<endl;
    cout<<"=========== Algorithme Dijsktra ==========="<<endl;
    double l[g.nb_sommets];
    double p[g.nb_sommets];
    Dijsktra(g.nb_sommets, c, l, p);
    list<Point> chemin = cheminFinale(memory, p, g.nb_sommets);
    cout<<"chemin optimal : ";
    printPoints(chemin);
    cout<<endl;
    cout<<"=========== Construction fichier obstacles.txt ==========="<<endl;
    parserObstacles(Obstacles);
    cout<<"=========== Construction fichier graphe.txt ==========="<<endl;
    parserGraphe(g,chemin);
    parserObstacle(g, chemin);
    if(Obstacles.size()>0){
        parserConcave(Obstacles.front());
        parserNormales(Obstacles.front());
    }
    return 0;
}



list<Obstacle> exampleobsts(){
    list<Obstacle> obsts;
    vector<Point> Sommets1;
    Sommets1.push_back(Point(-1,1)); 
    Sommets1.push_back(Point(1,1));
    Sommets1.push_back(Point(1,3)); 
    Sommets1.push_back(Point(-1,3));
    Sommets1.push_back(Point(-2,3));
    Sommets1.push_back(Point(-2,-2));
    Sommets1.push_back(Point(3,-2));
    Sommets1.push_back(Point(3,5));
    Sommets1.push_back(Point(-1,5));
    Sommets1.push_back(Point(-1,4));
    Sommets1.push_back(Point(2,4));
    Sommets1.push_back(Point(2,-1));
    Sommets1.push_back(Point(-1,-1));
    obsts.push_back(ConstructObstacle(Sommets1));

    vector<Point> Sommets2;
    Sommets2.push_back(Point(-1,5));
    Sommets2.push_back(Point(1,5));
    Sommets2.push_back(Point(1,8));
    Sommets2.push_back(Point(-1,8));
    Sommets2.push_back(Point(0,7));
    Sommets2.push_back(Point(-1,6));
    obsts.push_back(ConstructObstacle(Sommets2));

    vector<Point> Sommets3;
    Sommets3.push_back(Point(-3,2));
    Sommets3.push_back(Point(-2,2));
    Sommets3.push_back(Point(-2,10)); 
    Sommets3.push_back(Point(2,10)); 
    Sommets3.push_back(Point(2,8)); 
    Sommets3.push_back(Point(4,8));
    Sommets3.push_back(Point(4,6));
    Sommets3.push_back(Point(5,6)); 
    Sommets3.push_back(Point(5,9));
    Sommets3.push_back(Point(3,11));
    Sommets3.push_back(Point(4,12));
    Sommets3.push_back(Point(2,12)); 
    Sommets3.push_back(Point(-3,12));
    obsts.push_back(ConstructObstacle(Sommets3));

    vector<Point> Sommets4;
    Sommets4.push_back(Point(2,6)); 
    Sommets4.push_back(Point(3,6)); 
    Sommets4.push_back(Point(3,7));
    Sommets4.push_back(Point(2,7)); 
    obsts.push_back(ConstructObstacle(Sommets4));

    vector<Point> Sommets5;
    Sommets5.push_back(Point(4,1));
    Sommets5.push_back(Point(5,1));
    Sommets5.push_back(Point(6,3));
    Sommets5.push_back(Point(6,1));
    Sommets5.push_back(Point(7,1));
    Sommets5.push_back(Point(7,13));
    Sommets5.push_back(Point(5,13));
    Sommets5.push_back(Point(5,11));
    Sommets5.push_back(Point(6,9));
    Sommets5.push_back(Point(6,5));
    Sommets5.push_back(Point(4,3));
    obsts.push_back(ConstructObstacle(Sommets5));

    vector<Point> Sommets6;
    Sommets6.push_back(Point(10,11)); 
    Sommets6.push_back(Point(11,13)); 
    Sommets6.push_back(Point(13,14));
    Sommets6.push_back(Point(11,15));
    Sommets6.push_back(Point(10,17));
    Sommets6.push_back(Point(9,15));
    Sommets6.push_back(Point(7,14)); 
    Sommets6.push_back(Point(9,13));
    obsts.push_back(ConstructObstacle(Sommets6));

    vector<Point> Sommets7;
    Sommets7.push_back(Point(6.6,14)); 
    Sommets7.push_back(Point(6.6,17)); 
    Sommets7.push_back(Point(-2,17));
    Sommets7.push_back(Point(-2,14)); 
    obsts.push_back(ConstructObstacle(Sommets7));

    vector<Point> Sommets8;
    Sommets8.push_back(Point(13.5,13)); 
    Sommets8.push_back(Point(17,13)); 
    Sommets8.push_back(Point(17,14)); 
    Sommets8.push_back(Point(14,14));
    Sommets8.push_back(Point(14,16));
    Sommets8.push_back(Point(17,16));
    Sommets8.push_back(Point(17,20));
    Sommets8.push_back(Point(13.5,20));
    obsts.push_back(ConstructObstacle(Sommets8));

    vector<Point> Sommets9;
    Sommets9.push_back(Point(10,2)); 
    Sommets9.push_back(Point(11,2)); 
    Sommets9.push_back(Point(11,5)); 
    Sommets9.push_back(Point(12,5));
    Sommets9.push_back(Point(12,4));
    Sommets9.push_back(Point(16,8));
    Sommets9.push_back(Point(15,8));
    Sommets9.push_back(Point(15,7));
    Sommets9.push_back(Point(14,7));
    Sommets9.push_back(Point(14,8));
    Sommets9.push_back(Point(13,8));
    Sommets9.push_back(Point(13,7));
    Sommets9.push_back(Point(12,7));
    Sommets9.push_back(Point(12,8));
    Sommets9.push_back(Point(11,8));
    Sommets9.push_back(Point(11,7));
    Sommets9.push_back(Point(10,7));
    Sommets9.push_back(Point(10,8));
    Sommets9.push_back(Point(9,8));
    obsts.push_back(ConstructObstacle(Sommets9));

    vector<Point> Sommets10;
    Sommets10.push_back(Point(12,10));
    Sommets10.push_back(Point(13,10)); 
    Sommets10.push_back(Point(13,9)); 
    Sommets10.push_back(Point(15,9));
    Sommets10.push_back(Point(15,11));
    Sommets10.push_back(Point(13,11));
    Sommets10.push_back(Point(13,13));
    Sommets10.push_back(Point(12,13));
    obsts.push_back(ConstructObstacle(Sommets10));
    return obsts;
}

    
