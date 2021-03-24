#ifndef CAMERA_H
#define CAMERA_H

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <string>

using namespace std;

class Camera {
    private:
        GLdouble alpha;

        float sensitivity;

        GLdouble eyeX;
        GLdouble eyeY;
        GLdouble eyeZ;
        float speed;
    public:
        Camera(int width, int height);
        GLdouble getEyeX();
        GLdouble getEyeY();
        GLdouble getEyeZ();
        GLdouble getCenterX();
        GLdouble getCenterY();
        GLdouble getCenterZ();

        void reactRegularKey(unsigned char c);
        void reactMouseMovement(int xx, int yy);
};

#endif //CAMERA_H
