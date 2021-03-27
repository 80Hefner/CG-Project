#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <vector>

#include "ponto.h"

using namespace std;

class Object {
    private:
        string description;
        vector<Ponto> points;
    public:
        Object(string description, vector<Ponto> points) {
            this->description = description;
            this->points = points;
        };
        
        string getDescription() {return this->description;};
        vector<Ponto> getPoints() {return this->points;};
};

#endif //OBJECT_H