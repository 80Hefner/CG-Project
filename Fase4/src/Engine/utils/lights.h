#ifndef LIGHTS_H
#define LIGHTS_H

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "../../utils/ponto.h"

#define LIGHT_POINT 1

class Light {
    private:
        int index;
        int type;
        GLfloat ambient[4] = {0.2f, 0.2f, 0.2f, 1.0f};
        GLfloat diffuse[4] = {1.0f, 1.0f, 1.0f, 1.0f};
        GLfloat specular[4] = {1.0f, 1.0f, 1.0f, 1.0f};
        Ponto* pos;
    public:
        Light() {
            this->index = -1;
            this->type = 0;
            this->pos = new Ponto(0, 0, 0);
        };
        Light(int index, int type, Ponto* pos) {
            this->index = index;
            this->type = type;
            this->pos = pos;
        };

        void apply();

        int getIndex() {return this->index;};
        int getType() {return this->type;};
        Ponto* getPos() {return this->pos;};

        void setIndex(int index) {this->index = index;};
        void setType(int type) {this->type = type;};
        void setPos(Ponto* pos) {this->pos = pos;};    
};

#endif //LIGHTS_H
