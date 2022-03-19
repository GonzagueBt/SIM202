#include "Graphe.hpp"



Graphe::Graphe(list<Obstacle> obst, Point x, Point y){
    depart = x;
    fin = y;
    list<Segment> toDelete;
    Obstacle final = constructionGraphe(obst, depart, fin, toDelete);
    printSommet(final.Sommets);
    cout<<"ajout point de départ"<<endl;
    final = addPointObstacle(final, depart, toDelete); 
    cout<<"ajout point de fin"<<endl;
    final = addPointObstacle(final, fin, toDelete); 
    auto it3 = toDelete.begin();
    for(; it3 != toDelete.end(); it3++){
        cout<<"segment : " << *it3<< "supprimé"<<endl;
        final.deleteSegFromList(*it3, "contour");
        final.deleteSegFromList(*it3, "reste");
    }
    printSegments(final.segValides_contour);
    graphe_Obst = deleteSegCommun(final.segValides_contour);
    graphe_Autre = final.segValides_reste;
    graphe_All = concateListe(graphe_Obst, graphe_Autre, true);
    nb_sommets = final.nbr_sommets - sommetsNonUsed(final.Sommets, graphe_All);
    printSommet(final.Sommets);
}


Obstacle constructionGraphe(list<Obstacle> obst, Point x, Point y, list<Segment>& toDelete){
    auto its=obst.begin();
    Obstacle& final= *its;
    if(obst.size()>0 && (!isOutside(x, *its) || !isOutside(y, *its))){
        cout<<"Point d'arrivée ou de départ à l'intérieur d'un obstacle, problème non résoluble"<<endl;
        abort();
    }
    if(obst.size()>1){ 
        auto its2=obst.begin();
        its2++;
        for(; its!=obst.end(); its++){
            for(;its2!=obst.end(); its2++){
                checkIntersectionObsts(toDelete, *its, *its2);
            }
        }
        auto its1 = obst.rbegin();
        auto its3=obst.rbegin();
        its3++;
        for(; its1!=obst.rend(); its1++){
            for(;its3!=obst.rend(); its3++){
                checkIntersectionObsts(toDelete, *its1, *its3);
            }
        }
        its = obst.begin();
        its++;
        for(; its!= obst.end(); its++){
            if(!isOutside(x, *its) || !isOutside(y, *its)){
                cout<<"Point d'arrivée ou de départ à l'intérieur d'un obstacle, problème non résoluble"<<endl;
                abort();
            }
            final = assemblage2Obstsacles(final, *its, toDelete);
        }
    }
    final = lastCheck(final);
    return final;
}

Obstacle addPointObstacle(Obstacle final, Point x, list<Segment>& toDelete){
    vector<Point> pt;
    pt.push_back(x);
    Obstacle depart(pt, 1);
    final = assemblage2Obstsacles(final, pt, toDelete);
    return final;
}


Obstacle assemblage2Obstsacles(Obstacle& ob1, Obstacle ob2, list<Segment>& toDelete){
    Obstacle ob=ob1;
    auto its = ob2.segValides_reste.begin();
    for(; its!= ob2.segValides_reste.end(); its++) ob.segValides_reste.push_back(*its);
    its = ob2.segValides_contour.begin();
    for(; its!= ob2.segValides_contour.end(); its++) ob.segValides_contour.push_back(*its);   
    list<Point> toDeleteP;
    for(int i=0; i< (int) ob1.Sommets.size(); i++){
        for(int j=0; j< (int) ob2.Sommets.size(); j++){
            if(isIn(ob2.Sommets[j], ob1.Sommets)){
                deleteSegConfused(ob1, ob2, ob2.Sommets[j], toDelete);
            }
            Point pt2 = ob2.Sommets[j];
            if(ob1.Sommets[i]==pt2) continue;
            auto its=ob1.segValides_contour.begin();
            bool isValide = true; 
            for(; its!= ob1.segValides_contour.end(); its++){
                if(intersect(ob1.Sommets[i], pt2, its->a, its->b) || isIn(pt2,ob1.Sommets) || isIn(ob1.Sommets[i],ob2.Sommets)){ // si intersection entre segment de ob1 et segment ij
                    isValide = false;
                    break;
                } 
            }
            if(!isValide) continue;
            its=ob2.segValides_contour.begin(); 
            for(; its!= ob2.segValides_contour.end(); its++){
                if(its->a==ob1.Sommets[i] || its->b==ob1.Sommets[i] || its->a==pt2 || its->b==pt2) continue;
                if(intersect(ob1.Sommets[i], pt2, its->a, its->b)){
                    isValide = false;
                    break;
                } 
            }
            if(!isValide) continue;
            //if(!isOutside(ob1.Sommets[i], ob2) /*|| !isOutside(ob2.Sommets[j], ob1)*/) isValide = false;
            if(isValide){
                Segment newSeg = Segment(ob1.Sommets[i], pt2);
                if(!isIn(newSeg, ob.segValides_reste)) ob.segValides_reste.push_back(newSeg);
            }
        }
    }
    ob.Sommets = concateVectorPoints(ob1.Sommets, ob2.Sommets);
    ob.nbr_sommets = ob.Sommets.size();
    return ob;
}

