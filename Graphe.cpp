#include "Graphe.hpp"


Graphe::Graphe(list<Obstacle> obst, Point x, Point y){
    depart = x;
    fin = y;
    list<Obstacle>::iterator its=obst.begin();
    Obstacle final= *its;
    cout<<"premier obstacle"<<endl;
    int cpt=1;
    if(obst.size()!=1){ 
        its++; //gestion cas un seul obstacle
        cout<<"début boucle "<<endl;
        for(; its!= obst.end(); its++){// on ajoute un par un les obstacles (on ajoute à la liste des segments les segments entre obstacles)
            cout<<"ajout d'un obstacle :"<<cpt<<endl;
            final = sumObstacles(final, *its);
            cout<<"ajout obstacle réussi !"<<endl;
            cpt++;
        }
    }
    cout<<"obstacles tous assemblés"<<endl;
    printSegValides(final.segValides);
    vector<Point> dep;
    dep.push_back(x);
    Obstacle depart(dep, 1);
    cout<<"Ajout point de départ"<<endl;
    final = sumObstacles(final, depart); //traitement des segments entre le point de départ et et les sommets du graphe
    cout<<"point de départ ajouté"<<endl;
    depart.Sommets[0] = y;
    cout<<"ajout point de fin"<<endl;
    final = sumObstacles(final, depart);  //traitement des segments entre le point de fin et et les sommets du graphe
    cout<<"point de fin ajouté"<<endl;
    graphe_ = final.segValides;
    nb_sommets = final.nbr_sommets;
}

Obstacle sumObstacles(Obstacle ob1, Obstacle ob2){
    vector<Point> pts;
    cout<<"intialisation liste de points"<<endl;
    pts.reserve(ob1.nbr_sommets+ob2.nbr_sommets);
    cout<<"nombre de sommets totale maximum : "<<ob1.nbr_sommets+ob2.nbr_sommets<<endl;
    for(int i=0; i< (int) ob1.Sommets.size(); i++){
        pts.push_back(ob1.Sommets[i]);
    }
    for(int i=0; i< (int) ob2.Sommets.size(); i++){
        if(!isIn(ob2.Sommets[i], pts)) pts.push_back(ob2.Sommets[i]);
    }
    cout<<"nombre de sommets totale après suppression des doubles : "<<pts.size()<<endl;
    cout<<"liste de points des 2 obstacles construites"<<endl;
    list<Segment>::iterator its = ob2.segValides.begin();
    for(; its!= ob2.segValides.end(); its++) ob1.segValides.push_back(*its);
    printSegValides(ob1.segValides); ////////////////////////////////////////////////////////////////////////////////////////////////
    cout<<"segments valides des 2 obstacles réunis ("<<ob1.segValides.size()<<")"<<endl;
    for(int i=0; i< (int) ob1.Sommets.size(); i++){
        for(int j=0; j< (int) ob2.Sommets.size(); j++){
            cout<<"je fais le sommet : "<<ob1.Sommets[i]<<" avec le sommet : "<<ob2.Sommets[j]<<endl;
            its=ob1.segValides.begin();
            bool isValide = true; 
            for(; its!= ob1.segValides.end(); its++){ //on parcout tous les segments de l'obstacle 1
                //Obligé de vérif si le segment que l'on parcours n'a pas un de ces 2 sommets égales au sommet que l'on test
                //pour créer un segment, sinon l'algo d'intersection va considérer que il y a une intersection parce que sommet commun
                if(its->a==ob1.Sommets[i] || its->b==ob1.Sommets[i] || its->a==ob2.Sommets[j] || its->b==ob2.Sommets[j]) continue;
                if(intersect(ob1.Sommets[i], ob2.Sommets[j], its->a, its->b)){ // si intersection entre segment de ob1 et segment ij
                    if(ob1.Sommets[i].x==2 && ob1.Sommets[i].y==3){
                        cout<<"intersect avec l'arc : ("<<its->a<<", "<<its->b<<")"<<endl;
                    }
                    isValide = false; // le segment ij est non valdie
                    break; //on arrete la vérif puisque sait deja que le segment est invalide
                } 
            }
            if(!isValide) continue; // si le semgent est deja invalide, cela ne sert à rien de continuer la vérif
            // On fait la meme chose pour les semgents de l'obstacle 2
            its=ob2.segValides.begin(); 
            for(; its!= ob2.segValides.end(); its++){
                if(its->a==ob1.Sommets[i] || its->b==ob1.Sommets[i] || its->a==ob2.Sommets[j] || its->b==ob2.Sommets[j]) continue;
                if(intersect(ob1.Sommets[i], ob2.Sommets[j], its->a, its->b)){
                    isValide = false;
                    break;
                } 
            }
            if(isValide){ // si le segment est toujorus valdie après les vérifications, on l'ajoute à la liste segValides
                Segment newSeg = Segment(ob1.Sommets[i], ob2.Sommets[j]);
                ob1.segValides.push_back(newSeg);
                cout<<"segment entre point "<<ob1.Sommets[i]<<" et "<<ob2.Sommets[j]<<" ajouté"<<endl;
            }
        }
    }
    ob1.Sommets = pts;
    ob1.nbr_sommets = pts.size();
    return ob1;
}

void printSegValides(list<Segment> liste){
    cout<<"Liste des segments valides du graphe : "<<endl;
    list<Segment>::iterator its = liste.begin();
    for(; its!= liste.end(); its++){
        cout<<"("<<its->a<<","<<its->b<<")  ";
    }
    cout<<endl;
}
////////////////////////////////////////////////////////////


/**vector<vector<double> > initC(int nb){
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
}**/


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

void printMatricC(vector<vector<double> > c, Point * memory, int nb){
    cout<<"Matrice C : "<<endl;
    for(int i=0; i<nb; i++){
        cout<<memory[i]<<" ";
    }
    cout<<endl;
    for(int i=0; i< (int) c.size(); i++){
        for(int j=0; j < (int) c[0].size(); j++){
            cout<<c[i][j]<< " ";
        }
        cout<<endl;
    }
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
    for(int i=0; i< (int) pts.size(); i++){
        if(a==pts[i])return true; 
    }
    return false;
}
