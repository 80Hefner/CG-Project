#define _USE_MATH_DEFINES 
#include <math.h>
#include <vector>
#include <string.h>

#include "primitives.h"

using namespace std;


// Criação de um plano na superfície do plano XZ.
vector<Ponto> plane(float size) {

	//vector<Ponto> É o mesmo que ter um array dinamico de Ponto
	vector<Ponto> pontos;

	float distancia = size / 2;

	pontos.push_back(Ponto(distancia, 0, distancia));
	pontos.push_back(Ponto(distancia, 0, -distancia));
	pontos.push_back(Ponto(-distancia, 0, -distancia));

	pontos.push_back(Ponto(-distancia, 0, -distancia));
	pontos.push_back(Ponto(-distancia, 0, distancia));
	pontos.push_back(Ponto(distancia, 0, distancia));

	return pontos;

}

// Criação de uma box com as dimensões dadas e com um numero de Divisões em iguais secções da caixa
vector<Ponto> box(float dimX, float dimY, float dimZ, int nrDivisoes) {

	vector<Ponto> pontos;

	float inicialX = dimX / 2;
	float inicialY = dimY / 2;
	float inicialZ = dimZ / 2;

	float distanciaX = dimX / nrDivisoes;
	float distanciaY = dimY / nrDivisoes;
	float distanciaZ = dimZ / nrDivisoes;

	for (int divX = 0; divX < nrDivisoes; divX++) {
		for (int divZ = 0; divZ < nrDivisoes; divZ++) {

			// Plano xz pos
			pontos.push_back(Ponto(-inicialX + divX * distanciaX, inicialY, -inicialZ + (divZ + 1) * distanciaZ));
			pontos.push_back(Ponto(-inicialX + (divX + 1) * distanciaX, inicialY, -inicialZ + divZ * distanciaZ));
			pontos.push_back(Ponto(-inicialX + divX * distanciaX, inicialY, -inicialZ + divZ * distanciaZ));

			pontos.push_back(Ponto(-inicialX + divX * distanciaX, inicialY, -inicialZ + (divZ + 1) * distanciaZ));
			pontos.push_back(Ponto(-inicialX + (divX + 1) * distanciaX, inicialY, -inicialZ + (divZ + 1) * distanciaZ));
			pontos.push_back(Ponto(-inicialX + (divX + 1) * distanciaX, inicialY, -inicialZ + divZ * distanciaZ));

			// Plano xz neg
			pontos.push_back(Ponto(-inicialX + divX * distanciaX, -inicialY, -inicialZ + (divZ + 1) * distanciaZ));
			pontos.push_back(Ponto(-inicialX + divX * distanciaX, -inicialY, -inicialZ + divZ * distanciaZ));
			pontos.push_back(Ponto(-inicialX + (divX + 1) * distanciaX, -inicialY, -inicialZ + divZ * distanciaZ));

			pontos.push_back(Ponto(-inicialX + divX * distanciaX, -inicialY, -inicialZ + (divZ + 1) * distanciaZ));
			pontos.push_back(Ponto(-inicialX + (divX + 1) * distanciaX, -inicialY, -inicialZ + divZ * distanciaZ));
			pontos.push_back(Ponto(-inicialX + (divX + 1) * distanciaX, -inicialY, -inicialZ + (divZ + 1) * distanciaZ));

		}
	}

	for (int divX = 0; divX < nrDivisoes; divX++) {
		for (int divY = 0; divY < nrDivisoes; divY++) {

			// Plano xy pos
			pontos.push_back(Ponto(-inicialX + (divX + 1) * distanciaX, inicialY - divY * distanciaY, inicialZ));
			pontos.push_back(Ponto(-inicialX + divX * distanciaX, inicialY - divY * distanciaY, inicialZ));
			pontos.push_back(Ponto(-inicialX + divX * distanciaX, inicialY - (divY + 1) * distanciaY, inicialZ));

			pontos.push_back(Ponto(-inicialX + (divX + 1) * distanciaX, inicialY - (divY + 1) * distanciaY, inicialZ));
			pontos.push_back(Ponto(-inicialX + (divX + 1) * distanciaX, inicialY - divY * distanciaY, inicialZ));
			pontos.push_back(Ponto(-inicialX + divX * distanciaX, inicialY - (divY + 1) * distanciaY, inicialZ));

			// Plano xy neg
			pontos.push_back(Ponto(-inicialX + (divX + 1) * distanciaX, inicialY - divY * distanciaY, -inicialZ));
			pontos.push_back(Ponto(-inicialX + divX * distanciaX, inicialY - (divY + 1) * distanciaY, -inicialZ));
			pontos.push_back(Ponto(-inicialX + divX * distanciaX, inicialY - divY * distanciaY, -inicialZ));

			pontos.push_back(Ponto(-inicialX + (divX + 1) * distanciaX, inicialY - (divY + 1) * distanciaY, -inicialZ));
			pontos.push_back(Ponto(-inicialX + divX * distanciaX, inicialY - (divY + 1) * distanciaY, -inicialZ));
			pontos.push_back(Ponto(-inicialX + (divX + 1) * distanciaX, inicialY - divY * distanciaY, -inicialZ));

		}
	}

	for (int divY = 0; divY < nrDivisoes; divY++) {
		for (int divZ = 0; divZ < nrDivisoes; divZ++) {

			// Plano yz pos
			pontos.push_back(Ponto(inicialX, inicialY - (divY + 1) * distanciaY, inicialZ - divZ * distanciaZ));
			pontos.push_back(Ponto(inicialX, inicialY - (divY + 1) * distanciaY, inicialZ - (divZ + 1) * distanciaZ));
			pontos.push_back(Ponto(inicialX, inicialY - divY * distanciaY, inicialZ - (divZ + 1) * distanciaZ));

			pontos.push_back(Ponto(inicialX, inicialY - (divY + 1) * distanciaY, inicialZ - divZ * distanciaZ));
			pontos.push_back(Ponto(inicialX, inicialY - divY * distanciaY, inicialZ - (divZ + 1) * distanciaZ));
			pontos.push_back(Ponto(inicialX, inicialY - divY * distanciaY, inicialZ - divZ * distanciaZ));

			// Plano yz neg
			pontos.push_back(Ponto(-inicialX, inicialY - (divY + 1) * distanciaY, inicialZ - divZ * distanciaZ));
			pontos.push_back(Ponto(-inicialX, inicialY - divY * distanciaY, inicialZ - (divZ + 1) * distanciaZ));
			pontos.push_back(Ponto(-inicialX, inicialY - (divY + 1) * distanciaY, inicialZ - (divZ + 1) * distanciaZ));

			pontos.push_back(Ponto(-inicialX, inicialY - (divY + 1) * distanciaY, inicialZ - divZ * distanciaZ));
			pontos.push_back(Ponto(-inicialX, inicialY - divY * distanciaY, inicialZ - divZ * distanciaZ));
			pontos.push_back(Ponto(-inicialX, inicialY - divY * distanciaY, inicialZ - (divZ + 1) * distanciaZ));

		}
	}

	return pontos;
}

