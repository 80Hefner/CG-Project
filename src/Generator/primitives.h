#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include <vector>

#include "../utils/ponto.h"

using namespace std;

vector<Ponto> plane(float size);
vector<Ponto> criaCubo(float iniX, float iniY, float iniZ, float dimX, float dimY, float dimZ, int divX, int divY, int divZ);
vector<Ponto> box(float dimX, float dimY, float dimZ, int nrDivisoes);
vector<Ponto> cone(float raioBase, float altura, int nrSlices, int nrStacks);


#endif //PRIMITIVES_H