#include <string>
#include <sstream>
#include <vector>

#include "group.h"

using namespace std;

// * Translate * //

Translate::Translate() { //TODO: checkar isto
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

Translate::Translate(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}


// * Rotate * //

Rotate::Rotate() { //TODO: checkar isto
    this->angle = 0;
    this->axisX = 0;
    this->axisY = 0;
    this->axisZ = 0;
}

Rotate::Rotate(float angle, float axisX, float axisY, float axisZ) {
    this->angle = angle;
    this->axisX = axisX;
    this->axisY = axisY;
    this->axisZ = axisZ;
}


// * Group * //

Group::Group() {
    translate = Translate();
    rotate = Rotate();
    _3dFilesList = {};
    groups = {};
}

void Group::setTranslate(float x, float y, float z) {
    this->translate = Translate(x,y,z);
}

void Group::setRotate(float angle, float axisX, float axisY, float axisZ) {
    this->rotate = Rotate(angle,axisX,axisY,axisZ);
}

void Group::add3dFile(string file) {
    this->_3dFilesList.push_back(file);
}

void Group::addGroup(Group group) {
    this->groups.push_back(group);
}
