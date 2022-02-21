#include "Arc.hpp"
#include <vector>
#include <list>
#include <fstream>


void Dijsktra(int N, vector<vector<double> > c, double *l, double *p);
vector<vector<double> >  exempleEnonce();
void printC(vector<vector<double> > c);
list<Point> cheminFinale(Point * memory, double * p, int nb);
void printCheminFinale(list<Point> chemin);