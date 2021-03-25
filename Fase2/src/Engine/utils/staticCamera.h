#ifndef STATIC_CAMERA_H
#define STATIC_CAMERA_H

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <string>

using namespace std;

class staticCamera {
    private:
        GLdouble alpha;
        GLdouble alpha_inc;
        GLdouble beta;
        GLdouble beta_inc;
        GLdouble gamma;
        GLdouble gamma_inc;
    public:
        staticCamera();
        GLdouble getEyeX();
        GLdouble getEyeY();
        GLdouble getEyeZ();

        void reactRegularKey(unsigned char c);
};

#endif //STATIC_CAMERA_H
