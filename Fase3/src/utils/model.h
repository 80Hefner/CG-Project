#ifndef MODEL_H
#define MODEL_H

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "ponto.h"

using namespace std;

class Model {
    private:
        GLuint vbo_ind;
        GLuint vertice_count;
    public:
        Model() {
            this->vbo_ind = 0;
            this->vertice_count = 0;
        };
        Model(GLuint vbo_ind, GLuint vertice_count) {
            this->vbo_ind = vbo_ind;
            this->vertice_count = vertice_count;
        };
        
        GLuint getVBOInd() {return this->vbo_ind;};
        GLuint getVerticeCount() {return this->vertice_count;};
};

#endif //MODEL_H
