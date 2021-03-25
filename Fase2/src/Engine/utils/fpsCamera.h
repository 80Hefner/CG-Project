#ifndef FPS_CAMERA_H
#define FPS_CAMERA_H

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <string>

using namespace std;

class fpsCamera {
    private:
        GLdouble alpha;
        float sensitivity;

        GLdouble eyeX;
        GLdouble eyeY;
        GLdouble eyeZ;
        float speed;

        int startX, tracking;
    public:
        fpsCamera(int width, int height);
        GLdouble getEyeX();
        GLdouble getEyeY();
        GLdouble getEyeZ();
        GLdouble getCenterX();
        GLdouble getCenterY();
        GLdouble getCenterZ();

        void reactRegularKey(unsigned char c);
        void processMouseMotion(int xx, int yy);
        void processMouseButtons(int button, int state, int xx, int yy);
};

#endif //FPS_CAMERA_H
