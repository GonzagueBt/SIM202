#include "Graphe.hpp"


Graphe::Graphe(list<Obstacle> obst, Point x, Point y){
    depart = x;
    fin = y;
    list<Obstacle>::iterator its=obst.begin();
    Obstacle final= *its;
    its++;
    while(its!= obst.end()){ // on ajoute un par un les obstacles (on ajoute à la liste des segments les segments entre obstacles)
        final = sumObstacles(final, *its);
        its++;
    }
    vector<Point> dep;
    dep.push_back(x);
    Obstacle depart(dep, 1);
    final = sumObstacles(final, depart); //traitement des segments entre le point de départ et et les sommets du graphe
    depart.Sommets[0] = y;
    final = sumObstacles(final, depart);  //traitement des segments entre le point de fin et et les sommets du graphe
    graphe_ = final.segValides;
    nb_sommets = final.nbr_sommets;
}

Obstacle sumObstacles(Obstacle ob1, Obstacle ob2){
    vector<Point> pts;
    pts.reserve(ob1.nbr_sommets+ob2.nbr_sommets);
    for(int i=0; ob1.Sommets.size(); i++){
        if(!isIn(ob1.Sommets[i], pts)) pts.push_back(ob1.Sommets[i]);
    }

    list<Segment>::iterator its = ob2.segValides.begin();
    for(; its!= ob2.segValides.end(); its++) ob1.segValides.push_back(*its);
    for(int i=0; i<pts.size(); i++){
        for(int j=i+1; j<pts.size(); j++){
            its=ob1.segValides.begin();
            bool isValide = true; 
            for(; its!= ob1.segValides.end(); its++){ //on parcout tous les segments de l'obstacle 1
                if(intersect(pts[i], pts[j], its->a, its->b)){ // si intersection entre segment de ob1 et segment ij
                    isValide = false; // le segment ij est non valdie
                    break; //on arrete la vérif puisque sait deja que le segment est invalide
                } 
            }
            if(!isValide) break; // si le semgent est deja invalide, cela ne sert à rien de continuer la vérif
            // On fait la meme chose pour les semgents de l'obstacle 2
            its=ob2.segValides.begin(); 
            for(; its!= ob2.segValides.end(); its++){
                if(intersect(pts[i], pts[j], its->a, its->b)){
                    isValide = false;
                    break;
                } 
            }
            if(isValide){ // si le segment est toujorus valdie après les vérifications, on l'ajoute à la liste segValides
                Segment newSeg = Segment(pts[i], pts[j]);
                ob1.segValides.push_back(newSeg);
            }
        }
    }
    ob1.Sommets = pts;
    ob1.nbr_sommets = pts.size();
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
vector<vector<double> > initC(int nb){
    vector<vector<double> > c;
    vector<double> ligne(nb);
    for(int i=0; i<nb; i++){
        c.push_back(ligne);
    }
    //intitalisation de c
    for(int i=0; i<nb; i++){
        for(int j=0; j<nb; j++){
            if(i==j) c[i][j]=0;
            else c[i][j] = max;
        }
    }
    return c;
}


//Construction de la matrice
vector<vector<double> > buildMatrixC(Point * memory, Graphe g){
    int nb = g.nb_sommets;
    vector<vector<double> > c = initC(nb);
    //Point memory[nb];
    memory[0] = g.depart;
    memory[nb-1] = g.fin;
    int cpt=1;
    list<Segment>::iterator its = g.graphe_.begin();
    for(; its!= g.graphe_.end(); its++){
        int a = isIn(its->a, memory, nb);
        int b = isIn(its->b, memory, nb);
        if(b== -1){ 
            memory[cpt] = its->b;
            b = cpt;
            cpt++;
        }
        if(a== -1){
            memory[cpt] = its->a;
            a = cpt;
            cpt++;
        }
        c[a][b] = its->poid;
        c[b][a] = its->poid;
    }
    return c;
}

// renvoie l'index du point a dans la liste memory. Retourne -1 a n'est pas dans la liste
int isIn(Point a, Point * memory, int nb){
    for(int i=0; i<nb; i++){
        if(a==memory[i]) return i;
    }
    return -1;
}

//renvoie true si le point a est dans le vecteur de Point pts. Retourne false sinon
bool isIn(Point a, vector<Point> pts){
    for(int i=0; i<pts.size(); i++){
        if(a==pts[i]) return true;
    }
    return false;
}
