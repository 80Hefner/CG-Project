#include <sstream>

#include "group.h"

using namespace std;

// * Dynamic Translate * //

void DynamicTranslate::applyTransformations() {
    // Calculate passage of time
    float current_time = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    elapsed_time = current_time - timebase;

    if (elapsed_time > total_time) elapsed_time = total_time; // TODO: melhorar isto

    float t = fmod(elapsed_time, segment_time) / segment_time;

    // Calculate transformations
    int segment = elapsed_time / segment_time;
    Ponto p0 = points[segment];
    Ponto p1 = points[segment+1];
    Ponto p2 = points[segment+2];
    Ponto p3 = points[segment+3];

    // Generate matrices
    Matrix<float> m_t = {{t*t*t, t*t, t, 1.0f}};

    Matrix<float> m = {{-0.5f, 1.5f,-1.5f, 0.5f},
                       { 1.0f,-2.5f, 2.0f,-0.5f},
                       {-0.5f, 0.0f, 0.5f, 0.0f},
                       { 0.0f, 1.0f, 0.0f, 0.0f}};

    Matrix<float> m_px = {{p0.getX()},
                          {p1.getX()},
                          {p2.getX()},
                          {p3.getX()}};

    Matrix<float> m_py = {{p0.getY()},
                          {p1.getY()},
                          {p2.getY()},
                          {p3.getY()}};

    Matrix<float> m_pz = {{p0.getZ()},
                          {p1.getZ()},
                          {p2.getZ()},
                          {p3.getZ()}};

    float x_trans = (m_t * m * m_px)[0][0];
    float y_trans = (m_t * m * m_py)[0][0];
    float z_trans = (m_t * m * m_pz)[0][0];

    // Apply transformations
    glTranslatef(x_trans, y_trans, z_trans);

    if (elapsed_time == total_time) {
        elapsed_time = 0;
        timebase = current_time;
    }
}

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

void Group::addDynamicTranslate(float time, vector<Ponto> points) {
    DynamicTranslate* dtr = new DynamicTranslate(time, points);
    this->transformations.push_back(dtr);
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
