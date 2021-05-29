#include "float_vector.h"

void vector_cross(float* a, float* b, float* res) {

	res[0] = a[1]*b[2] - a[2]*b[1];
	res[1] = a[2]*b[0] - a[0]*b[2];
	res[2] = a[0]*b[1] - a[1]*b[0];
}

Ponto vector_cross_ponto(Ponto p1, Ponto p2) {
    return Ponto(p1.getY()*p2.getZ() - p1.getZ()*p2.getY(),
                 p1.getZ()*p2.getX() - p1.getX()*p2.getZ(),
                 p1.getX()*p2.getY() - p1.getY()*p2.getX());
}

void vector_normalize(float* a) {

	float l = sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
	a[0] = a[0]/l;
	a[1] = a[1]/l;
	a[2] = a[2]/l;
}

Ponto vector_normalize_ponto(Ponto p) {

    float x = p.getX(), y = p.getY(), z = p.getZ();

	float l = sqrt(x * x + y * y + z * z);
	x = x/l;
	y = y/l;
	z = z/l;

    return Ponto(x, y, z);
}

void vector_sub(float* a, float* b, float* res) {
    
    res[0] = a[0] - b[0];
    res[1] = a[1] - b[1];
    res[2] = a[2] - b[2];
}

Ponto vector_sub_ponto(Ponto p1, Ponto p2) {

    return Ponto(p1.getX() - p2.getX(),
                 p1.getY() - p2.getY(),
                 p1.getZ() - p2.getZ());
}

void vector_mul_value(float* a, float x, float* res) {
    res[0] = x * a[0];
    res[1] = x * a[1];
    res[2] = x * a[2];
}
