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
    alpha = 2*M_PI/3;
	beta = M_PI/2;
	sensitivity = 0.01;
    
	eyeX = 0.0f;
	eyeY = 1.0f;
	eyeZ = 10.0f;
	speed = 1.5;

	startX = width / 2;
	startY = height / 2;
	tracking[0] = 0;
	tracking[1] = 0;
}

GLdouble fpsCamera::getCenterX() {
	return eyeX + sin(alpha) * sin(beta);
}

GLdouble fpsCamera::getCenterY() {
	return eyeY + cos(beta);
}

GLdouble fpsCamera::getCenterZ() {
	return eyeZ + cos(alpha) * sin(beta);
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
			eyeY += 0.3 * speed;
			break;
		case 'e':
			eyeY -= 0.3 * speed;
			break;
    }

}

void fpsCamera::processMouseMotion(int xx, int yy) {
	if (tracking[0] == 1) {
		int deltaX = xx - startX;
		startX = xx;

		alpha -= deltaX * sensitivity;
	}
	
	if (tracking[1] == 1) {
		int deltaY = yy - startY;
		startY = yy;

		beta += deltaY * sensitivity;

		if (beta < M_PI/32) beta = M_PI/32;
    	else if (beta > M_PI - M_PI/32) beta = M_PI - M_PI/32;
	}
}

void fpsCamera::processMouseButtons(int button, int state, int xx, int yy) {
	if (state == GLUT_DOWN) {
		if (button == GLUT_LEFT_BUTTON) {
			startX = xx;
			tracking[0] = 1;
		}
		else if (button == GLUT_RIGHT_BUTTON) {
			startY = yy;
			tracking[1] = 1;
		}
	}
	else if (state == GLUT_UP) {
		if (button == GLUT_LEFT_BUTTON)
			tracking[0] = 0;
		else if (button == GLUT_RIGHT_BUTTON)
			tracking[1] = 0;
	}
}