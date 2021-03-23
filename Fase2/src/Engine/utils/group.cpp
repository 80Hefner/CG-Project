#include <string>
#include <sstream>
#include <vector>

#include "group.h"

using namespace std;

// * Translate * //

Translate::Translate(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

float Translate::getX() {
    return this->x;
}

float Translate::getY() {
    return this->y;
}

float Translate::getZ() {
    return this->z;
}

// * Rotate * //

Rotate::Rotate(float angle, float axisX, float axisY, float axisZ) {
    this->angle = angle;
    this->axisX = axisX;
    this->axisY = axisY;
    this->axisZ = axisZ;
}

float Rotate::getAngle() {
    return this->angle;
}

float Rotate::getAxisX() {
    return this->axisX;
}

float Rotate::getAxisY() {
    return this->axisY;
}

float Rotate::getAxisZ() {
    return this->axisZ;
}

// * Scale * //

Scale::Scale(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

float Scale::getX() {
    return this->x;
}

float Scale::getY() {
    return this->y;
}

float Scale::getZ() {
    return this->z;
}

// * Color * //

Color::Color() {
    this->r = 1.0f;
    this->g = 1.0f;
    this->b = 1.0f;
}

Color::Color(float r, float g, float b) {
    this->r = r;
    this->g = g;
    this->b = b;
}

float Color::getR() {
    return this->r;
}

float Color::getG() {
    return this->g;
}

float Color::getB() {
    return this->b;
}

// * Group * //

Group::Group() {
    translates = {};
    rotates = {};
    scales = {};
    color = Color();
    objects = {};
    groups = {};
}

void Group::addTranslate(float x, float y, float z) {
    Translate tr = Translate(x,y,z);
    this->translates.push_back(tr);
}

vector<Translate> Group::getTranslates() {
    return this->translates;
}

void Group::addRotate(float angle, float axisX, float axisY, float axisZ) {
    Rotate rt = Rotate(angle,axisX,axisY,axisZ);
    this->rotates.push_back(rt);
}

vector<Rotate> Group::getRotates() {
    return this->rotates;
}

void Group::addScale(float x, float y, float z) {
    Scale sc = Scale(x,y,z);
    this->scales.push_back(sc);
}

vector<Scale> Group::getScales() {
    return this->scales;
}

void Group::setColor(float r, float g, float b) {
    Color cl = Color(r,g,b);
    this->color = cl;
}

Color Group::getColor() {
    return this->color;
}

void Group::addObject(vector<Ponto> object) {
    this->objects.push_back(object);
}

vector<vector<Ponto>> Group::getObjects() {
    return this->objects;
}

void Group::addGroup(Group group) {
    this->groups.push_back(group);
}

vector<Group> Group::getGroups() {
    return this->groups;
}