// Criação de um cone com um dado raio, uma altura, nr slices e de stacks
vector<Ponto> cone(float raioBase, float alturaCone, int nrSlices, int nrStacks) {

	vector<Ponto> pontos;

	float defaultAngleFatia = (2 * M_PI) / nrSlices;
	float alturaStack = alturaCone / nrStacks;
	float mudancaRaioStack = raioBase / nrStacks;

	for (int fatiaNr = 0; fatiaNr < nrSlices; fatiaNr++) {

		float angulo = fatiaNr * defaultAngleFatia;
		float proxAngulo = angulo + defaultAngleFatia;

		float alturaAtual = 0;
		float proxAltura = alturaStack;

		float raioAtual = raioBase;
		float proxRaio = raioBase - mudancaRaioStack;


		// Base
		pontos.push_back(Ponto(0.0f, 0.0f, 0.0f));
		pontos.push_back(Ponto(raioBase * cos(angulo), 0.0f, raioBase * sin(angulo)));
		pontos.push_back(Ponto(raioBase * cos(proxAngulo), 0.0f, raioBase * sin(proxAngulo)));

		for (int nrCamada = 1; nrCamada < nrStacks; nrCamada++) {

			//Triangulo de stacks intermédias que compõe um quadrado
			pontos.push_back(Ponto(proxRaio * cos(proxAngulo), proxAltura, proxRaio * sin(proxAngulo)));
			pontos.push_back(Ponto(raioAtual * cos(proxAngulo), alturaAtual, raioAtual * sin(proxAngulo)));
			pontos.push_back(Ponto(raioAtual * cos(angulo), alturaAtual, raioAtual * sin(angulo)));

			//Triangulo de stacks intermédias que compõe um quadrado
			pontos.push_back(Ponto(proxRaio * cos(angulo), proxAltura, proxRaio * sin(angulo)));
			pontos.push_back(Ponto(proxRaio * cos(proxAngulo), proxAltura, proxRaio * sin(proxAngulo)));
			pontos.push_back(Ponto(raioAtual * cos(angulo), alturaAtual, raioAtual * sin(angulo)));

			alturaAtual += alturaStack;
			proxAltura += alturaStack;

			raioAtual -= mudancaRaioStack;
			proxRaio -= mudancaRaioStack;
		}

		//Triângulos ultima stack
		pontos.push_back(Ponto(raioAtual * cos(proxAngulo), alturaAtual, raioAtual * sin(proxAngulo)));
		pontos.push_back(Ponto(raioAtual * cos(angulo), alturaAtual, raioAtual * sin(angulo)));
		pontos.push_back(Ponto(0.0f, alturaCone, 0.0f));

	}

	return pontos;
}

