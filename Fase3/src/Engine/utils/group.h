#ifndef GROUP_H
#define GROUP_H

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <string>
#include <vector>

#include "../../utils/ponto.h"
#include "../../utils/model.h"

using namespace std;

class Transformation {
    public:
        virtual void smt(){};
};

class Translate : public Transformation {
    private:
        float x, y, z;
    public:
        float getX() {return this->x;};
        float getY() {return this->y;};
        float getZ() {return this->z;};
        Translate();
        Translate(float x, float y, float z) {
            this->x = x;
            this->y = y;
            this->z = z;
        };
};

class Rotate : public Transformation {
    private:
        float angle, axisX, axisY, axisZ;
    public:
        float getAngle() {return this->angle;};
        float getAxisX() {return this->axisX;};
        float getAxisY() {return this->axisY;};
        float getAxisZ() {return this->axisZ;};
        Rotate();
        Rotate(float angle, float axisX, float axisY, float axisZ) {
            this->angle = angle;
            this->axisX = axisX;
            this->axisY = axisY;
            this->axisZ = axisZ;
        };
};

class Scale : public Transformation {
    private:
        float x, y, z;
    public:
        float getX() {return this->x;};
        float getY() {return this->y;};
        float getZ() {return this->z;};
        Scale();
        Scale(float x, float y, float z) {
            this->x = x;
            this->y = y;
            this->z = z;
        };
};

class Color {
    private:
        float r, g, b;
    public:
        float getR() {return this->r;};
        float getG() {return this->g;};
        float getB() {return this->b;};
        Color() {
            this->r = 1.0f;
            this->g = 1.0f;
            this->b = 1.0f;
        };
        Color(float r, float g, float b) {
            this->r = r;
            this->g = g;
            this->b = b;
        };
};

class Group {
    private:
        vector<Transformation*> transformations;
        Color* color;
        vector<Model> models;
        vector<Group> groups;
    public:
        Group();
        void addTranslate(float x, float y, float z);
        void addRotate(float angle, float axisX, float axisY, float axisZ);
        void addScale(float x, float y, float z);
        vector<Transformation*> getTransformations();

        void setColor(float r, float g, float b);
        Color* getColor();

        void addModel(Model model);
        vector<Model> getModels();
        void addGroup(Group group);
        vector<Group> getGroups();
};

#endif //GROUP_H
