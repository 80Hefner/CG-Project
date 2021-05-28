#ifndef MODEL_H
#define MODEL_H

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

class Model {
    private:
        GLuint p_vbo_ind;
        GLuint n_vbo_ind;
        GLsizei vertice_count;
    public:
        Model() {
            this->p_vbo_ind = 0;
            this->n_vbo_ind = 0;
            this->vertice_count = 0;
        };
        Model(GLuint p_vbo_ind, GLuint n_vbo_ind, GLsizei vertice_count) {
            this->p_vbo_ind = p_vbo_ind;
            this->n_vbo_ind = n_vbo_ind;
            this->vertice_count = vertice_count;
        };
        
        GLuint getPVBOInd() {return this->p_vbo_ind;};
        GLuint getNVBOInd() {return this->n_vbo_ind;};
        GLsizei getVerticeCount() {return this->vertice_count;};
};

#endif //MODEL_H
