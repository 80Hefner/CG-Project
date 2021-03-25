#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <string>
#include <math.h>

#include "fpsCamera.h"

using namespace std;

fpsCamera::fpsCamera(int width, int height) {
    alpha = M_PI/2;
	sensitivity = 0.01;
    
	eyeX = 0.0f;
	eyeY = 1.0f;
	eyeZ = 10.0f;
	speed = 1.5;

	startX = width / 2;
	tracking = 0;
}

GLdouble fpsCamera::getEyeX() {
    return eyeX;
}

GLdouble fpsCamera::getEyeY() {
    return eyeY;
}

GLdouble fpsCamera::getEyeZ() {
    return eyeZ;
}

GLdouble fpsCamera::getCenterX() {
	return eyeX + sin(alpha);
}

GLdouble fpsCamera::getCenterY() {
	return eyeY;
}

GLdouble fpsCamera::getCenterZ() {
	return eyeZ + cos(alpha);
}


void fpsCamera::reactRegularKey(unsigned char c) {
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
		case 'q':
			eyeY += 0.2 * speed;
			break;
		case 'e':
			eyeY -= 0.2 * speed;
			break;
    }

}

void fpsCamera::processMouseMotion(int xx, int yy) {
	if (tracking == 1) {
		int deltaX = xx - startX;
		startX = xx;

		alpha -= deltaX * sensitivity;
	}
}

void fpsCamera::processMouseButtons(int button, int state, int xx, int yy) {
	if (state == GLUT_DOWN) {
		if (button == GLUT_LEFT_BUTTON) {
			startX = xx;
			tracking = 1;
		}
	}
	else if (state == GLUT_UP) {
		tracking = 0;
	}
}