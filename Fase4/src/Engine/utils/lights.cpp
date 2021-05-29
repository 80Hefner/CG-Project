#include "lights.h"

void Light::apply() {

    glLightfv(GL_LIGHT0+this->index, GL_AMBIENT, this->ambient);
    glLightfv(GL_LIGHT0+this->index, GL_DIFFUSE, this->diffuse);
    glLightfv(GL_LIGHT0+this->index, GL_SPECULAR, this->specular);

    GLfloat vec;
    this->type == LIGHT_POINT ? vec = 0 : vec = 1;

    GLfloat pos[4] = {this->pos->getX(), this->pos->getY(), this->pos->getZ(), 1.0};
    glLightfv(GL_LIGHT0+this->index, GL_POSITION, pos);
}
