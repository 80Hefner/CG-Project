#ifndef FLOAT_VECTOR_H
#define FLOAT_VECTOR_H

#include "ponto.h"

void vector_cross(float* a, float* b, float* res);
void vector_normalize(float* a);
void vector_sub(float* a, float* b, float* res);

Ponto vector_cross_ponto(Ponto p1, Ponto p2);
Ponto vector_normalize_ponto(Ponto p);
Ponto vector_sub_ponto(Ponto p1, Ponto p2);

#endif //FLOAT_VECTOR_H
