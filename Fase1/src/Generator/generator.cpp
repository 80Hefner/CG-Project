// Aqui é para correr o gerador com uma main e criar ficheiros .3d que ele pedir ou dar erro se não der
#include <vector>
#include <string.h>
#include <iostream>
#include <fstream>

#include "../utils/ponto.h"
#include "primitives.h"

using namespace std;


void writePointsToFile(vector<Ponto> points, string fileString) {
    ofstream file;
    file.open(fileString, ios::out | ios::trunc);
    file << points.size() << "\n";

    for(Ponto p : points) {
        float px = p.getX();
        float py = p.getY();
        float pz = p.getZ();

        string line = to_string(px) + ", " + to_string(py) + ", " + to_string(pz) + "\n";
        file << line;
    }

    file.close();
}

void generatorHelpMenu() {
	cout << "┌───────────────────────────────────────GENERATOR HELP───────────────────────────────────────┐" << endl;
	cout << "│   Usage: ./generator [SHAPE]... [OUTPUT FILE]                                              │" << endl;
	cout << "│   Generates a .3d file, ready to be readen by the engine                                   │" << endl;
	cout << "│                                                                                            │" << endl;
	cout << "│   SHAPE                                                                                    │" << endl;
	cout << "│      plane [SIZE]                                                                          │" << endl;
	cout << "│          Creates a square in the XZ plane, centred in the origin, with given size.         │" << endl;
    cout << "│                                                                                            │" << endl;
    cout << "│      box [X_DIM] [Y_DIM] [Z_DIM] <optional>[DIVISIONS]                                     │" << endl;
	cout << "│          Creates a box with given dimensions, optionally divided in given divisions.       │" << endl;
	cout << "│                                                                                            │" << endl;
    cout << "│      sphere [RADIUS] [SLICES] [STACKS]                                                     │" << endl;
    cout << "│          Creates a sphere with given radius, divided in given slices and stacks.           │" << endl;
    cout << "│                                                                                            │" << endl;
    cout << "│      cone [RADIUS] [HEIGHT] [SLICES] [STACKS]                                              │" << endl;
    cout << "│          Creates a cone with given radius and height, divided in given slices and stacks.  │" << endl;
	cout << "└────────────────────────────────────────────────────────────────────────────────────────────┘" << endl;
}

int main(int argc, char** argv) {

    vector<Ponto> pontos;
    string fileString;

    if (argc == 2 && strcmp(argv[1], "--help") == 0) {
        generatorHelpMenu();
    }
    else if (argc == 4 && strcmp(argv[1], "plane") == 0) {
        float size = atof(argv[2]);
        pontos = plane(size);

        fileString = argv[3];
        fileString = "../../files3D/" + fileString;

        writePointsToFile(pontos, fileString);
    }
    else if (argc >= 6 && strcmp(argv[1], "box") == 0) {
        int i = 2;
        float dimX = atof(argv[i++]); // i=2
        float dimY = atof(argv[i++]); // i=3
        float dimZ = atof(argv[i++]); // i=4
        int divisions = 1;
        if (argc == 7) divisions = atoi(argv[i++]); // i=5
        pontos = box(dimX, dimY, dimZ, divisions);

        fileString = argv[i]; // i=5 or 6
        fileString = "../../files3D/" + fileString;

        writePointsToFile(pontos, fileString);
    }
    else if (argc == 7 && strcmp(argv[1], "cone") == 0) {
        float radius = atof(argv[2]);
        float height = atof(argv[3]);
        int slices = atoi(argv[4]);
        int stacks = atoi(argv[5]);

        pontos = cone(radius, height, slices, stacks);

        fileString = argv[6];
        fileString = "../../files3D/" + fileString;

        writePointsToFile(pontos, fileString);
    }
    else if (argc == 6 && strcmp(argv[1], "sphere") == 0) {
        float radius = atof(argv[2]);
        int slices = atoi(argv[3]);
        int stacks = atoi(argv[4]);

        pontos = sphere(radius, slices, stacks);

        fileString = argv[5];
        fileString = "../../files3D/" + fileString;

        writePointsToFile(pontos, fileString);
    }

}