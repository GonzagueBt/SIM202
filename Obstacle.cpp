#include "Point.hpp"
#include "Arc.hpp"
#include "Obstacle.hpp"
#include <list>
extern ostream out;

int main(){
    Point a(2,2);
    Point b(5,2);
    Point c(6,3);
    Point * liste;
    liste = new Point [3];
    liste[0] = a;
    liste[1] = b;
    liste[2] = c;
    Obstacle test = Obstacle(liste, 3);
    Segment test2(a,b);

    test.segValides.push_back(test2);
}

Point Obstacle::operator[](int i) const
{
  return Sommets[i];
}

Point Coor_Vecteur_normale(const Point & S_1, const Point & S_2)
{
    Point P;
    P = S_1 | S_2;
    Point dir;
    // On utilise la matrice de rotation dans le sens horaire avec theta = Pi/2
    dir.x = P.y; 
    dir.y = - P.x;
    return dir;
}


Point * Coor_Sommets_Normale(const Point & S_1, const Point & S_2)
{
    Point * res = new Point[2]; // tableau qui contient nos deux coordonnées 
    Point S_milieu;
    S_milieu = (S_1 + S_2) / 2;
    Point debut;
    debut = S_milieu; // la 1ère coordonnée est le milieu de nos extrémités (normales centrées)
    res[0] = debut;
    Point direction;
    direction = Coor_Vecteur_normale(S_1, S_2); // la direction est donnée par la matrice de rotation
    Point fin;
    fin.x = S_milieu.x + direction.x;
    fin.y = S_milieu.y + direction.y;
    res[1] = fin;
    return res;
}

double Produit_Scalaire(const Point & a, const Point & b)
{
    double res;
    res = (a.x * b.x) + (a.y * b.y);
    return res;
}

double transfo(const Point & a, const Point & b, const Point & c)
{
    // on commence par calculer les coordonnées des normales entre les sommets a et b (P) puis b et c (Q)
    Point * P;
    P = Coor_Sommets_Normale(a,b);
    Point * Q;
    Q = Coor_Sommets_Normale(b,c);
    // on met ces coordonnées sous la forme de coordonnées vectoreilles puis on applique le pdt scalaire
    // pour connaitre l'angle algébrique entre nos deux normales
    Point var1;
    var1 = P[0] | P[1];
    Point var2;
    var2 = Q[0] | Q[1];
    return Produit_Scalaire(var1,var2);
}


bool Obstacle::concave_convexe(const Obstacle &Obs)
{
    if(Obs.nbr_sommets==1) return true; // ajout pour gestion facile point de départ et d'arrivée dans Graphe
    // si l'angle algébrique entre deux normales est < 0, l'angle est obtu donc les deux normales ne s'intersectent pas
    // il faut que tout couple de normales consécutives de notre obstacle vérifie cela pour que l'obstacle soit convexe
    int k = 0; // compteur pour pouvoir conclure à la fin des boucles
    for (int i = 0; i < (Obs.nbr_sommets - 2); i++) 
    {
        if (transfo(Obs[i], Obs[i+1], Obs[i+2]) < 0)
            k += 1;
    }
    if (transfo(Obs[Obs.nbr_sommets - 2], Obs[Obs.nbr_sommets - 1], Obs[0]) < 0) 
        k+=1;
    if (transfo(Obs[Obs.nbr_sommets - 1], Obs[0], Obs[1]) < 0)
        k+=1;
    if (k == nbr_sommets)
        return true;
    else if (k != nbr_sommets)
        return false;
    
}


Point_et_Indice Trouver_Sommet_le_plus_proche(const Point &A, const Obstacle &Obs)
{
    Point_et_Indice res;
    Point Sommet_le_plus_proche;
    Sommet_le_plus_proche = Obs[0]; // de base c'est Obs[0] le sommet le plus proche, sera peut-être changé pdt la boucle
    int i;
    int indice_du_sommet_le_plus_proche = 0; // indice correspondant à Obs[0] est i = 0
    res.i = indice_du_sommet_le_plus_proche;
    int n = Obs.nbr_sommets;
    for(i = 1; i < n; i++)
        if ( ((abs(A.x - Obs[i-1].x)) >= abs((A.x - Obs[i].x))) && ((abs(A.y - Obs[i-1].y)) >= abs((A.y - Obs[i].y))) )
            Sommet_le_plus_proche = Obs[i];
            indice_du_sommet_le_plus_proche = i;
    // si un sommet plus proche a été trouvé pdt la boucle, alors il prend la place de Obs[0]
    // on conserve aussi son indice
    res.i = indice_du_sommet_le_plus_proche;
    res.point = Sommet_le_plus_proche;
    return res;
}

bool Obstacle::inte_exte(const Point & P, const Obstacle &Obs)
{   
    if(Obs.nbr_sommets==1 && Obs.Sommets[0]!=P) return true; // ajout pour gestion facile point de départ et d'arrivée dans Graphe
    // on commence par chercher le sommet le plus proche de P
    Point_et_Indice Q;
    Q = Trouver_Sommet_le_plus_proche(P, Obs);
    Point R;
    R = Q.point;
    Point var1;
    var1 = R | P;
    Point * N;
    N = Coor_Sommets_Normale(Obs[Q.i], Obs[Q.i + 1]);
    Point var2;
    var2 = N[0] | N[1];
    double res;
    res = Produit_Scalaire(var1, var2); 
    // si le pdt scalaire entre la normal entre deux segments ( d'éxtrémités S_i et S_(i+1) et P et S_i (S_i étant le sommet le plus proche))
    // positive alors le point P est extérieur
    if (res >= 0)
        return true;
    else
        return false;
}


list<Segment> Obstacle::constructionSeg(Point *x, int n)
{
    //segValides.push_back(Segment a);
    /*if (concave_convexe(Obs) == true)
        // remplir la list segment en faisant le tour de l'obstacle
    else
        // réfélechir */
}

Obstacle::Obstacle(Point *x, int n){
    nbr_sommets = n;
    Sommets = x;
    segValides = constructionSeg(x,n);

}




