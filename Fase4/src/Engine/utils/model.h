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
        string description;
        GLuint p_vbo_ind;
        GLuint n_vbo_ind;
        GLsizei vertice_count;
        GLfloat ambient[4];
        GLfloat specular[4];
        GLfloat diffuse[4];
        GLfloat emissive[4];
        GLfloat shininess = 0.0;
    public:
        Model() {
            this->description = description;
            this->p_vbo_ind = 0;
            this->n_vbo_ind = 0;
            this->vertice_count = 0;
        };
        Model(GLuint p_vbo_ind, GLuint n_vbo_ind, GLsizei vertice_count) {
            this->p_vbo_ind = p_vbo_ind;
            this->n_vbo_ind = n_vbo_ind;
            this->vertice_count = vertice_count;
        };

        void setAmbient(GLfloat r_ambient, GLfloat g_ambient, GLfloat b_ambient, GLfloat a_ambient) {
            this->ambient[0] = r_ambient;
            this->ambient[1] = g_ambient;
            this->ambient[2] = b_ambient;
            this->ambient[3] = a_ambient;
        };

        void setSpecular(GLfloat r_specular, GLfloat g_specular, GLfloat b_specular, GLfloat a_specular) {
            this->specular[0] = r_specular;
            this->specular[1] = g_specular;
            this->specular[2] = b_specular;
            this->specular[3] = a_specular;
        };

        void setDiffuse(GLfloat r_diffuse, GLfloat g_diffuse, GLfloat b_diffuse, GLfloat a_diffuse) {
            this->diffuse[0] = r_diffuse;
            this->diffuse[1] = g_diffuse;
            this->diffuse[2] = b_diffuse;
            this->diffuse[3] = a_diffuse;
        };

        void setEmissive(GLfloat r_emissive, GLfloat g_emissive, GLfloat b_emissive, GLfloat a_emissive) {
            this->emissive[0] = r_emissive;
            this->emissive[1] = g_emissive;
            this->emissive[2] = b_emissive;
            this->emissive[3] = a_emissive;
        };

        void setDescription(string description) {
            this->description = description;
        }
        
        string getDescription() {return this->description;}; 

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