void deleteSegConfused(Obstacle ob1, Obstacle ob2, Point x, list<Segment>& toDelete){
    auto it = ob1.segValides_contour.begin();
    for(;it != ob1.segValides_contour.end();it++){
        if(it->a!=x && it->b!=x) continue;
        auto it2 = ob2.segValides_contour.begin();
        for(;it2 != ob2.segValides_contour.end() ; it2++){
            if(it2->a!=x && it2->b!=x) continue;
            if(isConfused(*it, *it2)){
                if(!isASide(*it, *it2, x)) continue;
                if(it->poid < it2->poid && !isIn(*it, toDelete) && !isIn(*it2, toDelete)){cout<<"je delete "<<*it<<endl; toDelete.push_back(*it);}
                else if(!isIn(*it2, toDelete) && !isIn(*it, toDelete)){ cout<<"je delete "<<*it<<endl; toDelete.push_back(*it2);}
            }
        }
    }
}

bool isASide(Segment A, Segment B, Point x){
    list<Point> sortPt;
    sortPt.push_back(x);
    if(A.a<x && !isIn(A.a, sortPt)) sortPt.push_back(A.a);
    else if(!isIn(A.a, sortPt)) sortPt.push_front(A.a);
    if(A.b<x && !isIn(A.b, sortPt)) sortPt.push_back(A.b);
    else if(!isIn(A.b, sortPt)) sortPt.push_front(A.b);
    if(B.a<x && !isIn(B.a, sortPt)) sortPt.push_back(B.a);
    else if(!isIn(B.a, sortPt)) sortPt.push_front(B.a);
    if(B.b<x && !isIn(B.b, sortPt)) sortPt.push_back(B.b);
    else if(!isIn(B.b, sortPt)) sortPt.push_front(B.b);
    //if(x==Point(1,2)) printPoints(sortPt);
    if(sortPt.front()==x || sortPt.back()==x) return true;
    return false;
}

Obstacle lastCheck(Obstacle final){
    list<Segment> toDelete;
    auto it= final.segValides_reste.begin();
    for(; it != final.segValides_reste.end(); it++){
        auto it2 = final.segValides_contour.begin();
        for(; it2 != final.segValides_contour.end(); it2++){
            if(intersect(*it2, *it)){ toDelete.push_back(*it); break;}
        }
    }
    auto it3 = toDelete.begin();
    for(; it3 != toDelete.end(); it3++){
        final.deleteSegFromList(*it3, "reste");
    }
    return final;
}


//////////////////////////////////////////|------------------------------|///////////////////////////////////////////
//////////////////////////////////////////| GESTION OBSTACLES CHEVAUCHES |///////////////////////////////////////////
//////////////////////////////////////////|------------------------------|///////////////////////////////////////////


