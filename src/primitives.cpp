#define _USE_MATH_DEFINES // always before the include

#include "ponto.h"
#include <math.h>
#include <vector>

using namespace std;


// Criação de um plano na superfície do plano XZ.
vector<Ponto> plano(float size) {
	
	//vector<Ponto> é o mesmo que ter um array dinamico de Ponto
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


vector<Ponto> criaCubo(float iniX, float iniY, float iniZ, float dimX, float dimY, float dimZ, int divX, int divY, int divZ) {
	
	vector<Ponto> pontos;

	//CONTRUINDO POR FACES TEMOS:


	//Baixo
	pontos.push_back(Ponto(-iniX + divX * dimX, -iniY, -iniZ + (divZ + 1) * dimZ));
	pontos.push_back(Ponto(-iniX + divX * dimX, -iniY, -iniZ + divZ * dimZ));
	pontos.push_back(Ponto(-iniX + (divX + 1) * dimX, -iniY, -iniZ + divZ * dimZ));

	pontos.push_back(Ponto(-iniX + divX * dimX, -iniY, -iniZ + (divZ + 1) * dimZ));
	pontos.push_back(Ponto(-iniX + (divX + 1) * dimX, -iniY, -iniZ + divZ * dimZ));
	pontos.push_back(Ponto(-iniX + (divX + 1) * dimX, -iniY, -iniZ + (divZ + 1) * dimZ));

	//Cima
	pontos.push_back(Ponto(-iniX + divX * dimX, iniY, -iniZ + (divZ + 1) * dimZ));
	pontos.push_back(Ponto(-iniX + (divX + 1) * dimX, iniY, -iniZ + divZ * dimZ));
	pontos.push_back(Ponto(-iniX + divX * dimX, iniY, -iniZ + divZ * dimZ));

	pontos.push_back(Ponto(-iniX + divX * dimX, iniY, iniZ + (divZ + 1) * dimZ));
	pontos.push_back(Ponto(-iniX + (divX + 1) * dimX, iniY, -iniZ + (divZ + 1) * dimZ));
	pontos.push_back(Ponto(-iniX + (divX + 1) * dimX, iniY, -iniZ + divZ * dimZ));

	
	//Frente
	pontos.push_back(Ponto(-iniX + (divX + 1) * dimX, iniY - dimY * dimY, iniZ));
	pontos.push_back(Ponto(-iniX + divX * dimX, iniY - dimY * dimY, iniZ));
	pontos.push_back(Ponto(-iniX + divX * dimX, iniY - (dimY + 1) * dimY, iniZ));

	pontos.push_back(Ponto(-iniX + (divX + 1) * dimX, iniY - (dimY + 1) * dimY, iniZ));
	pontos.push_back(Ponto(-iniX + (divX + 1) * dimX, iniY - dimY * dimY, iniZ));
	pontos.push_back(Ponto(-iniX + divX * dimX, iniY - (dimY + 1) * dimY, iniZ));

	//Trás
	pontos.push_back(Ponto(-iniX + (divX + 1) * dimX, iniY - dimY * dimY, -iniZ));
	pontos.push_back(Ponto(-iniX + divX * dimX, iniY - (dimY + 1) * dimY, -iniZ));
	pontos.push_back(Ponto(-iniX + divX * dimX, iniY - dimY * dimY, -iniZ));

	pontos.push_back(Ponto(-iniX + (divX + 1) * dimX, iniY - (dimY + 1) * dimY, -iniZ));
	pontos.push_back(Ponto(-iniX + divX * dimX, iniY - (dimY + 1) * dimY, -iniZ));
	pontos.push_back(Ponto(-iniX + (divX + 1) * dimX, iniY - dimY * dimY, -iniZ));

	
	//Direita
	pontos.push_back(Ponto(iniX, iniY - (divY + 1) * dimY, iniZ - divZ * dimZ));
	pontos.push_back(Ponto(iniX, iniY - (divY + 1) * dimY, iniZ - (divZ + 1) * dimZ));
	pontos.push_back(Ponto(iniX, iniY - divY * dimY, iniZ - (divZ + 1) * dimZ));

	pontos.push_back(Ponto(iniX, iniY - (divY + 1) * dimY, iniZ - divZ * dimZ));
	pontos.push_back(Ponto(iniX, iniY - divY * dimY, iniZ - (divZ + 1) * dimZ));
	pontos.push_back(Ponto(iniX, iniY - divY * dimY, iniZ - divZ * dimZ));

	//Esquerda
	pontos.push_back(Ponto(-iniX, iniY - (divY + 1) * dimY, iniZ - divZ * dimZ));
	pontos.push_back(Ponto(-iniX, iniY - (divY + 1) * dimY, iniZ - (divZ + 1) * dimZ));
	pontos.push_back(Ponto(-iniX, iniY - divY * dimY, iniZ - (divZ + 1) * dimZ));

	pontos.push_back(Ponto(-iniX, iniY - (divY + 1) * dimY, iniZ - divZ * dimZ));
	pontos.push_back(Ponto(-iniX, iniY - divY * dimY, iniZ - (divZ + 1) * dimZ));
	pontos.push_back(Ponto(-iniX, iniY - divY * dimY, iniZ - divZ * dimZ));


	return pontos;
}

// Criação de uma box com as dimensões dadas e com um numero de Divisões em iguais secções da caixa
vector<Ponto> box(float dimX, float dimY, float dimZ, int nrDivisoes) {
	
	vector<Ponto> pontos;

	float inicialX = dimX / 2;
	float inicialY = dimY / 2;
	float inicialZ = dimZ / 2;
	
	float distanicaX = dimX / nrDivisoes;
	float distanicaY = dimY / nrDivisoes;
	float distanicaZ = dimZ / nrDivisoes;

	// Se tivermos 2 divisões, pasamos a ter 8 cubos. 
	// Temos de fazer então 3 for (um para a divisão em cada eixo)
	for (int divX = 0; divX < nrDivisoes; divX++) {
		for (int divY = 0; divY < nrDivisoes; divY++) {
			for (int divZ = 0; divZ < nrDivisoes; divZ++) {

				//Cria um vector de Pontos para todos os cubos que vão fazer parte da Box
				vector<Ponto> novosPontos = criaCubo(inicialX, inicialY, inicialZ, distanicaX, distanicaY, distanicaZ, divX, divY, divZ);

				//Junta os pontos de um cubinho aos pontos que já tinha de cubos anteriores que formavam a caixa
				pontos.insert(pontos.end(), novosPontos.begin(), novosPontos.end());

			}
		}
	}

	return pontos;
}


//Criação de um cone com um dado raio, uma altura, nr slices e de stacks
vector<Ponto> cone(float raioBase, float altura, int nrSlices, int nrStacks) {
	
	vector<Ponto> pontos;

	float defaultAngleFatia = (2 * M_PI) / nrSlices;

	for (int fatiaNr = 0; fatiaNr < nrSlices; fatiaNr++) {

		float angulo = fatiaNr * defaultAngleFatia;
		float proxAngulo = angulo + defaultAngleFatia;


		//Base
		pontos.push_back(Ponto(0.0f, -altura / 2, 0.0f));
		pontos.push_back(Ponto(raioBase * cos(angulo), -altura / 2, raioBase * sin(angulo)));
		pontos.push_back(Ponto(raioBase * cos(proxAngulo), -altura / 2, raioBase * sin(proxAngulo)));

		for (int nrCamada = 1; nrCamada < nrStacks; nrCamada++) {

		}

		//pontos.push_back(Ponto());
		//pontos.push_back(Ponto());
		//pontos.push_back(Ponto());
	}

	return pontos;
}