#include "Arc.hpp"
#include <vector>
#include <iostream>

// N nombre de sommets du graphe 
//c  : matrice des poids du graphe (cij et le poid de l'arrete ij)
// S={1} à l'intialisation
// T=liste des autres sommets
//les sommets sont considérés nommées de 0 à n, 0 étant systématiquement le sommet de départ
// Exemple : cout de l'arrete 01 = c[0][1]

void Dijsktra(int N, double c[5][5], double *l, double *p){
    vector<int> S;
    vector<int> T;
    S.push_back(0); 
    // Initialisation de l et p //
    for(int i=0; i<N; i++){
        l[i]=c[0][i];
        if(i>0 && c[0][i]< INFINITY) p[i]=0;
        else  p[i]=-1;

        if(i>0) T.push_back(i); // On rempli T
    }
    // Fin initialisation de l et p //

    while(!T.empty()){ //Tant que liste T n'est pas vide
        // Recherche du point pt de T tel que l[pt] est minimum //
        int min = INFINITY; //intialise la mémoire de la recherche
        int pt = 0;
        vector<int>::iterator its=T.begin(); // On parcourt T avec un iterator
        for(; its!= T.end(); its++){ 
            if (l[*its]< min){ // si l[point visité] est inférieur à l[point mémoire]
                min = l[*its]; //on garde ce point visité en mémoire
                pt = *its;
            }
        } 

        S.push_back(pt); //On ajoute le point pt à S
        /// obliger de reparcourir T pour supprimer le point pt choisi : pas optimal ///
        its=T.begin();
        for(; its!= T.end(); its++){ 
            if(*its==pt){
                T.erase(its); // On retir le point pt de T /////////////////////////////////
                break;
            }
        }

        its=T.begin(); // On parcourt T avec un iterator
        for (; its!= T.end();its++){ 
            if( l[*its]>(l[pt]+c[pt][*its])){ //si le cout jusqu'a pt plus le cout de l'arrete pt-its est inférieur au cout minimal
                l[*its] = l[pt]+c[pt][*its]; // nouveau cout minimal pour chemin de 0 à its
                p[*its]= pt; // nouveau prédecesseur pour its : pt
            }
        }
    }
}


int main(){
    //Exemple de l'énoncé avec 5 points
    double c[5][5] = {
        {0, 15, INFINITY, INFINITY, 4},
        {INFINITY, 0, INFINITY, INFINITY, INFINITY}, 
        {INFINITY, 3, 0, 2, INFINITY}, 
        {10, 3, INFINITY, 0, INFINITY}, 
        {INFINITY, INFINITY, 7, 5, 0}};
    int N=5;
    double l[N];
    double p[N];
    Dijsktra(N, c, l, p);

    cout<<"l={";
    for(int i=0; i<N; i++){
        cout<<l[i]<<" ";
    }
    cout<<"}"<<endl;
    cout<<"p={";
    for(int i=0; i<N; i++){
        cout<<p[i]<<" ";
    }
    cout<<"}"<<endl;

    return 0;
}