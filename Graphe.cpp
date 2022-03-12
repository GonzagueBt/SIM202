#include "Graphe.hpp"



Graphe::Graphe(list<Obstacle> obst, Point x, Point y){
    depart = x;
    fin = y;
    Obstacle final = constructionGraphe(obst, depart, fin);
    cout<<"ajout point de départ"<<endl;
    final = addPointObstacle(final, depart); 
    cout<<"ajout point de fin"<<endl;
    final = addPointObstacle(final, fin);  
    graphe_Obst = deleteSegCommun(final.segValides_contour);
    graphe_Autre = deleteSegCommun(final.segValides_reste);
    graphe_All = concateListe(graphe_Obst, graphe_Autre, true);
    nb_sommets = final.nbr_sommets - sommetsNonUsed(final.Sommets, graphe_All);
}


Obstacle constructionGraphe(list<Obstacle> obst, Point x, Point y){
    list<Obstacle>::iterator its=obst.begin();
    Obstacle& final= *its;
    if(obst.size()>0 && (!isOutside(x, *its) || !isOutside(y, *its))){
        cout<<"Point d'arrivée ou de départ à l'intérieur d'un obstacle, problème non résoluble"<<endl;
        abort();
    }
    if(obst.size()>1){ 
        its++;
        for(; its!= obst.end(); its++){
            if(!isOutside(x, *its) || !isOutside(y, *its)){
                cout<<"Point d'arrivée ou de départ à l'intérieur d'un obstacle, problème non résoluble"<<endl;
                abort();
            }
            final = assemblage2Obstsacles(final, *its);
        }
    }
    return final;
}

Obstacle addPointObstacle(Obstacle final, Point x){
    vector<Point> pt;
    pt.push_back(x);
    Obstacle depart(pt, 1);
    final = assemblage2Obstsacles(final, pt);
    return final;
}


Obstacle assemblage2Obstsacles(Obstacle& ob1, Obstacle ob2){
    Obstacle ob=ob1;
    auto its = ob2.segValides_reste.begin();
    for(; its!= ob2.segValides_reste.end(); its++) ob.segValides_reste.push_back(*its);
    its = ob2.segValides_contour.begin();
    for(; its!= ob2.segValides_contour.end(); its++) ob.segValides_contour.push_back(*its);   
    list<Segment> toDelete;
    list<Point> toDeleteP;
    if(ob2.nbr_sommets>1) ob1 = overLapObstacles(toDelete, toDeleteP, ob, ob1, ob2);

    for(int i=0; i< (int) ob1.Sommets.size(); i++){
        for(int j=0; j< (int) ob2.Sommets.size(); j++){
            auto its=ob1.segValides_contour.begin();
            bool isValide = true; 
            for(; its!= ob1.segValides_contour.end(); its++){
                if(intersect(ob1.Sommets[i], ob2.Sommets[j], its->a, its->b) || isIn(ob2.Sommets[j],ob1.Sommets) || isIn(ob1.Sommets[i],ob2.Sommets)){ // si intersection entre segment de ob1 et segment ij
                    isValide = false;
                    break;
                } 
            }
            if(!isValide) continue;
            its=ob2.segValides_contour.begin(); 
            for(; its!= ob2.segValides_contour.end(); its++){
                if(its->a==ob1.Sommets[i] || its->b==ob1.Sommets[i] || its->a==ob2.Sommets[j] || its->b==ob2.Sommets[j]) continue;
                if(intersect(ob1.Sommets[i], ob2.Sommets[j], its->a, its->b)){
                    isValide = false;
                    break;
                } 
            }
            if(!isOutside(ob1.Sommets[i], ob2) || !isOutside(ob2.Sommets[j], ob1)) isValide = false;
            if(isValide){
                Segment newSeg = Segment(ob1.Sommets[i], ob2.Sommets[j]);
                ob.segValides_reste.push_back(newSeg);
                cout<<"segment entre point "<<ob1.Sommets[i]<<" et "<<ob2.Sommets[j]<<" ajouté"<<endl;
            }
        }
    }
    auto it3 = toDelete.begin();
    for(; it3 != toDelete.end(); it3++){
        cout<<"Suppression segment "<<it3->a<<"," <<it3->b<<endl;
        ob1.deleteSegFromList(*it3);
        ob2.deleteSegFromList(*it3);
        ob.deleteSegFromList(*it3);
    }
    printSommet(ob.Sommets);
    printSegments(ob.segValides_contour);
    ob.Sommets = concateVectorPoints(ob1.Sommets, ob2.Sommets);
    ob.nbr_sommets = ob.Sommets.size();
    return ob;
}


