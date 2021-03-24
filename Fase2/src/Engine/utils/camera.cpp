#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <string>
#include <math.h>

#include "camera.h"

using namespace std;

Camera::Camera(int width, int height) {
    alpha = M_PI/2;

	sensitivity = 0.01;
    
	eyeX = 0.0f;
	eyeY = 10.0f;
	eyeZ = 150.0f;

	speed = 2.5;
}

GLdouble Camera::getEyeX() {
    return eyeX;
}

GLdouble Camera::getEyeY() {
    return eyeY;
}

GLdouble Camera::getEyeZ() {
    return eyeZ;
}

GLdouble Camera::getCenterX() {
	return eyeX + sin(alpha);
}

GLdouble Camera::getCenterY() {
	return eyeY;
}

GLdouble Camera::getCenterZ() {
	return eyeZ + cos(alpha);
}


void Camera::reactRegularKey(unsigned char c) {
	GLdouble eyeZ_old = eyeZ;
    switch (c) {
        case 'a':
			eyeX -= sin(alpha - M_PI/2) * speed;
        	eyeZ -= cos(alpha - M_PI/2) * speed;
			break;
        case 'd':
			eyeX -= sin(alpha + M_PI/2) * speed;
        	eyeZ -= cos(alpha + M_PI/2) * speed;
			break;
		case 'w':
			eyeX += sin(alpha) * speed;
        	eyeZ += cos(alpha) * speed;
			break;
		case 's':
			eyeX -= sin(alpha) * speed;
        	eyeZ -= cos(alpha) * speed;
			break;
		case 'e':
			eyeY += 0.4 * speed;
			break;
		case 'q':
			eyeY -= 0.4 * speed;
			break;
    }

}

void Camera::reactMouseMovement(int xx, int yy) {
	alpha -= (float)(xx) * sensitivity;
}
