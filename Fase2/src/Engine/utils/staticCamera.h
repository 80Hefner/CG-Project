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
        staticCamera(string cfg_file_str);
        GLdouble getEyeX();
        GLdouble getEyeY();
        GLdouble getEyeZ();

        void reactRegularKey(unsigned char c);

        void loadCamera(string file_str);
        void saveCamera(string file_str);
};

#endif //STATIC_CAMERA_H