// Criação de uma esfera com um dado raio, nr slices e de stacks
void sphere(float raio, int nrSlices, int nrStacks, vector<Ponto>* ps, vector<Ponto>* ns) {

	vector<Ponto> pontos;
	vector<Ponto> normals;

	float defaultAngleFatia = (2 * M_PI) / nrSlices;
	float defaultAngleStack = M_PI / nrStacks;

	for (int fatiaNr = 0; fatiaNr < nrSlices; fatiaNr++) {

		float anguloFatia = fatiaNr * defaultAngleFatia;
		float proxAnguloFatia = anguloFatia + defaultAngleFatia;

		float anguloStack = - M_PI_2;
		float proxAnguloStack = anguloStack + defaultAngleStack;

		// Para perceber ver slides P03, mais especificamente página 3/9 (tem lá as fórmulas e a explicação)

		//Triângulos da primeira stack (mais em baixo)
		Ponto p1 = Ponto(0.0f, -raio, 0.0f);
		Ponto p2 = Ponto(raio * cos(proxAnguloStack) * sin(proxAnguloFatia), raio * sin(proxAnguloStack), raio * cos(proxAnguloStack) * cos(proxAnguloFatia));
		Ponto p3 = Ponto(raio * cos(proxAnguloStack) * sin(anguloFatia), raio * sin (proxAnguloStack) , raio * cos(proxAnguloStack) * cos(anguloFatia));
		
		pontos.push_back(p1);
		pontos.push_back(p2);
		pontos.push_back(p3);

		normals.push_back(vector_normalize_ponto(p1));
		normals.push_back(vector_normalize_ponto(p2));
		normals.push_back(vector_normalize_ponto(p3));

		anguloStack += defaultAngleStack;
		proxAnguloStack += defaultAngleStack;

		for (int nrCamada = 1; nrCamada < nrStacks; nrCamada++) {

			//Triangulo de stacks intermédias que compõe um quadrado
			p1 = Ponto(raio * cos(anguloStack) * sin(anguloFatia), raio * sin(anguloStack), raio * cos(anguloStack) * cos(anguloFatia));
			p2 = Ponto(raio * cos(anguloStack) * sin(proxAnguloFatia), raio * sin(anguloStack), raio * cos(anguloStack) * cos(proxAnguloFatia));
			p3 = Ponto(raio * cos(proxAnguloStack) * sin(anguloFatia), raio * sin(proxAnguloStack), raio * cos(proxAnguloStack) * cos(anguloFatia));

			pontos.push_back(p1);
			pontos.push_back(p2);
			pontos.push_back(p3);

			normals.push_back(vector_normalize_ponto(p1));
			normals.push_back(vector_normalize_ponto(p2));
			normals.push_back(vector_normalize_ponto(p3));

			//Triangulo de stacks intermédias que compõe um quadrado
			p1 = Ponto(raio * cos(anguloStack) * sin(proxAnguloFatia), raio * sin(anguloStack), raio * cos(anguloStack) * cos(proxAnguloFatia));
			p2 = Ponto(raio * cos(proxAnguloStack) * sin(proxAnguloFatia), raio * sin(proxAnguloStack), raio * cos(proxAnguloStack) * cos(proxAnguloFatia));
			p3 = Ponto(raio * cos(proxAnguloStack) * sin(anguloFatia), raio * sin(proxAnguloStack), raio * cos(proxAnguloStack) * cos(anguloFatia));

			pontos.push_back(p1);
			pontos.push_back(p2);
			pontos.push_back(p3);

			normals.push_back(vector_normalize_ponto(p1));
			normals.push_back(vector_normalize_ponto(p2));
			normals.push_back(vector_normalize_ponto(p3));

			anguloStack += defaultAngleStack;
			proxAnguloStack += defaultAngleStack;
		}

		//Triângulos da última stack (mais em cima)
		p1 = Ponto(0.0f, raio, 0.0f);
		p2 = Ponto(raio * cos(anguloStack) * sin(proxAnguloFatia), raio * sin(anguloStack), raio * cos(anguloStack) * cos(proxAnguloFatia));
		p3 = Ponto(raio * cos(anguloStack) * sin(anguloFatia), raio * sin(anguloStack), raio * cos(anguloStack) * cos(anguloFatia));

		pontos.push_back(p1);
		pontos.push_back(p2);
		pontos.push_back(p3);

		normals.push_back(vector_normalize_ponto(p1));
		normals.push_back(vector_normalize_ponto(p2));
		normals.push_back(vector_normalize_ponto(p3));

		anguloStack += defaultAngleStack;
		proxAnguloStack += defaultAngleStack;
	}

	*ps = pontos;
	*ns = normals;
}


