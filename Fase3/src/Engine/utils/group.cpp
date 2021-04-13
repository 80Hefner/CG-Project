#include <sstream>

#include "group.h"

using namespace std;

// * Group * //

Group::Group() {
    transformations = {};
    color = nullptr;
    models = {};
    groups = {};
}

void Group::addTranslate(float x, float y, float z) {
    Translate* tr = new Translate(x,y,z);
    this->transformations.push_back(tr);
}

void Group::addRotate(float angle, float axisX, float axisY, float axisZ) {
    Rotate* rt = new Rotate(angle,axisX,axisY,axisZ);
    this->transformations.push_back(rt);
}

void Group::addScale(float x, float y, float z) {
    Scale* sc = new Scale(x,y,z);
    this->transformations.push_back(sc);
}

vector<Transformation*> Group::getTransformations() {
    return this->transformations;
}

void Group::setColor(float r, float g, float b) {
    Color* cl = new Color(r,g,b);
    this->color = cl;
}

Color* Group::getColor() {
    return this->color;
}

void Group::addModel(Model model) {
    this->models.push_back(model);
}

vector<Model> Group::getModels() {
    return this->models;
}

void Group::addGroup(Group group) {
    this->groups.push_back(group);
}

vector<Group> Group::getGroups() {
    return this->groups;
}
