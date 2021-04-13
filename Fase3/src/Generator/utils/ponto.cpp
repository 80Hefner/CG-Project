#include <string>
#include <sstream>
#include <vector>

#include "ponto.h"

using namespace std;

Ponto::Ponto(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Ponto::Ponto(string line) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(line);

    while (getline(tokenStream, token, ','))
        tokens.push_back(token);

    this->x = atof(tokens[0].c_str());
    this->y = atof(tokens[1].c_str());
    this->z = atof(tokens[2].c_str());
}


float Ponto::getX() {
    return this->x;
}

float Ponto::getY() {
    return this->y;
}

float Ponto::getZ() {
    return this->z;
}