// Torus auxiliary function to generate a point in the surface
Ponto generateTorusPoint(float innerRadius, float outerRadius , float alpha, float beta) {
	return Ponto(cos(alpha) * (innerRadius * sin(beta) + outerRadius),
					cos(beta) * innerRadius,
					sin(alpha) * (innerRadius * sin(beta) + outerRadius));
}

// Torus auxiliary function to generate a point in the middle of its interior
Ponto generateTorusCenterPoint(float alpha, float outerRadius) {
	return Ponto(cos(alpha) * outerRadius, 0.0, sin(alpha) * outerRadius);
}

// Creates a torus centered on origin
void torus(float innerRadius, float outerRadius, int slices, int stacks, vector<Ponto>* ps, vector<Ponto>* ns) {
	
	vector<Ponto> points;
	vector<Ponto> normals;

	float alpha, alpha2, beta, beta2;

	float sliceAngle = (2 * M_PI) / slices;
	float stackAngle = (2 * M_PI) / stacks;

	// Process each slice
	for (int i = 0; i < slices; i++) {
		alpha = i * sliceAngle;
		alpha2 = (i+1) * sliceAngle;

		// Process each stack
		for (int j = 0; j < stacks; j++) {
			beta = j * stackAngle;
			beta2 = (j+1) * stackAngle;

			// Generates all four points associated to this slice and stack
			Ponto p1 = generateTorusPoint(innerRadius, outerRadius, alpha, beta);
			Ponto p2 = generateTorusPoint(innerRadius, outerRadius, alpha, beta2);
			Ponto p3 = generateTorusPoint(innerRadius, outerRadius, alpha2, beta2);
			Ponto p4 = generateTorusPoint(innerRadius, outerRadius, alpha2, beta);

			// Adds the points of the two triangles associated to this slice and stack
			points.push_back(p1);
			points.push_back(p3);
			points.push_back(p2);

			points.push_back(p1);
			points.push_back(p4);
			points.push_back(p3);

			// Adds the normals of the two triangles associated to this slice and stack
			Ponto c_p1 = generateTorusCenterPoint(alpha, outerRadius);
			Ponto c_p2 = generateTorusCenterPoint(alpha2, outerRadius);

			normals.push_back(vector_normalize_ponto(vector_sub_ponto(p1, c_p1)));
			normals.push_back(vector_normalize_ponto(vector_sub_ponto(p3, c_p2)));
			normals.push_back(vector_normalize_ponto(vector_sub_ponto(p2, c_p1)));
			
			normals.push_back(vector_normalize_ponto(vector_sub_ponto(p1, c_p1)));
			normals.push_back(vector_normalize_ponto(vector_sub_ponto(p4, c_p2)));
			normals.push_back(vector_normalize_ponto(vector_sub_ponto(p3, c_p2)));
		}
	}

	*ps = points;
	*ns = normals;
}

// Function that calculates the normal in p1, given two other points, following the right hand rule
Ponto calculate_normal(Ponto p1, Ponto p2, Ponto p3) {
	Ponto v1 = vector_sub_ponto(p2, p1);
	Ponto v2 = vector_sub_ponto(p3, p1);

	Ponto n = vector_cross_ponto(v1, v2);

	return vector_normalize_ponto(n);
}
