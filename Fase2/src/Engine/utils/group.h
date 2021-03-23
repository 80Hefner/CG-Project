#ifndef GROUP_H
#define GROUP_H

#include <string>
#include <vector>

#include "../../utils/ponto.h"

using namespace std;

class Translate {
    private:
        float x, y, z;
    public:
        float getX();
        float getY();
        float getZ();
        Translate();
        Translate(float x, float y, float z);
};

class Rotate {
    private:
        float angle, axisX, axisY, axisZ;
    public:
        float getAngle();
        float getAxisX();
        float getAxisY();
        float getAxisZ();
        Rotate();
        Rotate(float angle, float axisX, float axisY, float axisZ);
};

class Scale {
    private:
        float x, y, z;
    public:
        float getX();
        float getY();
        float getZ();
        Scale();
        Scale(float x, float y, float z);
};

class Color {
    private:
        float r, g, b;
    public:
        float getR();
        float getG();
        float getB();
        Color();
        Color(float r, float g, float b);
};

class Group {
    private:
        vector<Translate> translates;
        vector<Rotate> rotates;
        vector<Scale> scales;
        Color color;
        vector<vector<Ponto>> objects;
        vector<Group> groups;
    public:
        Group();
        void addTranslate(float x, float y, float z);
        vector<Translate> getTranslates();
        void addRotate(float angle, float axisX, float axisY, float axisZ);
        vector<Rotate> getRotates();
        void addScale(float x, float y, float z);
        vector<Scale> getScales();
        void setColor(float r, float g, float b);
        Color getColor();

        void addObject(vector<Ponto> object);
        vector<vector<Ponto>> getObjects();
        void addGroup(Group group);
        vector<Group> getGroups();
};

#endif //GROUP_H
