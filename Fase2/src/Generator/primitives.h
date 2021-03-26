#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include <vector>

#include "../utils/ponto.h"

using namespace std;

vector<Ponto> plane(float size);
vector<Ponto> box(float dimX, float dimY, float dimZ, int nrDivisoes);
vector<Ponto> cone(float raioBase, float alturaCone, int nrSlices, int nrStacks);
vector<Ponto> sphere(float raio, int nrSlices, int nrStacks);
vector<Ponto> torus(float innerRadius,float outerRadius , int stacks, int slices);

#endif //PRIMITIVES_H
