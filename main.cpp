
#include "main.hpp"

int main(){
    cout<<"=========== Initialisation Graphe ==========="<<endl;
    Obstacle ob1 = ConstructObstacle(exemple());
    list<Obstacle> Obstacles;
    //Obstacles.push_back(ob1);
    Obstacle ob2 = ConstructObstacle(exemple2());
    Obstacles.push_back(ob2);
    Obstacle ob3 = ConstructObstacle(exemple3());
    Obstacles.push_back(ob3);
    Obstacle ob4 = ConstructObstacle(exemple4());
    //Obstacles.push_back(ob4);
    Obstacle ob5 = ConstructObstacle(exemple5());
    //Obstacles.push_back(ob5);
    Obstacle ob6 = ConstructObstacle(exemple6());
    //Obstacles.push_back(ob6);
    cout<<"liste obstacle construite"<<endl;
    parserObstacles(Obstacles);
    Point depart(0,0);
    Point fin(0,2);
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
    printMatricC(c, memory, g.nb_sommets);
    cout<<endl;
    cout<<"=========== Algorithme Dijsktra ==========="<<endl;
    double l[g.nb_sommets];
    double p[g.nb_sommets];
    Dijsktra(g.nb_sommets, c, l, p);
    list<Point> chemin = cheminFinale(memory, p, g.nb_sommets);
    cout<<"chemin optimal : ";
    printPoints(chemin);
    cout<<endl;
    cout<<"=========== Construction fichier Chevauchement.txt ==========="<<endl;
    parserObstacles(Obstacles);
    cout<<"=========== Construction fichier graphe.txt ==========="<<endl;
    parserGraphe(g,chemin);
    parserObstacle(g, chemin);
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
    exemple.push_back(Point(-2,1));
    exemple.push_back(Point(1,1));
    exemple.push_back(Point(1,2));
    exemple.push_back(Point(-2,2));
    return exemple;
}

vector<Point> exemple3(){
    vector<Point> exemple;
    exemple.push_back(Point(1,2));
    exemple.push_back(Point(1,4));
    exemple.push_back(Point(0,4));
    exemple.push_back(Point(0,2));
    return exemple;
}

vector<Point> exemple4(){
    vector<Point> exemple;
    exemple.push_back(Point(7,1));
    exemple.push_back(Point(9,1));
    exemple.push_back(Point(9,5));
    exemple.push_back(Point(7,5));
    return exemple;
}

vector<Point> exemple5(){
    vector<Point> exemple;
    exemple.push_back(Point(0,0));
    exemple.push_back(Point(2,0));
    exemple.push_back(Point(2,6));
    exemple.push_back(Point(0,6));
    return exemple;
}

vector<Point> exemple6(){
    vector<Point> exemple;
    exemple.push_back(Point(-2,1));
    exemple.push_back(Point(3,1));
    exemple.push_back(Point(3,2));
    exemple.push_back(Point(-1,2));
    exemple.push_back(Point(-1,3));
    exemple.push_back(Point(3,3));
    exemple.push_back(Point(3,4));
    exemple.push_back(Point(-1,4));
    exemple.push_back(Point(-2,4));
    return exemple;
}



