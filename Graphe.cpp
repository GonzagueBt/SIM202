#include "Graphe.hpp"



Graphe::Graphe(list<Obstacle> obst, Point x, Point y){
    depart = x;
    fin = y;
    Obstacle final = constructionGraphe(obst, depart, fin);
    final = addPointObstacle(final, depart); 
    final = addPointObstacle(final, fin);  
    graphe_Obst = deleteSegCommun(final.segValides_contour);
    graphe_Autre = deleteSegCommun(final.segValides_reste);
    graphe_All = concateListe(graphe_Obst, graphe_Autre, true);
    nb_sommets = final.nbr_sommets - sommetsNonUsed(final.Sommets, graphe_All);
}


Obstacle constructionGraphe(list<Obstacle> obst, Point x, Point y){
    list<Obstacle>::iterator its=obst.begin();
    Obstacle final= *its;
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


Obstacle assemblage2Obstsacles(Obstacle ob1, Obstacle ob2){
    Obstacle ob=ob1;
    auto its = ob2.segValides_reste.begin();
    for(; its!= ob2.segValides_reste.end(); its++) ob.segValides_reste.push_back(*its);
    its = ob2.segValides_contour.begin();
    for(; its!= ob2.segValides_contour.end(); its++) ob.segValides_contour.push_back(*its);   
    ob1 = overLapObstacles(ob, ob1, ob2);

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
    ob.Sommets = concateVectorPoints(ob1.Sommets, ob2.Sommets);
    ob.nbr_sommets = ob.Sommets.size();
    return ob;
}


//////////////////////////////////////////|------------------------------|///////////////////////////////////////////
//////////////////////////////////////////| GESTION OBSTACLES CHEVAUCHES |///////////////////////////////////////////
//////////////////////////////////////////|------------------------------|///////////////////////////////////////////

Obstacle overLapObstacles(Obstacle& ob, Obstacle& ob1, Obstacle& ob2){
    cout<<"vérifications d'obstacles chevauchés"<<endl;
    auto it = ob1.segValides_contour.begin();
    auto it2 = ob1.segValides_contour.begin();
    it2++;
    list<Segment> toDelete;
    for(; it!= ob1.segValides_contour.end();it++){
        for(; it2!= ob1.segValides_contour.end() ;it2++){
            if(it->a==it2->a || it->b==it2->a || it->a==it2->b || it->b==it2->b) continue;
            if(intersect(*it, *it2)){
                toDelete = checkIntersectionSeg(toDelete, *it, *it2, ob1, ob2, ob);
            }
        }
        it2 = ob1.segValides_contour.begin();
    }
    cout<<ob1.nbr_sommets<<endl;
    printSommet(ob1.Sommets);
    printSegments(ob1.segValides_contour);
    auto it3 = toDelete.begin();
    for(; it3 != toDelete.end(); it3++){
        cout<<"Suppression segment "<<it3->a<<"," <<it3->b<<endl;
        ob1.deleteSegFromList(*it3);
        ob2.deleteSegFromList(*it3);
        ob.deleteSegFromList(*it3);
    }
    return ob;
}


list<Segment> checkIntersectionSeg(list<Segment>& toDelete, Segment A, Segment B, Obstacle& ob1, Obstacle& ob2, Obstacle& ob){
    Point inter = Intersction2Arcs(A,B);
    if(A.a==inter || A.a==inter || A.b==inter || A.b==inter) return toDelete; // si l'intersection des segments et sur le somemt à tous les 2, tous les points sont segValides_reste
    if(isIn(A.a, ob1.Sommets) &&  !isOutside(A.a, ob2) && !isIn(A, toDelete)){ 
        toDelete = monitorInstersctSeg(toDelete, A.b, inter, B, A, ob2, ob1, ob);
    }
    else if(isIn(A.b, ob1.Sommets) &&  !isOutside(A.b, ob2) && !isIn(A, toDelete)){
        toDelete = monitorInstersctSeg(toDelete, A.a, inter, B, A, ob2, ob1, ob);
    }
    else if(isIn(B.a, ob1.Sommets) &&  !isOutside(B.a, ob2) && !isIn(B, toDelete)){
        toDelete = monitorInstersctSeg(toDelete, B.b, inter, A, B, ob1, ob2, ob);
    }
    else if(isIn(B.b, ob1.Sommets) &&  !isOutside(B.b, ob2) && !isIn(B, toDelete)){
        toDelete = monitorInstersctSeg(toDelete, B.a, inter, A, B, ob1, ob2, ob);
    }
    return toDelete;
}

list<Segment> monitorInstersctSeg(list<Segment>& toDelete, Point x, Point inter, Segment A, Segment B, Obstacle& ob1, Obstacle& ob2, Obstacle& ob){
    Segment nouveau(x, inter);
    ob.segValides_contour.push_back(nouveau);
    Segment test(A.a, inter);
    auto it = ob2.segValides_contour.begin();
    bool mem = true;
    for(; it != ob2.segValides_contour.end() ; it++) if(intersect(*it, test)) mem = false; 
    if( mem && isOutside(A.a, ob1)){ ob.segValides_contour.push_back(test); cout<<"ajout du seg en 1"<<test<<endl;}
    test = Segment(A.b,inter);
    it = ob2.segValides_contour.begin();
    mem = true;
    for(; it != ob2.segValides_contour.end() ; it++) if(intersect(*it, test)) mem = false; 
    if( mem && isOutside(A.b, ob1)){ ob.segValides_contour.push_back(test); cout<<"ajout du seg en 2"<<test<<endl;}
    toDelete.push_back(B);
    ob.Sommets.push_back(inter);
    ob.nbr_sommets += 1;
    return toDelete;
}