void checkIntersectionObsts(list<Segment>& toDelete, Obstacle& ob1, Obstacle& ob2){
    list<Point> toDeleteP;
    auto it = ob1.segValides_contour.begin();
    list<Segment> segToAdd;
    for(; it != ob1.segValides_contour.end(); it++){
        if(isIn(*it, toDelete)) continue;
        bool haveIntersct = false;
        Segment A = *it;
        vector<Point> intersects;
        intersects.push_back(A.a);
        auto it2 = ob2.segValides_contour.begin();
        for(; it2 != ob2.segValides_contour.end() ; it2++){
            Segment B = *it2;
            if(intersect(A, B)){ 
                haveIntersct = true;
                intersects.push_back(Intersction2Arcs(A, B));
                if(!isIn(B, toDelete)) toDelete.push_back(B);
                if(!isOutside(B.a, ob1.Sommets)) toDeleteP.push_back(B.a);
                if(!isOutside(B.b, ob1.Sommets)) toDeleteP.push_back(B.b);
            }
        }
        if(!haveIntersct) continue;
        cout<<A<<" inteserct"<<endl;
        toDelete.push_back(A);
        intersects = sortByDist(intersects);
        intersects.push_back(A.b);
        int i=0;
        if(isIn(A.a, ob2.Sommets))i=1;
        else if(!isOutside(A.a, ob2)){ i=1; toDeleteP.push_back(A.a);}
        for(; i< (int) intersects.size(); i=i+2){
            if(intersects[i]== A.b) break;
            segToAdd.push_back(Segment(intersects[i], intersects[i+1]));
            if(!isIn(intersects[i], ob1.Sommets) && !isIn(intersects[i], ob2.Sommets)){
                ob1.Sommets.push_back(intersects[i]);
                //ob2.Sommets.push_back(intersects[i]);
            }
            if(!isIn(intersects[i+1], ob1.Sommets) && !isIn(intersects[i+1], ob2.Sommets)){
                ob1.Sommets.push_back(intersects[i+1]);
                //ob2.Sommets.push_back(intersects[i+1]);
            }
            ob1.nbr_sommets+=1;
            ob2.nbr_sommets+=1;
        }
        if(!isOutside(A.b, ob2.Sommets)) toDeleteP.push_back(A.b);
        if(!isOutside(A.a, ob2.Sommets)) toDeleteP.push_back(A.a);
    }
    list<Segment> segToAddBis;
    auto it5 = ob2.segValides_contour.begin();
    for(; it5 != ob2.segValides_contour.end(); it5++){
        bool haveIntersct = false;
        Segment A = *it5;
        vector<Point> intersects;
        intersects.push_back(A.a);
        auto it6 = ob1.segValides_contour.begin();
        for(; it6 != ob1.segValides_contour.end() ; it6++){
            Segment B = *it6;
            if(intersect(A, B)){ 
                haveIntersct = true;
                intersects.push_back(Intersction2Arcs(A, B));
                if(!isIn(B, toDelete)) toDelete.push_back(B);
                if(!isOutside(B.a, ob2.Sommets)) toDeleteP.push_back(B.a);
                if(!isOutside(B.b, ob2.Sommets)) toDeleteP.push_back(B.b);
            }
        }
        if(!haveIntersct) continue;
        cout<<A<<" interserct"<<endl;
        toDelete.push_back(A);
        intersects = sortByDist(intersects);
        intersects.push_back(A.b);
        int i=0;
        if(isIn(A.a, ob1.Sommets))i=1;
        else if(!isOutside(A.a, ob1)){ i=1; toDeleteP.push_back(A.a);}
        for(; i< (int) intersects.size(); i=i+2){
            if(intersects[i]== A.b) break;
            segToAddBis.push_back(Segment(intersects[i], intersects[i+1]));
            if(!isIn(intersects[i], ob2.Sommets) && !isIn(intersects[i], ob1.Sommets)){
                //ob1.Sommets.push_back(intersects[i]);
                ob2.Sommets.push_back(intersects[i]);
            }
            if(!isIn(intersects[i+1], ob1.Sommets) && !isIn(intersects[i+1], ob2.Sommets)){
                //ob1.Sommets.push_back(intersects[i+1]);
                ob2.Sommets.push_back(intersects[i+1]);
            }
            ob1.nbr_sommets+=1;
            ob2.nbr_sommets+=1;
        }
        if(!isOutside(A.b, ob1.Sommets)) toDeleteP.push_back(A.b);
        if(!isOutside(A.a, ob1.Sommets)) toDeleteP.push_back(A.a);
    }
    auto it3 = segToAdd.begin();
    for(; it3 != segToAdd.end(); it3++){
        ob1.segValides_reste.push_back(*it3);
        ob1.segValides_contour.push_back(*it3);
        cout<<"segment "<<*it3<<" ajouté"<<endl;
    }
    it3 = segToAddBis.begin();
    for(; it3 != segToAddBis.end(); it3++){
        ob2.segValides_reste.push_back(*it3);
        ob2.segValides_contour.push_back(*it3);
        cout<<"segment "<<*it3<<" ajouté"<<endl;
    }
    auto it4 = toDeleteP.begin();
    for(; it4 != toDeleteP.end(); it4++){
        deleteSegWithPt(toDelete, ob1.segValides_contour, *it4);
        deleteSegWithPt(toDelete, ob1.segValides_reste, *it4);
        deleteSegWithPt(toDelete, ob2.segValides_contour, *it4);
        deleteSegWithPt(toDelete, ob2.segValides_reste, *it4);  
        deletePointFromVector(ob1.Sommets, *it4);
        deletePointFromVector(ob2.Sommets, *it4);
        cout<<"point "<<*it4<<" supprimé"<<endl; 
    }
}

vector<Point> sortByDist(vector<Point> pts){
    auto it = pts.begin();
    vector<Point> sort;
    sort.push_back(*it);
    Point first = *it;
    pts.erase(it);
    while(pts.size()!=0){
        it = pts.begin();
        double dist= (int) INT_MAX;
        vector<Point>::iterator memory = sort.begin();
        for(;it!=pts.end();it++){
            double newdist = distance(first, *it);
            if(newdist<dist){
                dist = newdist;
                memory = it;
            }
        }
        sort.push_back(*memory);
        pts.erase(memory);
    }
    return sort;
}




