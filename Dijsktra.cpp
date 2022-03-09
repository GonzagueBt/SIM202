#include "Dijsktra.hpp"
#define max INT_MAX


void Dijsktra(int N, vector<vector<double> > c, double *l, double *p){
    vector<int> S;
    vector<int> T;
    S.push_back(0); 
    // Initialisation de l et p //
    for(int i=0; i<N; i++){
        l[i]=c[0][i];
        if(i>0 && c[0][i]< max) p[i]=0;
        else  p[i]=-1;

        if(i>0) T.push_back(i);
    }

    while(!T.empty()){
        int min = max;
        int pt = 0;
        vector<int>::iterator its=T.begin();
        for(; its!= T.end(); its++){ 
            if (l[*its]< min){
                min = l[*its];
                pt = *its;
            }
        } 
        S.push_back(pt);
        /// obliger de reparcourir T pour supprimer le point pt choisi : Could Be Better
        its=T.begin();
        for(; its!= T.end(); its++){ 
            if(*its==pt){
                T.erase(its);
                break;
            }
        }
        its=T.begin();
        for (; its!= T.end();its++){ 
            if( l[*its]>(l[pt]+c[pt][*its])){
                l[*its] = l[pt]+c[pt][*its];
                p[*its]= pt;
            }
        }
    }
    // Dijkstra fini
    cout<<"l={";
    for(int i=0; i<N; i++) cout<<l[i]<<" ";
    cout<<"}"<<endl;
    cout<<"p={";
    for(int i=0; i<N; i++) cout<<p[i]<<" ";
    cout<<"}"<<endl;
}

vector<vector<double> > initC(int nb){
    vector<vector<double> > c;
    vector<double> ligne(nb);
    for(int i=0; i<nb; i++){
        c.push_back(ligne);
    }
    for(int i=0; i<nb; i++){
        for(int j=0; j<nb; j++){
            if(i==j) c[i][j]=0;
            else c[i][j] = max;
        }
    }
    return c;
}

vector<vector<double> > buildMatrixC(Point * memory, Graphe g){
    int nb = g.nb_sommets;
    vector<vector<double> > c = initC(nb);
    memory[0] = g.depart;
    memory[nb-1] = g.fin;
    int cpt=1;
    list<Segment>::iterator its = g.graphe_All.begin();
    for(; its!= g.graphe_All.end(); its++){
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



list<Point> cheminFinale(Point * memory, double * p, int nb){
    list<Point> chemin;
    chemin.push_front(memory[nb-1]);
    int index = (int) p[nb-1];
    while(p[index]!= -1){
        chemin.push_front(memory[index]);
        index = (int) p[index];
    }
    chemin.push_front(memory[0]);
    return chemin;
}

void printMatricC(vector<vector<double> > c, Point * memory, int nb){
    cout<<"Matrice C : "<<endl;
    for(int i=0; i<nb; i++){
        cout<<memory[i]<<" ";
    }
    cout<<endl;
    for(int i=0; i< (int) c.size(); i++){
        for(int j=0; j < (int) c[0].size(); j++){
            if(c[i][j]>=2.14748e+09) cout<<"max"<<" ";
            else cout<<c[i][j]<<" ";
        }
        cout<<endl;
    }
}

