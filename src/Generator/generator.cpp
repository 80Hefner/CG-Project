// Aqui é para correr o gerador com uma main e criar ficheiros .3d que ele pedir ou dar erro se não der
#include <vector>
#include <string.h>
#include <iostream>
#include <fstream>

#include "../utils/ponto.h"
#include "primitives.cpp"

using namespace std;


void writePointsToFile(vector<Ponto> points, string fileString) {
    ofstream file;
    file.open(fileString, ios::out | ios::trunc);

    for(Ponto p : points) {
        float px = p.getX();
        float py = p.getY();
        float pz = p.getZ();

        string line = to_string(px) + ", " + to_string(py) + ", " + to_string(pz) + "\n";
        file << line;
    }

    file.close();
}

int main(int argc, char** argv) {

    vector<Ponto> pontos;
    string fileString;

    if (argc == 4 && strcmp(argv[1], "plane") == 0) {
        float size = atof(argv[2]);
        pontos = plane(size);

        fileString = argv[3];
        fileString = "../../../files3D/" + fileString;
        //fileString = strcat("../../../files3D/", fileString);

        writePointsToFile(pontos, fileString);
    }
}