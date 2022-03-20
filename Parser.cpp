#include "Parser.hpp"
ofstream out;

void parserGraphe(Graphe g, list<Point> chemin){
    out.open("Graphe.txt");  
    out<< g.graphe_Autre.size()<<endl;
    out<< g.graphe_Obst.size()<<endl;
    out<<g.nb_sommets<<endl;
    list<Segment>::iterator  its = g.graphe_Autre.begin();
    for(; its!= g.graphe_Autre.end(); its++){
        out<< its->a.x<<" "<<its->a.y<<" "<<its->b.x<<" "<<its->b.y<<endl;
    }
    its = g.graphe_Obst.begin();
    for(; its!= g.graphe_Obst.end(); its++){
        out<< its->a.x<<" "<<its->a.y<<" "<<its->b.x<<" "<<its->b.y<<endl;
    }
    out<< chemin.size()<<endl;
    list<Point>::iterator it = chemin.begin();
    for(;it !=chemin.end(); it++){
        out<<it->x<<" "<<it->y<<endl;
    }
    out.close();
}

void parserObstacle(Graphe g, list<Point> chemin)
{
    out.open("trajectoire.txt");
    out<< g.graphe_Obst.size()<<endl;
    out<<g.nb_sommets<<endl;
    auto its = g.graphe_Obst.begin();
    for(; its!= g.graphe_Obst.end(); its++){
        out<< its->a.x<<" "<<its->a.y<<" "<<its->b.x<<" "<<its->b.y<<endl;
    }
    out<< chemin.size()<<endl;
    list<Point>::iterator it = chemin.begin();
    for(;it !=chemin.end(); it++){
        out<<it->x<<" "<<it->y<<endl;
    }
    out.close();
}

void parserObstacles(list<Obstacle> l_obs)
{
    out.open("obstacles.txt");
    out<< l_obs.size()<<endl; // nombre d'obstacles
    list<Obstacle>::iterator itl = l_obs.begin();
    for(; itl!=l_obs.end(); itl++){ // on parcours les obstacles
        out<<itl->nbr_sommets<<endl;
        list<Segment>::iterator its = itl->segValides_contour.begin();
        for(; its!=itl->segValides_contour.end(); its++){ // on parcours les sommets de l'obstacle
            out<< its->a.x << " "<< its->a.y<<" "<<its->b.x<<" "<<its->b.y<<endl;
        }
    }
    out.close();
}

void parserConcave(Obstacle obs)
{
    out.open("Concave.txt");
    out<< obs.segValides_contour.size()<<endl; // nombre de segments formant l'obstacle
    list<Segment>::iterator itl = obs.segValides_contour.begin();
    for(; itl!=obs.segValides_contour.end(); itl++){
        out<< itl->a.x << " "<< itl->a.y<<" "<<itl->b.x<<" "<<itl->b.y<<endl;
        }
    out<< obs.segValides_reste.size()<<endl;
    list<Segment>::iterator its = obs.segValides_reste.begin();
    for(; its!=obs.segValides_reste.end(); its++){
        out<< its->a.x << " "<< its->a.y<<" "<<its->b.x<<" "<<its->b.y<<endl;
        }
    out.close();
}


vector<Point> affichage_normale(Obstacle Ob)
{
    vector<Point> res;
    for(int i = 0; i< Ob.nbr_sommets-1; i++)
    {
        vector<Point> ajoute = Coor_Sommets_Normale(Ob.Sommets[i], Ob.Sommets[i+1]);
        res.push_back(ajoute[0]);
        res.push_back(ajoute[1]);
    }
    vector<Point> dernier = Coor_Sommets_Normale(Ob.Sommets[Ob.nbr_sommets - 1],Ob.Sommets[0]);
    res.push_back(dernier[0]);
    res.push_back(dernier[1]);
    return res;
}

// Cr�e un fichier avec les coordonn�es 1 obstacle et ses normales
void parserNormales(Obstacle obs)
{
    vector<Point> normales = affichage_normale(obs);
    out.open("Normale.txt");
    out<< obs.nbr_sommets<<endl; // nombre de sommets
    list<Segment>::iterator itl = obs.segValides_contour.begin();
    for(; itl!=obs.segValides_contour.end(); itl++){ // on parcours les sommets
        out<< itl->a.x << " "<< itl->a.y<<" "<<itl->b.x<<" "<<itl->b.y<<endl;
        }
    out<< normales.size()<<endl; // nombre de normales
    vector<Point>::iterator its = normales.begin();
    for(; its!=normales.end(); its++){ // on parcours les normales
        out<< its->x << " "<< its->y<<endl;
        }
    out.close();
}