#include <sstream>

#include "group.h"

using namespace std;

// * Dynamic Translate * //

// Given a t from a segment an its 4 points, returns the corresponding points in the curve
Ponto getCatmullRomPoint(float t, Ponto p0, Ponto p1, Ponto p2, Ponto p3) {
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

    // Calculate curve point
    float x_pos = (m_t * m * m_px)[0][0];
    float y_pos = (m_t * m * m_py)[0][0];
    float z_pos = (m_t * m * m_pz)[0][0];

    return Ponto(x_pos, y_pos, z_pos);
}

void DynamicTranslate::generateRenderPoints() {
    int segment_count = points.size() - 3;

    for (int i = 0; i < segment_count; i++) {
        Ponto p0 = points[i];
        Ponto p1 = points[i+1];
        Ponto p2 = points[i+2];
        Ponto p3 = points[i+3];

        for (float t = 0; t < 1.0; t += CATMULL_TESSELATION) {
            Ponto curve_point = getCatmullRomPoint(t, p0, p1, p2, p3);
            render_points.push_back(curve_point);
        }
    }

}

DynamicTranslate::DynamicTranslate(float total_time, vector<Ponto> points) {
    this->total_time = total_time;
    this->segment_time = this->total_time / (points.size() - 3);
    this->timebase = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    this->elapsed_time = 0.0;
    this->points = points;
    
    generateRenderPoints();  // iniciates render_points with the points to render the curve
}

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

    Ponto curve_point = getCatmullRomPoint(t, p0, p1, p2, p3);
    
    // Apply transformations
    // position teapot along the curve
    glTranslatef(curve_point.getX(), curve_point.getY(), curve_point.getZ());

    // align teapot with the curve


    if (elapsed_time == total_time) {
        elapsed_time = 0;
        timebase = current_time;
    }
}

void DynamicTranslate::renderCatmullRomCurve() {
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINE_LOOP);
    //for (int i = 1; i < points.size()-2; i++) glVertex3f(points[i].getX(), points[i].getY(), points[i].getZ());
    for (Ponto p : render_points) glVertex3f(p.getX(), p.getY(), p.getZ());
    glEnd();
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
