#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include <vector>

#include "../utils/ponto.h"
#include "../utils/float_vector.h"

using namespace std;

vector<Ponto> plane(float size);
vector<Ponto> box(float dimX, float dimY, float dimZ, int nrDivisoes);
vector<Ponto> cone(float raioBase, float alturaCone, int nrSlices, int nrStacks);
void sphere(float raio, int nrSlices, int nrStacks, vector<Ponto>* pontos, vector<Ponto>* normals, vector<float>* ts);
void torus(float innerRadius, float outerRadius, int slices, int stacks, vector<Ponto>* ps, vector<Ponto>* ns);
Ponto calculate_normal(Ponto p1, Ponto p2, Ponto p3);

#endif //PRIMITIVES_H
