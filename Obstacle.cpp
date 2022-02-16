#include "Point.hpp"
#include "Arc.hpp"
#include "Obstacle.hpp"


Point Coor_Vecteur_Normale(const Point & S_1, const Point & S_2)
{
    Point P;
    P = S_1 | S_2;
    Point dir;
    // On utilise la matrice de rotation dans le sens horaire avec theta = Pi/2
    dir.x = P.y; 
    dir.y = - P.x;
    return dir;
}


vector<Point> Coor_Sommets_Normale(const Point & S_1, const Point & S_2)
{
    vector<Point> res; // vecteur de points qui contient nos deux coordonnées 
    Point S_milieu;
    S_milieu = (S_1 + S_2) / 2;
    Point debut;
    debut = S_milieu; // la 1ère coordonnée est le milieu de nos extrémités (normales centrées)
    res.push_back(debut);
    Point direction;
    direction = Coor_Vecteur_Normale(S_1, S_2); // la direction est donnée par la matrice de rotation
    Point fin;
    fin.x = S_milieu.x + direction.x;
    fin.y = S_milieu.y + direction.y;
    res.push_back(fin);
    return res;
}


bool ccw(const Point &A, const Point &B, const Point &C){
    return ((C.y-A.y) * (B.x-A.x)) > ((B.y-A.y) * (C.x-A.x));
}


bool intersect(const Point &A, const Point &B, const Point &C, const Point &D){
    return ccw(A,C,D) != ccw(B,C,D) and ccw(A,B,C) != ccw(A,B,D);
}



bool transfo(const Point & a, const Point & b, const Point & c)
{
    // On commence par calculer les coordonnées des normales entre les sommets a et b (P) puis b et c (Q)
    vector<Point> P;
    P = Coor_Sommets_Normale(a,b);
    vector<Point> Q;
    Q = Coor_Sommets_Normale(b,c);
    Point E1; Point E2;
    E1 = P[0] | P[1];
    E2 = Q[0] | Q[1];
    double angle;
    angle = E1.x * E2.y - E2.x * E1.y;
    if (angle > 0)
        return false; // transfo false => segment ab et bc convexe
    else
        return true; // transfo false => segment ab et bc concave
}


bool Obstacle::concave_convexe()
{
    if(this->nbr_sommets==1) return true; // ajout pour gestion facile point de départ et d'arrivée dans Graphe
    // si l'angle algébrique entre deux normales est < 0, l'angle est obtu donc les deux normales ne s'intersectent pas
    // il faut que tout couple de normales consécutives de notre obstacle vérifie cela pour que l'obstacle soit convexe
    int k = 0; // compteur pour pouvoir conclure à la fin des boucles
    for (int i = 0; i < this->nbr_sommets - 2; i++) 
    {
        if (transfo(this->Sommets[i], this->Sommets[i+1], this->Sommets[i+2]) == false)
            k += 1;
    }
    if (transfo(this->Sommets[this->nbr_sommets - 2], this->Sommets[this->nbr_sommets - 1], this->Sommets[0]) == false) 
        k += 1;
    if (transfo(this->Sommets[this->nbr_sommets - 1], this->Sommets[0], this->Sommets[1]) == false)
        k += 1; 
    if (k == this->nbr_sommets)
        return true;
    else
        return false;
}


list<Segment> Obstacle::constructionSeg()
{
    if (concave_convexe() == true) // on remplit la liste des segments valides en faisant le tour de l'obstacle
    {
        for(int i = 0; i < this->nbr_sommets -1; i++)
        {
            Segment var1(this->Sommets[i], this->Sommets[i+1]); 
            segValides.push_back(var1);
        }
        Segment var2(this->Sommets[this->nbr_sommets-1], this->Sommets[0]);
        segValides.push_back(var2);
    }
    else // on remplit la liste des segments valides en faisant le tour de l'obstacle et en considérant d'autres segmets valides dus à la concavité
    {
        for(int i = 0; i < this->nbr_sommets - 1; i++)
        {
            Segment var1(this->Sommets[i], this->Sommets[i+1]);
            segValides.push_back(var1);
        }
        Segment var2(this->Sommets[this->nbr_sommets-1], this->Sommets[0]);
        segValides.push_back(var2);
        for (int i = 0; i < this->nbr_sommets - 2; i++) 
        {
            if (transfo(this->Sommets[i], this->Sommets[i+1], this->Sommets[i+2]) == true)
            {
                Segment var3(this->Sommets[i], this->Sommets[i+2]);
                segValides.push_back(var3);
            }
        }
        if (transfo(this->Sommets[this->nbr_sommets - 2], this->Sommets[this->nbr_sommets - 1], this->Sommets[0]) == true) 
            {
                Segment var4(this->Sommets[this->nbr_sommets - 2], this->Sommets[0]);
                segValides.push_back(var4);
            }
        if (transfo(this->Sommets[this->nbr_sommets - 1], this->Sommets[0], this->Sommets[1]) == true)
            {
                Segment var5(this->Sommets[this->nbr_sommets - 1], this->Sommets[1]);
                segValides.push_back(var5);
            }
        
    }
    return segValides;
}