/**
vector <Point> depart; depart.push_back(Point(-14,3)); Obstacle D = ConstructObstacle(depart);

    vector<Point> Sommets1;
    Sommets1.push_back(Point(-13,7)); Sommets1.push_back(Point(-13,8)); Sommets1.push_back(Point(-14,8)); 
    Sommets1.push_back(Point(-14,7)); 
    Obstacle N1 = ConstructObstacle(Sommets1);

    vector<Point> Sommets2;
    Sommets2.push_back(Point(-14,-1)); Sommets2.push_back(Point(-12,-1)); Sommets2.push_back(Point(-13,1)); 
    Obstacle N2 = ConstructObstacle(Sommets2);
    
    vector<Point> Sommets3;
    Sommets3.push_back(Point(-14,-4)); Sommets3.push_back(Point(-12,-4)); Sommets3.push_back(Point(-13,-2)); 
    Obstacle N3 = ConstructObstacle(Sommets3);

    vector<Point> Sommets4;
    Sommets4.push_back(Point(-14,-7)); Sommets4.push_back(Point(-12,-7)); Sommets3.push_back(Point(-13,-5)); 
    Obstacle N4 = ConstructObstacle(Sommets4);

    vector<Point> Sommets5;
    Sommets5.push_back(Point(-9,-8)); Sommets5.push_back(Point(-9,-6)); Sommets5.push_back(Point(-14,-6)); 
    Sommets5.push_back(Point(-14,-8));
    Obstacle N5 = ConstructObstacle(Sommets5);

    vector<Point> Sommets6;
    Sommets6.push_back(Point(-11,-7)); Sommets6.push_back(Point(-7,-7)); Sommets6.push_back(Point(-7,-3));
    Sommets6.push_back(Point(-8,-3)); Sommets6.push_back(Point(-8,-5)); Sommets6.push_back(Point(-10,-5));
    Sommets6.push_back(Point(-10,-3)); Sommets6.push_back(Point(-11,-3));
    Obstacle N6 = ConstructObstacle(Sommets6);

    vector<Point> Sommets7;
    Sommets7.push_back(Point(-7,-7)); Sommets7.push_back(Point(-5,-5)); Sommets7.push_back(Point(-3,-7));
    Sommets7.push_back(Point(-3,-3)); Sommets7.push_back(Point(-7,-3));
    Obstacle N7 = ConstructObstacle(Sommets7);

    vector<Point> Sommets8;
    Sommets8.push_back(Point(-3,-8)); Sommets8.push_back(Point(-1,-8)); Sommets8.push_back(Point(-1,-6)); 
    Sommets8.push_back(Point(-3,-6));
    Obstacle N8 = ConstructObstacle(Sommets8);

    vector<Point> Sommets9;
    Sommets9.push_back(Point(-1,-8)); Sommets9.push_back(Point(0,-8)); Sommets9.push_back(Point(0,-3)); 
    Sommets9.push_back(Point(-1,-3));
    Obstacle N9 = ConstructObstacle(Sommets9);
    
    vector<Point> Sommets10;
    Sommets10.push_back(Point(-2,-3)); Sommets10.push_back(Point(-1,-3)); Sommets10.push_back(Point(-1,2)); 
    Sommets10.push_back(Point(-2,2));
    Obstacle N10 = ConstructObstacle(Sommets10);

    vector<Point> Sommets11;
    Sommets11.push_back(Point(-9,-1)); Sommets11.push_back(Point(-7,-1)); Sommets11.push_back(Point(-7,-2));
    Sommets11.push_back(Point(-6,-2)); Sommets11.push_back(Point(-6,-1)); Sommets11.push_back(Point(-5,-1));
    Sommets11.push_back(Point(-5,-2)); Sommets11.push_back(Point(-4,-2)); Sommets11.push_back(Point(-4,-1));
    Sommets11.push_back(Point(-3,2)); Sommets11.push_back(Point(-4,6)); Sommets11.push_back(Point(-9,0));
    Obstacle N11 = ConstructObstacle(Sommets11);

    vector<Point> Sommets12;
    Sommets12.push_back(Point(-10,1)); Sommets12.push_back(Point(-7,1)); Sommets12.push_back(Point(-7,2));
    Sommets12.push_back(Point(-10,2)); Sommets12.push_back(Point(-10,8)); Sommets12.push_back(Point(-12,4));
    Obstacle N12 = ConstructObstacle(Sommets12);

    vector<Point> Sommets13;
    Sommets13.push_back(Point(-9,4)); Sommets13.push_back(Point(-5,2)); Sommets13.push_back(Point(-5,8)); 
    Sommets13.push_back(Point(-7,8));
    Obstacle N13 = ConstructObstacle(Sommets13);

    vector<Point> Sommets14;
    Sommets14.push_back(Point(-4.5,4)); Sommets14.push_back(Point(-1,4)); Sommets14.push_back(Point(-1,8)); 
    Sommets14.push_back(Point(-4.5,8));
    Obstacle N14 = ConstructObstacle(Sommets14);

    vector<Point> Sommets15;
    Sommets15.push_back(Point(-2,5)); Sommets15.push_back(Point(0,5)); Sommets15.push_back(Point(0,6)); 
    Sommets15.push_back(Point(1,6)); Sommets15.push_back(Point(1,8));
    Obstacle N15 = ConstructObstacle(Sommets15);

    vector<Point> Sommets16;
    Sommets16.push_back(Point(5,3)); Sommets16.push_back(Point(5,5)); Sommets16.push_back(Point(6,2));
    Sommets16.push_back(Point(6,5)); Sommets16.push_back(Point(7,5)); Sommets16.push_back(Point(7,8));
    Sommets16.push_back(Point(5,8)); Sommets16.push_back(Point(4,4));
    Obstacle N16 = ConstructObstacle(Sommets16);

    vector<Point> Sommets17;
    Sommets17.push_back(Point(3,1)); Sommets17.push_back(Point(3,2.5)); Sommets17.push_back(Point(4.5,2.5)); 
    Sommets17.push_back(Point(4.5,5)); Sommets17.push_back(Point(1,1));
    Obstacle N17 = ConstructObstacle(Sommets17);

    vector<Point> Sommets18;
    Sommets18.push_back(Point(2,0.5)); Sommets18.push_back(Point(4.5,0.5)); Sommets18.push_back(Point(4.5,1.5)); 
    Sommets18.push_back(Point(2,1.5));
    Obstacle N18 = ConstructObstacle(Sommets18);

    vector<Point> Sommets19;
    Sommets19.push_back(Point(4,-2)); Sommets19.push_back(Point(9,-2)); Sommets19.push_back(Point(9,1));
    Sommets19.push_back(Point(8,1)); Sommets19.push_back(Point(8,-1)); Sommets19.push_back(Point(5,-1));
    Sommets19.push_back(Point(5,2)); Sommets19.push_back(Point(4,2));
    Obstacle N19 = ConstructObstacle(Sommets19);

    vector<Point> Sommets20;
    Sommets20.push_back(Point(7,2)); Sommets20.push_back(Point(9,2)); Sommets20.push_back(Point(9,5)); 
    Obstacle N20 = ConstructObstacle(Sommets20);

    vector<Point> Sommets21;
    Sommets21.push_back(Point(9.5,1)); Sommets21.push_back(Point(10,1)); Sommets21.push_back(Point(11,1)); 
    Sommets21.push_back(Point(11,4)); Sommets21.push_back(Point(12,5)); Sommets21.push_back(Point(11,7)); 
    Sommets21.push_back(Point(9,7)); Sommets21.push_back(Point(8,6)); Sommets21.push_back(Point(10,6)); 
    Sommets21.push_back(Point(10,2)); 
    Obstacle N21 = ConstructObstacle(Sommets21);

    vector<Point> Sommets22;
    Sommets22.push_back(Point(13,6)); Sommets22.push_back(Point(15,6)); Sommets22.push_back(Point(15,8)); 
    Obstacle N22 = ConstructObstacle(Sommets22);

    vector<Point> Sommets23;
    Sommets23.push_back(Point(12,-7)); Sommets23.push_back(Point(13,-7)); Sommets23.push_back(Point(13,-4)); 
    Sommets23.push_back(Point(14,-4)); Sommets23.push_back(Point(14,-3)); Sommets23.push_back(Point(15,-3)); 
    Sommets23.push_back(Point(15,-2)); Sommets23.push_back(Point(14,-2)); Sommets23.push_back(Point(14,1)); 
    Sommets23.push_back(Point(15,2)); Sommets23.push_back(Point(14,3)); Sommets23.push_back(Point(12,-1)); 
    Sommets23.push_back(Point(12,-2)); Sommets23.push_back(Point(11,-2.5)); Sommets23.push_back(Point(12,-3)); 
    Sommets23.push_back(Point(11,-3.5)); Sommets23.push_back(Point(12,-4)); Sommets23.push_back(Point(11,-4.5)); 
    Sommets23.push_back(Point(12,-5)); Sommets23.push_back(Point(11,-5.5)); Sommets23.push_back(Point(12,-6));  
    Obstacle N23 = ConstructObstacle(Sommets23);

    vector<Point> Sommets24;
    Sommets24.push_back(Point(6,-4)); Sommets24.push_back(Point(7,-4)); Sommets24.push_back(Point(7,-3)); 
    Sommets24.push_back(Point(6,-3)); 
    Obstacle N24 = ConstructObstacle(Sommets24);

    vector<Point> Sommets25;
    Sommets25.push_back(Point(4,-4)); Sommets25.push_back(Point(5,-4)); Sommets25.push_back(Point(5,-3)); 
    Sommets25.push_back(Point(4,-3)); 
    Obstacle N25 = ConstructObstacle(Sommets25);
    
    vector<Point> Sommets26;
    Sommets26.push_back(Point(5,-5)); Sommets26.push_back(Point(6,-5)); Sommets26.push_back(Point(6,-4)); 
    Sommets22.push_back(Point(5,-4)); 
    Obstacle N26 = ConstructObstacle(Sommets26);

    vector<Point> Sommets27;
    Sommets27.push_back(Point(7,-5)); Sommets27.push_back(Point(8,-5)); Sommets27.push_back(Point(8,-4)); 
    Sommets27.push_back(Point(7,-4)); 
    Obstacle N27 = ConstructObstacle(Sommets27);

    vector<Point> Sommets28;
    Sommets28.push_back(Point(6,-6)); Sommets28.push_back(Point(7,-6)); Sommets28.push_back(Point(7,-5)); 
    Sommets28.push_back(Point(6,-5)); 
    Obstacle N28 = ConstructObstacle(Sommets28);

    vector<Point> Sommets29;
    Sommets29.push_back(Point(4,-6)); Sommets29.push_back(Point(5,-6)); Sommets29.push_back(Point(5,-5)); 
    Sommets29.push_back(Point(4,-5)); 
    Obstacle N29 = ConstructObstacle(Sommets29);

    vector<Point> Sommets30;
    Sommets30.push_back(Point(5,-7)); Sommets30.push_back(Point(6,-7)); Sommets30.push_back(Point(6,-6)); 
    Sommets30.push_back(Point(5,-6)); 
    Obstacle N30 = ConstructObstacle(Sommets30);

    vector<Point> Sommets31;
    Sommets31.push_back(Point(7,-7)); Sommets31.push_back(Point(8,-7)); Sommets31.push_back(Point(8,-6)); 
    Sommets31.push_back(Point(7,-6)); 
    Obstacle N31 = ConstructObstacle(Sommets31);

    vector<Point> Sommets32;
    Sommets32.push_back(Point(1,-5)); Sommets32.push_back(Point(3,-5)); Sommets32.push_back(Point(3,-1));
    Sommets32.push_back(Point(2.5,-1)); Sommets32.push_back(Point(2.5,-3)); Sommets32.push_back(Point(1.5,-3));
    Sommets32.push_back(Point(1.5,-1)); Sommets32.push_back(Point(1,-1));
    Obstacle N32 = ConstructObstacle(Sommets32);

    vector <Point> arrivee; arrivee.push_back(Point(15,-8)); Obstacle A = ConstructObstacle(arrivee);
**/
    