//////////////////////////////////////////|------------------------------|///////////////////////////////////////////
//////////////////////////////////////////| GESTION OBSTACLES CHEVAUCHES |///////////////////////////////////////////
//////////////////////////////////////////|------------------------------|///////////////////////////////////////////

Obstacle overLapObstacles(list<Segment>& toDelete, list<Point>& toDeleteP, Obstacle& ob, Obstacle& ob1, Obstacle& ob2){
    cout<<"vérifications d'obstacles chevauchés"<<endl;
    auto it = ob1.segValides_contour.begin();
    auto it2 = ob2.segValides_contour.begin();
    it2++;
    for(; it!= ob1.segValides_contour.end();it++){
        for(; it2!= ob2.segValides_contour.end() ;it2++){
            if(intersect(*it, *it2)){
                toDelete = checkIntersectionSeg(toDelete, toDeleteP, *it, *it2, ob1, ob2, ob);
            }
        }
        it2 = ob2.segValides_contour.begin();
    }
    auto it4 = toDeleteP.begin();
    for(; it4 != toDeleteP.end(); it4++){
        deletePointFromVector(ob.Sommets, *it4);
        deletePointFromVector(ob1.Sommets, *it4);
        deletePointFromVector(ob2.Sommets, *it4);
        cout<<"point "<<*it4<<" supprimé"<<endl; 
    }
    return ob;
}


list<Segment> checkIntersectionSeg(list<Segment>& toDelete, list<Point>& toDeleteP, Segment A, Segment B, Obstacle& ob1, Obstacle& ob2, Obstacle& ob){
    Point inter = Intersction2Arcs(A,B);
    toDelete.push_back(B);
    toDelete.push_back(A);
    ob1.Sommets.push_back(inter);
    ob2.Sommets.push_back(inter);
    ob.nbr_sommets += 1;
    monitor1Point(toDelete,toDeleteP, A.a, A.b, inter, ob1, ob2, ob);
    monitor1Point(toDelete,toDeleteP, A.b, A.a, inter, ob1, ob2, ob);
    monitor1Point(toDelete,toDeleteP, B.a, B.b, inter, ob2, ob1, ob);
    monitor1Point(toDelete,toDeleteP, B.b, B.a, inter, ob2, ob1, ob);
    return toDelete;
}


void monitor1Point(list<Segment>& toDelete, list<Point>& toDeleteP, Point x, Point oppose, Point inter, Obstacle ob1, Obstacle ob2, Obstacle& ob){
    Segment newOne(x,inter);
    if(!isOutside(x,ob2)){
        if(! isIn(x, toDeleteP)) toDeleteP.push_back(x);       
    }
    Segment autre(oppose, inter);
    auto it = ob2.segValides_contour.begin();
    for(; it != ob2.segValides_contour.end() ; it++){
        if(isOutside(oppose, ob2) && intersect(*it, autre)) return; //{ cout<<"tu paniques la ?"<<endl; toDelete= checkIntersectionSeg(toDelete, toDeleteP, autre, *it, ob1, ob2, ob); }
    }
    if(isOutside(x,ob2)){
        ob.segValides_contour.push_back(newOne);
    }
    //return toDelete;
}




