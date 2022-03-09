#include "Point.hpp"
#include "Arc.hpp"
#include "Obstacle.hpp"


bool Obstacle::concave_convexe(){
    if(this->nbr_sommets==1) return true;
    // si l'angle algébrique entre deux normales est < 0, l'angle est obtu donc les deux normales ne s'intersectent pas
    // il faut que tout couple de normales consécutives de notre obstacle vérifie cela pour que l'obstacle soit convexe
    int k = 0; // compteur pour pouvoir conclure à la fin des boucles
    for (int i = 0; i < this->nbr_sommets - 2; i++) {
        if (transfo(this->Sommets[i], this->Sommets[i+1], this->Sommets[i+2]) == false) k += 1;
    }
    if(transfo(this->Sommets[this->nbr_sommets - 2], this->Sommets[this->nbr_sommets - 1], this->Sommets[0]) == false) k += 1;
    if (transfo(this->Sommets[this->nbr_sommets - 1], this->Sommets[0], this->Sommets[1]) == false) k += 1; 
    if (k == this->nbr_sommets) return true;
    return false;
}

void Obstacle::constructionSeg(){
    if (concave_convexe() == true){ // on remplit la liste des segments valides en faisant le tour de l'obstacle
        for(int i = 0; i < this->nbr_sommets -1; i++){
            Segment var1(this->Sommets[i], this->Sommets[i+1]); 
            segValides_contour.push_back(var1);
        }
        Segment var2(this->Sommets[this->nbr_sommets-1], this->Sommets[0]);
        segValides_contour.push_back(var2);
    }
    else{ // on remplit la liste des segments valides en faisant le tour de l'obstacle et en considérant d'autres segmets valides dus à la concavité
        for(int i = 0; i < this->nbr_sommets - 1; i++){
            Segment var1(this->Sommets[i], this->Sommets[i+1]);
            segValides_contour.push_back(var1);
        }
        Segment var2(this->Sommets[this->nbr_sommets-1], this->Sommets[0]);
        segValides_contour.push_back(var2);
        for(int i = 0; i < this->nbr_sommets-1; i++){
            for(int j = i + 1; j < this->nbr_sommets; j++){
                Segment arete(this->Sommets[i],this->Sommets[j]);
                if(isIn(arete, segValides_contour)) continue;
                auto it = this->segValides_contour.begin();
                bool memory = true;
                for(; it != this->segValides_contour.end(); it++){
                    if((intersect(arete, *it) && (arete.a!= it->a && arete.a!= it->b && arete.b!= it->a && arete.b!= it->b))){
                        memory = false;
                    }
                }
                if(memory){
                    Point x = (this->Sommets[i]+this->Sommets[j])/2;
                    if(isOutside(x, *this) && !isIn(arete, this->segValides_reste)){
                        this->segValides_reste.push_back(arete);
                    }
                }
            }
        }
    }
}

void Obstacle::deleteSegContour(Segment seg){
    auto it = segValides_contour.begin();
    for(; it!= segValides_contour.end(); it++){
        if(*it==seg){
            segValides_contour.erase(it);
            return;
        }
    }
}

Obstacle ConstructObstacle(vector<Point> V){
    Obstacle Obs(V, V.size());
    Obs.constructionSeg();
    return Obs;
}

Point Coor_Vecteur_Normale(const Point & S_1, const Point & S_2){
    Point P = S_1 | S_2;
    Point dir(P.y, -P.x);
    // On utilise la matrice de rotation dans le sens horaire avec theta = Pi/2
    return dir;
}


vector<Point> Coor_Sommets_Normale(const Point & S_1, const Point & S_2){
    vector<Point> res; // vecteur de points qui contient nos deux coordonnées 
    Point S_milieu = (S_1 + S_2) / 2;
    Point debut = S_milieu; // la 1ère coordonnée est le milieu de nos extrémités (normales centrées)
    res.push_back(debut);
    Point direction = Coor_Vecteur_Normale(S_1, S_2); // la direction est donnée par la matrice de rotation
    Point fin(S_milieu.x + direction.x, S_milieu.y + direction.y);
    res.push_back(fin);
    return res;
}


bool transfo(const Point & a, const Point & b, const Point & c){
    vector<Point> P = Coor_Sommets_Normale(a,b);
    vector<Point> Q = Coor_Sommets_Normale(b,c);
    Point E1 = P[0] | P[1];
    Point E2 = Q[0] | Q[1];
    double angle = E1.x * E2.y - E2.x * E1.y;
    if (angle > 0) return false; // transfo false => segment ab et bc convexe
    return true; // transfo false => segment ab et bc concave
}


//renvoie true si le point x est à l'extérieur OU sur un coté de l'obstacle
//renvoie false si le point est à l'intérieur strictement du polygone
bool isOutside(Point x, Obstacle ob){
    Point y(x.x, INT_MAX);
    int cpt = 0;
    list<Segment>::iterator its = ob.segValides_contour.begin();
    for(; its!= ob.segValides_contour.end(); its++){
        if(intersect(its->a, its->b, x, y)){
            cpt++;
        }
    }
    if(cpt%2 == 0) return true;
    else{
        //on refait une deuxieme fois le test avec une demi-droite horizontal pour gérer d'éventuel erreur quand x se trouve sur 
        // un coté de l'obstacle
        Point y(INT_MAX, x.y);
        cpt = 0;
        list<Segment>::iterator its = ob.segValides_contour.begin();
        for(; its!= ob.segValides_contour.end(); its++){
            if(intersect(its->a, its->b, x, y)){
                cpt++;
            }
        }
        if(cpt%2 == 0) return true;
    }
   return false;
}


//////////////////////////////// INTERSECTION DE 2 POINTS //////////////////////////////////
bool ccw(const Point &A, const Point &B, const Point &C){ return ((C.y-A.y) * (B.x-A.x)) > ((B.y-A.y) * (C.x-A.x));}
bool intersect(const Point &A, const Point &B, const Point &C, const Point &D){
    if(A==C || A==D || B==C || B==D) return false;
    return ccw(A,C,D) != ccw(B,C,D) and ccw(A,B,C) != ccw(A,B,D);}
bool intersect(const Segment A, const Segment B){ return intersect(A.a, A.b, B.a, B.b);}




