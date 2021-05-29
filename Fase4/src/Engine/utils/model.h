#ifndef MODEL_H
#define MODEL_H

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "../../utils/float_vector.h"

using namespace std;

class Model {
    private:
        GLuint p_vbo_ind;
        GLuint n_vbo_ind;
        GLsizei vertice_count;
        GLfloat* ambient;
        GLfloat* specular;
        GLfloat* diffuse;
        GLfloat* emissive;
        GLfloat shininess = 0.0;
    public:
        Model() {
            this->p_vbo_ind = 0;
            this->n_vbo_ind = 0;
            this->vertice_count = 0;
            this->ambient = nullptr;
            this->specular = nullptr;
            this->diffuse = nullptr;
            this->emissive = nullptr;
        };
        Model(GLuint p_vbo_ind, GLuint n_vbo_ind, GLsizei vertice_count) {
            this->p_vbo_ind = p_vbo_ind;
            this->n_vbo_ind = n_vbo_ind;
            this->vertice_count = vertice_count;
        };

        void setAmbient(GLfloat* ambient) {this->ambient = ambient;};
        void setSpecular(GLfloat* specular) {this->specular = specular;};
        void setDiffuse(GLfloat* diffuse) {this->diffuse = diffuse;};
        void setEmissive(GLfloat* emissive) {this->emissive = emissive;};

        GLuint getPVBOInd() {return this->p_vbo_ind;};
        GLuint getNVBOInd() {return this->n_vbo_ind;};
        GLsizei getVerticeCount() {return this->vertice_count;};

        GLfloat* getDiffuse() {return this->diffuse;};
        GLfloat* getAmbient() {return this->ambient;};
        GLfloat* getSpecular() {return this->specular;};
        GLfloat* getEmissive() {return this->emissive;};
        GLfloat getShininess() {return this->shininess;};
};

#endif //MODEL_H
